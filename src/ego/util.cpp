//============================================================================
// Name        : util.cpp
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : detect community in ego-network
//============================================================================

#include <vector>
#include <map>
#include <cmath>
using std::vector;
using std::map;
static const double EPS = 1e-6;

void Diff(const vector<int>& first, const vector<int>& second, int *to) {
    int f_size = static_cast<int>(first.size());
    int s_size = static_cast<int>(second.size());
    for (int i = 0; i < f_size && i < s_size; i++) {
        to[i] = first[i] ^ second[i];
    }
}
map<int, int>* MakeSparse(int * f, int n) {
    map<int, int>* res = new map<int, int>;
    for (int i = 0; i < n; i++) {
        if (f[i]) {
            (*res)[i] = f[i];
        }
    }
    return res;
}

double InnerProduct(map<int, int>* x, const double * y, int D) {
    double res = 0.0;
    for (const auto & it : *x) {
        res += it.second * y[it.first];
    }
    return res;
}

double Sgn(double x) {
    if (std::abs(x) <= EPS) return 0.0;
    return x < 0 ? -x : x;
}
