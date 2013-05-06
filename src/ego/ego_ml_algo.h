/*
 * ego_ML_algo.h
 *
 *  Created on: May 6, 2013
 *      Author: ronaflx
 */

#ifndef EGO_ML_ALGO_H_
#define EGO_ML_ALGO_H_
#include <string>
using namespace std;
namespace ego {
void EgoMLAlgo(int K, int lamda, int reps, int gradientReps, int improveReps,
		const string& ifilename, const string& ofilename);
}
#endif /* EGO_ML_ALGO_H_ */
