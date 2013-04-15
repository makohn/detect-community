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
	btw.reserve(5000);
	for (int i = 0; i < n; i++) {
		for (const auto & v : g[i]) {
			if (i < v) {
				btw.push_back(edgeBtw(i, v, 0));
			}
		}
	}
	sort(btw.begin(), btw.end());
	vector<int> dis(n, -1), sigma(n, 0);
	vector<float> delta(n, 0);
	vector<vector<int> > prev(n);
	queue<int> q, s;
	for (int node = 0; node < n; node++) {
		// init dis, sigma, delta, prev
		fill(dis.begin(), dis.end(), -1);
		fill(sigma.begin(), sigma.end(), 0);
		fill(delta.begin(), delta.end(), 0);
		for(int i = 0;i < n;i++) {
			prev[i].clear();
		}
		//initialize sigma shortest path
		sigma[node] = 1;
		dis[node] = 0;
		q.push(node);
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
					prev[u].push_back(v);
				}
			}
		}
		//slow
		while (!s.empty()) {
			int w = s.front();
			s.pop();
			const vector<int>& adj = prev[w];
			int sigmaV = sigma[w];
			int deltaV = delta[w];
			for (const auto & v : adj) {
				double c = (sigma[v] * 1.0 / sigmaV) * (1 + deltaV);
				delta[v] += c;
				auto iter = lower_bound(btw.begin(), btw.end(),
						edgeBtw(min(w, v), max(w, v), 0));
				iter->weight += c;
			}
		}
	}
	sort(btw.begin(), btw.end(), cmp_weight);
}

#endif /* BETWEENNESS_H_ */
