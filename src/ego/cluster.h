//============================================================================
// Name        : cluster.h
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : detect community in ego-network
//============================================================================

#ifndef SRC_EGO_CLUSTER_H_
#define SRC_EGO_CLUSTER_H_

#include <vector>
#include <set>

#include "./egograph.h"

namespace ego {

class Cluster {
    public:
        explicit Cluster(EgoGraph * graph);
        virtual ~Cluster();
        EgoGraph* graph_;
        int num_;
        double * theta_;
        double * alpha_;
        vector<set<int> > chat_;
        void train(int K, int reps, int gradientReps, int improveReps,
                double lamda, int whichLoss);
        double loglikelihood(const double * theta, const double * alpha,
                const vector<set<int> >& chat);
    private:
        std::set<int> minimize_graphcuts(int k, int improveReps, int *changed);
        void dl(double* dldt, double* dlda, int K, double lambda);
        void InitialSet(std::set<int>* _set, double* theta, double * alpha,
                int num_nodes, int num_feature);
        void GradientAscent(double * theta, double * alpha,
                vector<set<int> >& chat, double rate, int K, int reps,
                int lamda);
};

}  //  namespace ego
#endif  // SRC_EGO_CLUSTER_H_
