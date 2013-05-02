/*
 * EgoGraph.cpp
 *
 *  Created on: Apr 22, 2013
 *      Author: ronaflx
 */

#include "EgoGraph.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cassert>
#include "util.h"
namespace ego {

EgoGraph::EgoGraph(const string& node_feature_file,
		const string& self_feature_file, const string& cluster_file,
		const string& edge_file, int which) {
	read_node_feature(node_feature_file, self_feature_file);
	read_cluster(cluster_file);
	read_edge(edge_file);
	int * d = new int[num_features_];
	for (int i = 0; i < num_nodes_; i++) {
		for (int j = i + 1; j < num_nodes_; j++) {
			d[0] = 1;
			diff(feature_[i], feature_[j], d + 1);
			edge_features_[make_pair(i, j)] = make_sparse(d, num_features_);
		}
	}
	delete [] d;
}

EgoGraph::~EgoGraph() {
	for (const auto & feature : edge_features_) {
		delete feature.second;
	}
}
int EgoGraph::get_node(int index) {
	return index_node_[index];
}
int EgoGraph::get_index(int node) {
	return node_index_[node];
}

vector<int> EgoGraph::read_list(const string& self_feature) {
	istringstream sin(self_feature);
	vector<int> v;

	copy(istream_iterator<int>(sin), istream_iterator<int>(), back_inserter(v));
	return v;
}

void EgoGraph::read_node_feature(const string& node_feature_file,
		const string& self_feature_file) {
	// 暂时不需要和ego节点对比的feature
	// ifstream self_fin(self_feature_file);
	// node 0 is ego node, index is always 0
	// getline(self_fin, data);
	// feature_.push_back(read_list(data));
	// self_fin.close();
	ifstream node_fin(node_feature_file);
	string data;
	feature_.clear();
	// normal node
	while (getline(node_fin, data)) {
		//first element is node index
		vector<int> f = read_list(data);
		int cur_node = f[0], index = int(node_index_.size());
		node_index_[cur_node] = index;
		index_node_[index] = cur_node;
		f.erase(f.begin());
		feature_.push_back(f);
	}
	num_nodes_ = feature_.size();
	num_features_ = feature_[0].size() + 1;

	node_fin.close();
}

void EgoGraph::read_edge(const string& edge_file) {
	int u, v;

	edge_.clear();
	ifstream fin(edge_file);
	while (fin >> u >> v) {
		u = node_index_[u];
		v = node_index_[v];
		edge_.insert(make_pair(u, v));
	}
	fin.close();
}
void EgoGraph::read_cluster(const string& cluster_file) {
	ifstream fin(cluster_file);
	string data, name;
	int p;

	cluster_.clear();
	while (getline(fin, data)) {
		istringstream sin(data);
		sin >> name;
		set<int> cluster;
		while (sin >> p)
			cluster.insert(node_index_[p]);
		cluster_.push_back(cluster);
	}
	fin.close();
}
} /* namespace ego */
