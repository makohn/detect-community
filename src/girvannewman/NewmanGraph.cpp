/*
 * NewmanGraph.cpp
 *
 *  Created on: May 3, 2013
 *      Author: ronaflx
 */

#include "NewmanGraph.h"
#include <cstdio>
#include <algorithm>
using namespace std;
NewmanGraph::NewmanGraph() {
}

NewmanGraph::~NewmanGraph() {
}

const vector<vector<int> >& NewmanGraph::get_graph() {
	return g_;
}

int NewmanGraph::get_node(int index) const {
	auto i = index_node_.find(index);
	return i == index_node_.end() ? -1 : i->second;
}

int NewmanGraph::get_index(int node) const {
	auto i = node_index_.find(node);
	return i == node_index_.end() ? -1 : i->second;
}

void NewmanGraph::add_edge(int u, int v) {
	u = add_node(u);
	v = add_node(v);
	if (int(g_.size()) <= u)
		g_.resize(u + 1);
	if (int(g_.size()) <= v)
		g_.resize(v + 1);
	g_[u].push_back(v);
}
void NewmanGraph::remove_edge(int u, int v) {
	auto i = find(g_[u].begin(), g_[u].end(), v);
	if (i != g_[u].end()) {
		g_[u].erase(i);
	}
}
void NewmanGraph::read_graph(FILE* filp) {
	int u, v;
	clear();
	while (fscanf(filp, "%d %d", &v, &u) == 2) {
		add_edge(v, u);
	}
	for (int i = 0; i < int(g_.size()); i++) {
		sort(g_[i].begin(), g_[i].end());
	}
}
void NewmanGraph::write_graph(FILE * filp) {
	int n = g_.size();
	for (int i = 0; i < n; i++) {
		fprintf(filp, "%d", i);
		for (const auto & v : g_[i]) {
			fprintf(filp, " %d", v);
		}
		fprintf(filp, "\n");
	}
}
void NewmanGraph::clear() {
	g_.clear();
	node_index_.clear();
	index_node_.clear();
}

int NewmanGraph::add_node(int u) {
	auto i = node_index_.find(u);
	if (i != node_index_.end()) {
		return i->second;
	} else {
		int id = node_index_.size();
		node_index_[u] = id;
		index_node_[id] = u;
		return id;
	}
	//error
	return -1;
}
