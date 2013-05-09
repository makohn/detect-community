//============================================================================
// Name        : egograph.h
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : class EgoGraph
//============================================================================

#ifndef SRC_EGO_EGOGRAPH_H_
#define SRC_EGO_EGOGRAPH_H_
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>

using std::string;
using std::set;
using std::map;
using std::pair;
using std::vector;
namespace ego {

class EgoGraph {
    public:
        EgoGraph(const string& node_feature_file,
                const string& self_feature_file, const string& cluster_file,
                const string& edge_file, int which = 0);
        virtual ~EgoGraph();
        vector<set<int> > cluster_;
        set<pair<int, int> > edge_;
        map<pair<int, int>, map<int, int>*> edge_features_;
        vector<vector<int> > feature_;
        int num_nodes_;
        int num_edges_;
        int num_features_;
        int GetNode(int index) const;
        int GetIndex(int node) const;
    private:
        map<int, int> node_index_;
        map<int, int> index_node_;
        vector<int> ReadList(const string& self_feature);
        void ReadNodeFeature(const string& node_feature_file,
                const string& self_feature_file);
        void ReadEdge(const string& edge_file);
        void ReadCluster(const string& cluster_file);
};

} /* namespace ego */
#endif  // SRC_EGO_EGOGRAPH_H_
