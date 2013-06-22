//============================================================================
// Name        : util.h
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : detect community in ego-network
//============================================================================

#ifndef SRC_EGO_UTIL_H_
#define SRC_EGO_UTIL_H_
#include <map>
#include <vector>

void Diff(int * first, int * second, int * to, int n);
void Diff(const std::vector<int>& first, const std::vector<int>& second,
        int *to);
std::map<int, int>* MakeSparse(int * f, int n);
double InnerProduct(std::map<int, int>* x, const double * y, int D);
double Sgn(double x);
#endif  // SRC_EGO_UTIL_H_
