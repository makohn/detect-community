/*
 * connection.h
 *
 *  Created on: Apr 10, 2013
 *      Author: ronaflx
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_
#include "cmtyConfig.h"
#include <queue>
using namespace std;

// get weak connected component though node
community& get_node_wcc(const undirected_graph& g, int node, community& wcc) {
	int n = g.size();
	vector<bool> vst(n);
	queue<int> q;
	q.push(node);
	vst[node] = 1;
	while (!q.empty()) {
		int v = q.front();
		wcc.push_back(v);
		q.pop();
		for(auto& i : g[v]) {
			if (vst[i] == 0) {
				q.push(i);
				vst[i] = true;
			}
		}
	}
	return wcc;
}

// judge weather v and u are connected
bool is_connected(const undirected_graph& g, int v, int u) {
	if (v == u)
		return true;
	int n = g.size();
	vector<bool> vst(n);
	queue<int> q;
	q.push(v);
	vst[v] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for(auto& i : g[v]) {
			if (i == u)
				return true;
			if (vst[i] == 0) {
				q.push(i);
				vst[i] = 1;
			}
		}
	}
	return false;
}

//static function
static community& __get_wcc(const undirected_graph& g, int node, community& wcc,
		vector<bool>& vst) {
	queue<int> q;
	q.push(node);
	vst[node] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		wcc.push_back(v);
		for(auto& i : g[v]) {
			if (vst[i] == 0) {
				q.push(i);
				vst[i] = true;
			}
		}
	}
	return wcc;
}

// get all weak connected component in undirected graph
communityV& get_wcc(const undirected_graph& g, communityV& cmtv) {
	int n = g.size();
	vector<bool> vst(n);
	cmtv.clear();
	for(int i = 0;i < n;i++) {
		if(!vst[i]) {
			cmtv.push_back(community());
			__get_wcc(g, i, *cmtv.rbegin(), vst);
		}
	}
	return cmtv;
}
#endif /* CONNECTION_H_ */
