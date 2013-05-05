/*
 * girvannewman.cpp
 *
 *  Created on: May 3, 2013
 *      Author: ronaflx
 */

#include "girvannewman.h"

typedef vector<vector<int> > communityV;

static void GirvanNewmanStep(NewmanGraph& g) {
	vector<edgeBtw> btw;
	while (true) {
		btw.clear();
		edge_betweenness(g.get_graph(), btw);
		if (btw.size() == 0) {
			return;
		}
		const int u = btw[0].u;
		const int v = btw[0].v;
		//remove edge
		g.remove_edge(u, v);
		g.remove_edge(v, u);
		if (is_connected(g.get_graph(), u, v) == false) {
			return;
		}
	}
}
static double GirvanNewmanModularity(NewmanGraph& graph, communityV& cmtyV,
		const vector<int>& origdgr, int m) {
	double Mod = 0;
	const vector<vector<int> >& g = graph.get_graph();
	get_wcc(g, cmtyV);
	int len = cmtyV.size();
	for (int i = 0; i < len; i++) {
		double ori_in_dgr = 0;
		double cur_in_dgr = 0;
		for (const auto& v : cmtyV[i]) {
			ori_in_dgr += origdgr[v];
			cur_in_dgr += g[v].size();
		}
		Mod += (cur_in_dgr - ori_in_dgr * ori_in_dgr / (2 * m));
	}
	return Mod / (2 * m);
}
static double GirvanNewman(NewmanGraph& graph, communityV& cmtyV) {
	cmtyV.clear();
	const vector<vector<int> >& g = graph.get_graph();
	int n = g.size();
	vector<int> dgree(n);
	for (int i = 0; i < n; i++) {
		dgree[i] = g[i].size();
	}
	const int e = accumulate(dgree.begin(), dgree.end(), 0) / 2;
	double bestQ = -1;
	communityV curCmty;
	for (int i = 0; i < e; i++) {
		GirvanNewmanStep(graph);
		double Q = GirvanNewmanModularity(graph, curCmty, dgree, e);
		if (bestQ < Q) {
			cmtyV.swap(curCmty);
			bestQ = Q;
		}
	}
	return bestQ;
}
static void write_community(const NewmanGraph& graph, const communityV& cmtys,
		FILE* filp) {
	int n = cmtys.size();
	for (int i = 0; i < n; i++) {
		for (const auto& v : cmtys[i]) {
			fprintf(filp, "%d %d\n", graph.get_node(v), i);
		}
	}
}


void girvanNewmanAlgo(const string& ifilename, const string& ofilename) {
	FILE * istream = fopen(ifilename.c_str(), "r");
	FILE * ostream = fopen(ofilename.c_str(), "w");

	NewmanGraph graph;
	communityV cmtyV;
	graph.read_graph(istream);

	const vector<vector<int> >& ref = graph.get_graph();
	int n = int(ref.size()), e = 0;
	for (int i = 0; i < n; i++) {
		e += int(ref[i].size());
	}
	e /= 2;

	printf("%s : %d %d\n", ifilename.c_str(), n, e);
	time_t start, end;
	time(&start);
	printf("%ld\n", start);
	double Q = GirvanNewman(graph, cmtyV);
	time(&end);
	printf("%ld\n", end);

	fprintf(ostream, "nodes : %d\nedges : %d\n", n, e);
	fprintf(ostream, "Modularity is %0.6f\n", Q);
	fprintf(ostream, "communities : %u\n", cmtyV.size());
	fprintf(ostream, "cost time : %.2lf\n", difftime(end, start));
	write_community(graph, cmtyV, ostream);

	fclose(istream);
	fclose(ostream);
	printf("%s over\n", ifilename.c_str());
}
