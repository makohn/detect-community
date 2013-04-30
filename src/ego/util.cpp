/*
 * util.cpp
 *
 *  Created on: Apr 28, 2013
 *      Author: ronaflx
 */

#include <vector>
#include <map>
#include <cmath>
using std::vector;
using std::map;
static const double EPS = 1e-6;
void diff(int * first, int * second, int * to, int n) {
	for (int i = 0; i < n; i++) {
		to[i] = first[i] ^ second[i];
	}
}
void diff(const vector<int>& first, const vector<int>& second, int *to) {
	for (int i = 0; i < int(first.size()) && i < int(second.size()); i++) {
		to[i] = first[i] ^ second[i];
	}
}
map<int, int>* make_sparse(int * f, int n) {
	map<int, int>* res = new map<int, int>;
	for (int i = 0; i < n; i++) {
		if (f[i]) {
			(*res)[i] = f[i];
		}
	}
	return res;
}

double inp(map<int, int>* x, const double * y, int D) {
	double res = 0.0;
	for (const auto & it : *x) {
		res += it.second * y[it.first];
	}
	return res;
}

double sgn(double x) {
	if (std::abs(x) <= EPS)
		return 0.0;
	return x < 0 ? -x : x;
}
