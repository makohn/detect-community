/*
 * Cluster.cpp
 *
 *  Created on: Apr 27, 2013
 *      Author: ronaflx
 */

#include "Cluster.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "util.h"
#include "../qpbo/QPBO.h"
namespace ego {

Cluster::Cluster(EgoGraph * graph) :
		graph_(graph) {
	theta_ = NULL;
	alpha_ = NULL;
}

Cluster::~Cluster() {
	delete[] theta_;
	delete[] alpha_;
}
void Cluster::train(int K, int reps, int gradientReps, int improveReps,
		double lamda, int whichLoss) {
	//initialize
	const int N = graph_->num_features_;
	const int M = graph_->num_nodes_;
	const double rate = 1.0 / graph_->num_nodes_ / graph_->num_nodes_;
	srand(time(0));
	delete[] theta_;
	delete[] alpha_;
	num_ = K * N;
	theta_ = new double[num_];
	alpha_ = new double[K];
	chat_ = vector<set<int> >(K);
	// reps iterations
	for (int rep = 0; rep < reps; rep++) {
		//for each circle
		for (int k = 0; k < K; k++) {
			// first iteration or degenerate solution
			if (rep == 0 || chat_[k].size() == 0U
					|| int(chat_[k].size()) == M) {
				chat_[k].clear();
				for (int i = 0; i < M; i++) {
					if ((rand() & 1) || 1) {
						chat_[k].insert(i);
					}
				}
				// set a single feature 1.0, other is 0.0
				int start = k * N;
				fill(theta_ + start, theta_ + start + N, 0.0);
				theta_[start + k % N] = 1.0;
				theta_[start] = 1.0;
				alpha_[k] = 1.0;
			}
		}
		vector<int> order;
		for (int k = 0; k < K; k++) {
			order.push_back(k);
		}
		//shuffle all circles
		//random_shuffle(order.begin(), order.end());
		int changed = 0;
		for (const auto & u : order) {
			chat_[u] = minimize_graphcuts(u, improveReps, changed);
            for(const auto & i : chat_[u]) {
                printf("%d ", i);
            }
            puts("");
		}
		double loglike_prev = loglikelihood(theta_, alpha_, chat_);
		printf("loglikelihood %lf\n", loglike_prev);
		if (!changed)
			break;
		// gradient ascent
		double loglike_curr = 0.0;
		double * dlda = new double[K];
		double * dldt = new double[num_];
		for (int gradient = 0; gradient < gradientReps; gradient++) {
			dl(dldt, dlda, K, lamda);
			for (int i = 0; i < num_; i++) {
				theta_[i] += rate * dldt[i];
			}
			for (int k = 0; k < K; k++) {
				alpha_[k] += rate * dlda[k];
			}
			loglike_curr = loglikelihood(theta_, alpha_, chat_);
			//if current loglikelihood is small than previous loglikelihood, recover
			if (loglike_curr < loglike_prev) {
				for (int i = 0; i < num_; i++)
					theta_[i] -= rate * dldt[i];
				for (int k = 0; k < K; k++)
					alpha_[k] -= rate * dlda[k];
				loglike_curr = loglike_prev;
				break;
			}
			loglike_prev = loglike_curr;
		}
		delete[] dlda;
		delete[] dldt;
	}
}
double Cluster::loglikelihood(const double * theta, const double * alpha,
		const vector<set<int> >& chat) {
	const int K = (int) chat.size();
	const int N = graph_->num_features_;
	const int M = graph_->num_nodes_;

	vector<vector<bool> > flag(K, vector<bool>(M));
	for (int k = 0; k < K; k++) {
		for (const auto & node : chat[k]) {
			flag[k][node] = true;
		}
	}

	double loglike = 0.0;
	for (const auto & i : graph_->edge_features_) {
		// for each (x, y) belongs to (V * V), calculate Φ(x, y)
		double inner_product = 0.0;
		pair<int, int> e = i.first;
		int node0 = e.first;
		int node1 = e.second;
		bool exist = graph_->edge_.find(e) != graph_->edge_.end();
		for (int k = 0; k < K; k++) {
			double d = (flag[k][node0] == flag[k][node1]) ? 1.0 : -alpha[k];
			inner_product += d * inp(i.second, theta + k * N, N);
		}
		if (exist) {
			loglike += inner_product;
		}
		loglike -= log(1.0 + exp(inner_product));
	}
	return loglike;
}

std::set<int> Cluster::minimize_graphcuts(int k, int improveReps,
		int& changed) {
	const int E = (int) graph_->feature_.size();
	const int K = (int) chat_.size();
	const int N = graph_->num_features_;
	const int M = graph_->num_nodes_;

	QPBO<double> q(M, E);
	q.AddNode(M);
	map<pair<int, int>, double> mc00;
	map<pair<int, int>, double> mc11;
	for (const auto & i : graph_->edge_features_) {
		pair<int, int> e = i.first;
		int node0 = e.first;
		int node1 = e.second;
		bool exist = graph_->edge_.find(e) != graph_->edge_.end();
		double inner_product = inp(i.second, theta_ + k * N, N);
		double other_product = 0.0;
		for (int l = 0; l < K; l++) {
			if (l == k)
				continue;
			const set<int>& ref = chat_[l];
			double d =
					(ref.find(node0) != ref.end()
							&& ref.find(node1) != ref.end()) ? 1 : -alpha_[l];
			other_product += d * inp(i.second, theta_ + l * N, N);
		}
		double e00 = 0.0, e11 = 0.0;
		if (exist) {
			e00 = -other_product + alpha_[k] * inner_product
					+ log(1.0 + exp(other_product - alpha_[k] * inner_product));
			e11 = -other_product - inner_product
					+ log(1.0 + exp(other_product + inner_product));
		} else {
			e00 = log(1.0 + exp(other_product - alpha_[k] * inner_product));
			e11 = log(1.0 + exp(other_product + inner_product));
		}
		mc00[e] = e00;
		mc11[e] = e11;
		q.AddPairwiseTerm(node0, node1, e00, e00, e00, e11);
	}
	for (int i = 0; i < M; i++) {
		if (chat_[k].find(i) == chat_[k].end()) {
			q.SetLabel(i, 0);
		} else {
			q.SetLabel(i, 1);
		}
	}
	q.MergeParallelEdges();
	q.Solve();
	q.ComputeWeakPersistencies();
	for (int i = 0; i < improveReps; i++) {
		q.Improve();
	}
	vector<int> old_label(M);
	vector<int> new_label(M);
	set<int> res;
	for (int i = 0; i < M; i++) {
		new_label[i] = 0;
		int id = q.GetLabel(i);
		if (id == 1) {
			res.insert(i);
			new_label[i] = 1;
		} else if (id < 0 && chat_[k].find(i) != chat_[k].end()) {
			res.insert(i);
			new_label[i] = 1;
		}
		if (chat_[k].find(i) == chat_[k].end()) {
			old_label[i] = 0;
		} else {
			old_label[i] = 1;
		}
	}
	double oldE = 0.0, newE = 0.0;
	for (const auto & i : graph_->edge_features_) {
		pair<int, int> e = i.first;
		int node0 = e.first;
		int node1 = e.second;

		int old_n0 = old_label[node0];
		int old_n1 = old_label[node1];
		int new_n0 = new_label[node0];
		int new_n1 = new_label[node1];
		if (old_n0 && old_n1) {
			oldE += mc11[e];
		} else {
			oldE += mc00[e];
		}
		if (new_n0 && new_n1) {
			newE += mc11[e];
		} else {
			newE += mc00[e];
		}
	}
	//printf("%d %.2lf %.2lf\n", k, newE, oldE);
	if (newE > oldE || res.size() == 0) {
		res = chat_[k];
	} else {
		changed |= (res != chat_[k]);
	}
	return res;
}

void Cluster::dl(double* dldt, double* dlda, int K, double lamda) {
	const int N = graph_->num_features_;
	const int M = graph_->num_nodes_;

	vector<double> inps(K);
	vector<vector<bool> > flag(K, vector<bool>(M));

	for (int k = 0; k < K; k++) {
		for (const auto & node : chat_[k]) {
			flag[k][node] = true;
		}
	}

	for (int i = 0; i < num_; i++) {
		dldt[i] = -lamda * sgn(theta_[i]);
	}

	fill(dlda, dlda + K, 0.0);
	for (const auto & i : graph_->edge_features_) {
		double inner_product = 0.0;
		pair<int, int> e = i.first;
		int node0 = e.first;
		int node1 = e.second;
		bool exist = graph_->edge_.find(e) != graph_->edge_.end();
		for (int k = 0; k < K; k++) {
			double d = ((flag[k][node0] == flag[k][node1]) ? 1.0 : -alpha_[k]);
			inner_product += d * (inps[k] = inp(i.second, theta_ + k * N, N));
		}
		double expinp = exp(inner_product);
		double q = expinp / (1 + expinp);
		if (q != q)
			q = 1; //in case q is not a number.
		for (int k = 0; k < K; k++) {
			bool sameCircle = (flag[k][node0] == flag[k][node1]);
			double d = (sameCircle ? 1.0 : -alpha_[k]);
			for (const auto& sparse_vector : *i.second) {
				int j = sparse_vector.first;
				int f = sparse_vector.second;
				if (exist) {
					dldt[k * N + j] = d * f;
				}
				dldt[k * N + j] -= d * f * q;
			}
			if (!sameCircle) {
				if (exist) {
					dlda[k] -= inps[k];
				}
				dlda[k] += inps[k] * q;
			}
		}
	}
}
} /* namespace ego */
