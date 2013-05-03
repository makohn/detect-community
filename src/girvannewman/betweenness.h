/*
 * betweenness.h
 *
 *  Created on: Apr 13, 2013
 *      Author: ronaflx
 */

#ifndef BETWEENNESS_H_
#define BETWEENNESS_H_

#include <algorithm>
#include <vector>
using namespace std;

struct edgeBtw {
	int u, v;
	double weight;
	edgeBtw(int u = 0, int v = 0, double weight = 0) :
			u(u), v(v), weight(weight) {
	}
};
void edge_betweenness(const vector<vector<int> >& g, vector<edgeBtw>& btw);

#endif /* BETWEENNESS_H_ */
