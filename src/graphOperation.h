/*
 * graphOperation.h
 *
 *  Created on: Apr 14, 2013
 *      Author: ronaflx
 */

#ifndef GRAPHOPERATION_H_
#define GRAPHOPERATION_H_
#include "cmtyConfig.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

static void _remove_edge(undirected_graph& g, int v, int u) {
	auto i = find(g[v].begin(), g[v].end(), u);
	if (i != g[v].end()) {
		g[v].erase(i);
	}
}
void remove_edge(undirected_graph& g, int v, int u) {
	_remove_edge(g, v, u);
	_remove_edge(g, u, v);
}

void add_edge(undirected_graph& g, int v, int u) {
	if (v >= int(g.size()))
		g.resize(v + 1);
	if (u >= int(g.size()))
		g.resize(u + 1);
	g[u].push_back(v);
}
void read_graph(undirected_graph& g, istream& in) {
	int v, u;
	while (in >> v >> u) {
		v--, u--;
		add_edge(g, v, u);
	}
	for (int i = 0; i < int(g.size()); i++) {
		sort(g[i].begin(), g[i].end());
	}
}

void read_graph(undirected_graph& g, FILE* filp) {
	int u, v;
	while (fscanf(filp, "%d %d", &v, &u) == 2) {
		v--, u--;
		add_edge(g, v, u);
	}
	for (int i = 0; i < int(g.size()); i++) {
		sort(g[i].begin(), g[i].end());
	}
}

void write_graph(const undirected_graph& g, ostream& out) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		out << i;
		for (const auto & v : g[i]) {
			out << " " << v;
		}
		out << endl;
	}
}

void write_graph(const undirected_graph& g, FILE * filp) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		fprintf(filp, "%d", i);
		for (const auto & v : g[i]) {
			fprintf(filp, " %d", v);
		}
		fprintf(filp, "\n");
	}
}
void write_community(const communityV& cmtys, ostream& out) {
	int n = cmtys.size();
	for (int i = 0; i < n; i++) {
		for (const auto& v : cmtys[i]) {
			out << v << " " << i << endl;
		}
	}
}

void write_community(const communityV& cmtys, FILE* filp) {
	int n = cmtys.size();
	for (int i = 0; i < n; i++) {
		for (const auto& v : cmtys[i]) {
			fprintf(filp, "%d %d\n", v, i);
		}
	}
}
#endif /* GRAPHOPERATION_H_ */
