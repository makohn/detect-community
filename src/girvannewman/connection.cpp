/*
 * connection.cpp
 *
 *  Created on: May 3, 2013
 *      Author: ronaflx
 */


#include <queue>
#include <vector>
using namespace std;

typedef vector<int> community;
typedef vector<community > communityV;

// get weak connected component though node
community& get_node_wcc(const vector<vector<int> >& g, int node,
		community& wcc) {
	int n = g.size();
	vector<bool> vst(n);
	queue<int> q;
	q.push(node);
	vst[node] = 1;
	while (!q.empty()) {
		int v = q.front();
		wcc.push_back(v);
		q.pop();
		for (auto& i : g[v]) {
			if (vst[i] == 0) {
				q.push(i);
				vst[i] = true;
			}
		}
	}
	return wcc;
}

// judge weather v and u are connected
bool is_connected(const vector<vector<int> >& g, int v, int u) {
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
		for (auto& i : g[v]) {
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
static community& __get_wcc(const vector<vector<int> >& g, int node,
		community& wcc, vector<bool>& vst) {
	queue<int> q;
	q.push(node);
	vst[node] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		wcc.push_back(v);
		for (auto& i : g[v]) {
			if (vst[i] == 0) {
				q.push(i);
				vst[i] = true;
			}
		}
	}
	return wcc;
}

// get all weak connected component in undirected graph
communityV& get_wcc(const vector<vector<int> >& g, communityV& cmtv) {
	int n = g.size();
	vector<bool> vst(n);
	cmtv.clear();
	for (int i = 0; i < n; i++) {
		if (!vst[i]) {
			cmtv.push_back(community());
			__get_wcc(g, i, *cmtv.rbegin(), vst);
		}
	}
	return cmtv;
}

