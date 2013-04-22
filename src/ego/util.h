/*
 * util.h
 *
 *  Created on: Apr 22, 2013
 *      Author: ronaflx
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <vector>
using std::vector;
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
		if(f[i]) res[i] = f[i];
	}
	return res;
}
#endif /* UTIL_H_ */
