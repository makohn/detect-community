//============================================================================
// Name        : egograph.cpp
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : implement class EgoGraph
//============================================================================

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <vector>
#include <set>

#include "egograph.h"
#include "util.h"
#include "./profiletree.h"

using std::fill;
namespace ego {

EgoGraph::EgoGraph(const string& node_feature_file,
        const string& self_feature_file, const string& cluster_file,
        const string& edge_file, const string& feature_name) {
    ReadNodeFeature(node_feature_file, self_feature_file);
    ReadCluster(cluster_file);
    ReadEdge(edge_file);
    ProfileTree tree(feature_name);
    num_edges_ = static_cast<int>(edge_.size());
    num_nodes_ = static_cast<int>(feature_.size());
    num_features_ = tree.get_num_feature() + 1;
    int * d = new int[num_features_];
    for (int i = 0; i < num_nodes_; i++) {
        for (int j = i + 1; j < num_nodes_; j++) {
            d[0] = 1;
            tree.Diff(feature_[i], feature_[j], d + 1);
            edge_features_[std::make_pair(i, j)] = MakeSparse(d, num_features_);
        }
    }
    delete[] d;
}

EgoGraph::~EgoGraph() {
    for (const auto & feature : edge_features_) {
        delete feature.second;
    }
}
int EgoGraph::GetNode(int index) const {
    auto i = index_node_.find(index);
    return i == index_node_.end() ? -1 : i->second;
}
int EgoGraph::GetIndex(int node) const {
    auto i = node_index_.find(node);
    return i == node_index_.end() ? -1 : i->second;
}

vector<int> EgoGraph::ReadList(const string& self_feature) {
    std::istringstream sin(self_feature);
    vector<int> v;

    std::copy(std::istream_iterator<int>(sin), std::istream_iterator<int>(),
            std::back_inserter(v));
    return v;
}

void EgoGraph::ReadNodeFeature(const string& node_feature_file,
        const string& self_feature_file) {
    char data[10250];
    FILE * istream = fopen(node_feature_file.c_str(), "r");
    feature_.clear();
    // normal node
    while (fscanf(istream, "%[^\n]\n", data) == 1) {
        // first element is node index
        vector<int> f = ReadList(data);
        int cur_node = f[0], index = static_cast<int>(node_index_.size());
        node_index_[cur_node] = index;
        index_node_[index] = cur_node;
        f.erase(f.begin());
        feature_.push_back(f);
    }
    fclose(istream);
}

void EgoGraph::ReadEdge(const string& edge_file) {
    int u, v;
    edge_.clear();
    FILE * istream = fopen(edge_file.c_str(), "r");
    while (fscanf(istream, "%d %d", &u, &v) == 2) {
        u = node_index_[u];
        v = node_index_[v];
        edge_.insert(std::make_pair(u, v));
    }
    fclose(istream);
}
void EgoGraph::ReadCluster(const string& cluster_file) {
    FILE * istream = fopen(cluster_file.c_str(), "r");
    char data[10250];
    string name;
    int p;
    cluster_.clear();
    while (fscanf(istream, "%[^\n]\n", data) == 1) {
        std::istringstream sin(data);
        sin >> name;
        set<int> cluster;
        while (sin >> p)
            cluster.insert(node_index_[p]);
        cluster_.push_back(cluster);
    }
    fclose(istream);
}
} /* namespace ego */
