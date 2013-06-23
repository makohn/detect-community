//============================================================================
// Name        : profiletree.h
// Author      : ronaflx
// Version     : 
// Copyright   : 
// Description : 
//============================================================================

#ifndef SRC_EGO_PROFILETREE_H_
#define SRC_EGO_PROFILETREE_H_

#include <string>
#include <map>
#include <vector>
namespace ego {

class ProfileTree {
    public:
        ProfileTree(const std::string& feature_file);
        std::map<int, int>* Diff(const std::vector<int>& x,
                const std::vector<int>& y) const;
        void Diff(const std::vector<int>& node_x,
                const std::vector<int>& node_y, int *to);
        int get_num_feature();
        virtual ~ProfileTree();
    private:
        void BuildTree(const std::vector<std::string>& profile);
        void AddNode(const std::string& label, int& idx);
        std::vector<std::vector<int> > CompressFeature(
                const std::vector<int>& node);
        std::vector<std::string> feature_;
        std::map<std::string, int> label_index_;
        std::map<int, std::string> index_label_;
        int num_feature_;
};

}  //  namespace ego
#endif //  SRC_EGO_PROFILETREE_H_
