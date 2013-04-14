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
#include <cmath>
using namespace std;
#include "cmtyConfig.h"
struct edgeBtw {
	int u, v;
	int weight;
	edgeBtw(int u = 0, int v = 0, int weight = 0) :
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
	for (int i = 0; i < n; i++) {
		vector<int> dis(n, -1), sigma(n, 0);
		vector<float> delta(n, 0);
		vector<set<int> > prev(n);
		queue<int> q, s;

		//initialize sigma shortest path
		sigma[i] = 1;
		dis[i] = 0;
		q.push(i);
		//breadth first search
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			s.push(v);
			const vector<int>& adj = g[v];
			for (const auto& u : adj) {
				if (dis[u] == -1) {
					dis[u] = dis[v] + 1;
					q.push(u);
				}
				if (dis[u] == dis[v] + 1) {
					sigma[u] += sigma[v];
					prev[u].insert(v);
				}
			}
		}
		while (!s.empty()) {
			int v = s.front();
			s.pop();
			const vector<int>& adj = g[v];
			int sigmaV = sigma[v];
			int deltaV = delta[v];
			for (const auto & w : adj) {
				double c = sigma[w] * 1.0 / sigmaV * (1 + deltaV);
				delta[w] += c;
				auto i = lower_bound(btw.begin(), btw.end(),
						edgeBtw(min(w, v), max(w, v), 0));
				i->weight += c;
			}
		}
	}
	sort(btw.begin(), btw.end(), cmp_weight);
}

#endif /* BETWEENNESS_H_ */
