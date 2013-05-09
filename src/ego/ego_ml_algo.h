//============================================================================
// Name        : Ego_ML_algo.h
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : detect community in ego-network
//============================================================================

#ifndef SRC_EGO_EGO_ML_ALGO_H_
#define SRC_EGO_EGO_ML_ALGO_H_
#include <string>
namespace ego {
void EgoMLAlgo(int K, int lamda, int reps, int gradientReps, int improveReps,
        const std::string& ifilename, const std::string& ofilename);
}
#endif  // SRC_EGO_EGO_ML_ALGO_H_
