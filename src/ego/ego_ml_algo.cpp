//============================================================================
// Name        : Ego_ML_algo.cpp
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : detect community in ego-network
//============================================================================

#include <set>
#include <vector>
#include <string>

#include "./ego_ml_algo.h"
#include "./graph_match.h"
#include "./cluster.h"

namespace ego {
static void PrintInfo(const Cluster& cluster, FILE * ostream, int K,
        double times) {
    const vector<set<int> >& one = cluster.chat_;
    const vector<set<int> >& that = cluster.graph_->cluster_;
    fprintf(ostream, "nodes : %d\n", cluster.graph_->num_nodes_);
    fprintf(ostream, "edges : %d\n", cluster.graph_->num_edges_);
    fprintf(ostream, "features : %d\n", cluster.graph_->num_features_);
    fprintf(ostream, "predict : %u\n", one.size());
    fprintf(ostream, "in fact : %u\n", that.size());
    for (size_t i = 0; i < one.size(); i++) {
        const set<int>& group = one[i];
        fprintf(ostream, "community %u, size : %u\n", i, group.size());
        for (const auto & index : group) {
            int person = cluster.graph_->GetNode(index);
            fprintf(ostream, "%d ", person);
        }
        fprintf(ostream, "\n");
    }
    double match = GraphMatch(one, that);
    double one_size = 0;
    double that_size = 0;
    for (const auto & c : one) {
        one_size += c.size();
    }
    for (const auto & c : that) {
        that_size += c.size();
    }
    double precision = match / one_size;
    double recall = match / that_size;
    double F1_score = 2 * recall * precision / (precision + recall);
    fprintf(ostream, "cost time = %.2lf\n", times);
    fprintf(ostream, "precision = %.6lf\n", precision);
    fprintf(ostream, "recall    = %.6lf\n", recall);
    fprintf(ostream, "F1-score  = %.6lf\n", F1_score);
}

void EgoMLAlgo(int K, int lamda, int reps, int gradientReps, int improveReps,
        const string& ifilename, const string& ofilename) {
    const string node_feature = ifilename + ".feat";
    const string self_feature = ifilename + ".egofeat";
    const string cluster_file = ifilename + ".circles";
    const string edge_file = ifilename + ".edges";
    const string feature_name = ifilename + ".featnames";
    time_t start, end;
    time(&start);
    ego::EgoGraph graph(node_feature, self_feature, cluster_file, edge_file,
            feature_name);
    printf("%d %d %d\n", graph.num_nodes_, graph.num_edges_,
            graph.num_features_);
    ego::Cluster cluster(&graph);
    cluster.train(K, reps, gradientReps, improveReps, lamda, 1);
    time(&end);
    FILE * ostream = fopen(ofilename.c_str(), "w");
    PrintInfo(cluster, ostream, K, difftime(end, start));
    fclose(ostream);
}
}  // namespace ego
