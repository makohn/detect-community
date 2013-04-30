/*
 * Cluster.h
 *
 *  Created on: Apr 27, 2013
 *      Author: ronaflx
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_
#include "EgoGraph.h"

namespace ego {

class Cluster {
public:
	Cluster(EgoGraph * graph);
	virtual ~Cluster();
	EgoGraph* graph_;
	int num_;
	double * theta_;
	double * alpha_;
	vector<set<int> > chat_;
	void train(int K, int reps, int gradientReps, int improveReps, double lamda,
			int whichLoss);
	double loglikelihook(const double * theta, const double * alpha,
			const vector<set<int> >& chat);
private:
	std::set<int> minimize_graphcuts(int k, int improveReps, int& changed);
	void dl(double* dldt, double* dlda, int K, double lambda);
};

} /* namespace ego */
#endif /* CLUSTER_H_ */
