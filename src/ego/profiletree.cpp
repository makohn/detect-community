//============================================================================
// Name        : profiletree.cpp
// Author      : ronaflx
// Version     : 
// Copyright   : 
// Description : 
//============================================================================

#include "profiletree.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <sstream>
namespace ego {

ProfileTree::ProfileTree(const std::string& feature_file) {
    std::ifstream fin(feature_file);
    std::string buffer, type;
    int num;
    while (fin >> num) {
        fin >> buffer >> type >> num;
        std::ostringstream sout;
        sout << buffer << type << num;
        std::string feature = sout.str();
        feature_.push_back(feature);
    }
    fin.close();
    BuildTree(feature_);
}

void ProfileTree::Diff(const std::vector<int>& node_x,
        const std::vector<int>& node_y, int *to) {
    const auto feature_x = CompressFeature(node_x);
    const auto feature_y = CompressFeature(node_y);
    for(int i = 0;i < num_feature_;i++) {
        to[i] = (feature_x[i] != feature_y[i]);
    }
}
int ProfileTree::get_num_feature() {
    return num_feature_;
}

ProfileTree::~ProfileTree() {
}

void ProfileTree::BuildTree(const std::vector<std::string>& profiles) {
    int num_profile = static_cast<int>(profiles.size());
    int num_tree_node = 0;
    for (int i = 0; i < num_profile; i++) {
        AddNode(profiles[i], num_tree_node);
    }
    for (int i = 0; i < num_profile; i++) {
        const std::string& profile = profiles[i];
        std::string::size_type pos = std::string::npos;
        while ((pos = profile.find(';', pos + 1)) != std::string::npos) {
            std::string label = profile.substr(0, pos);
            AddNode(label, num_tree_node);
        }
    }
    num_feature_ = static_cast<int>(label_index_.size()) - num_profile;
#ifdef DEBUG
    for (int i = 0; i < num_feature_; i++) {
        printf("%s\n", index_label_[i + num_profile].c_str());
    }
#endif
}
void ProfileTree::AddNode(const std::string& label, int & idx) {
    if (label_index_.find(label) == label_index_.end()) {
        label_index_[label] = idx;
        index_label_[idx] = label;
        idx++;
    }
}
std::vector<std::vector<int> > ProfileTree::CompressFeature(
        const std::vector<int>& node) {
    std::vector<std::vector<int> > compressed(num_feature_);
    int num_profile = static_cast<int>(feature_.size());
    for (int i = 0; i < num_profile; i++) {
        int value = node[i];
        const std::string& profile = feature_[i];
        std::string::size_type pos = std::string::npos;
        while ((pos = profile.find(';', pos + 1)) != std::string::npos) {
            int index = label_index_[profile.substr(0, pos)];
            compressed[index - num_profile].push_back(value);
        }
    }
    return compressed;
}
}  //  namespace ego
