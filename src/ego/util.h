/*
 * util.h
 *
 *  Created on: Apr 22, 2013
 *      Author: ronaflx
 */

#ifndef UTIL_H_
#define UTIL_H_
using std::vector;
using std::map;

void diff(int * first, int * second, int * to, int n);
void diff(const vector<int>& first, const vector<int>& second, int *to);
map<int, int>* make_sparse(int * f, int n);
double inp(map<int, int>* x, const double * y, int D);
double sgn(double x);
#endif /* UTIL_H_ */
