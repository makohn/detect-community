/*
 * community.h
 *
 *  Created on: Apr 14, 2013
 *      Author: ronaflx
 */

#ifndef COMMUNITY_H_
#define COMMUNITY_H_
#include <algorithm>
#include <numeric>
using namespace std;
#include "cmtyConfig.h"
#include "connection.h"
#include "betweenness.h"
#include "graphOperation.h"
static void GirvanNewmanStep(undirected_graph& g) {
	vector<edgeBtw> btw;
	while (true) {
		btw.clear();
		edge_betweenness(g, btw);
		if (btw.size() == 0) {
			return;
		}
		const int u = btw[0].u;
		const int v = btw[0].v;
		//remove edge
		remove_edge(g, u, v);
		if (is_connected(g, u, v) == false) {
			return;
		}
	}
}
static double GirvanNewmanModularity(undirected_graph& g, communityV& cmtyV,
		const vector<int>& origdgr, int edge) {
	double Mod = 0;
	get_wcc(g, cmtyV);
	int len = cmtyV.size();
	for (int i = 0; i < len; i++) {
		double ori_in_dgr = 0;
		double cur_in_dgr = 0;
		for (const auto& v : cmtyV[i]) {
			ori_in_dgr += origdgr[v];
			cur_in_dgr += g[v].size();
		}
		Mod += (cur_in_dgr - ori_in_dgr * ori_in_dgr / (2 * edge));
	}
	return Mod / (2 * edge);
}
double GirvanNewman(undirected_graph& g, communityV& cmtyV) {
	cmtyV.clear();
	int n = g.size();
	vector<int> dgree(n);
	for (int i = 0; i < n; i++) {
		dgree[i] = g[i].size();
	}
	const int e = accumulate(dgree.begin(), dgree.end(), 0) / 2;
	double bestQ = -1;
	communityV curCmty;
	for(int i = 0;i < e;i++) {
		GirvanNewmanStep(g);
		double Q = GirvanNewmanModularity(g, cmtyV, dgree, e);
		if (bestQ < Q) {
			cmtyV.swap(curCmty);
			bestQ = Q;
		}
	}
	return bestQ;
}

#endif /* COMMUNITY_H_ */
