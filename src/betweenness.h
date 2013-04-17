/*
 * betweenness.h
 *
 *  Created on: Apr 13, 2013
 *      Author: ronaflx
 */

#ifndef BETWEENNESS_H_
#define BETWEENNESS_H_

#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <cmath>
#include <stack>
using namespace std;
#include "cmtyConfig.h"
struct edgeBtw {
	int u, v;
	double weight;
	edgeBtw(int u = 0, int v = 0, double weight = 0) :
			u(u), v(v), weight(weight) {
	}
};
bool operator <(const edgeBtw& a, const edgeBtw& b) {
	return a.u == b.u ? a.v < b.v : a.u < b.u;
}
bool cmp_weight(const edgeBtw& a, const edgeBtw& b) {
	return a.weight > b.weight;
}
void edge_betweenness(const undirected_graph& g, vector<edgeBtw>& btw) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		for (const auto & v : g[i]) {
			if (i < v) {
				btw.push_back(edgeBtw(i, v, 0));
			}
		}
	}
	sort(btw.begin(), btw.end());
	vector<int> dis(n), sigma(n);
	vector<vector<int> > prev(n);
	vector<double> delta(n);
	queue<int> q;
	stack<int> s;
	for (int node = 0; node < n; node++) {
		// initialize distance, delta, previous, sigma
		fill(dis.begin(), dis.end(), -1);
		fill(sigma.begin(), sigma.end(), 0);
		fill(delta.begin(), delta.end(), 0);
		for (int i = 0; i < n; i++) {
			prev[i].clear();
		}

		sigma[node] = 1;
		dis[node] = 0;
		q.push(node);

		//breadth first search : shortest path
		while (!q.empty()) {
			const int v = q.front();
			q.pop();
			s.push(v);
			const vector<int>& adj = g[v];
			const int distance = dis[v] + 1;
			for (const auto& u : adj) {
				if (dis[u] == -1) {
					dis[u] = distance;
					q.push(u);
				}
				if (dis[u] == distance) {
					sigma[u] += sigma[v];
					prev[u].push_back(v);
				}
			}
		}
		while (!s.empty()) {
			const int w = s.top();
			s.pop();
			const vector<int>& adj = prev[w];
			const double sigmaW = sigma[w];
			const double deltaW = delta[w];
			for (const auto & v : adj) {
				double c = (sigma[v] * 1.0 / sigmaW) * (1.0 + deltaW);
				delta[v] += c;
				const int newu = min(w, v);
				const int newv = max(w, v);
				auto iter = lower_bound(btw.begin(), btw.end(),
						edgeBtw(newu, newv, 0));
				iter->weight += c;
			}
		}
	}
	sort(btw.begin(), btw.end(), cmp_weight);
}

#endif /* BETWEENNESS_H_ */
