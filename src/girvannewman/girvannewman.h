/*
 * girvannewman.h
 *
 *  Created on: May 3, 2013
 *      Author: ronaflx
 */

#ifndef GIRVANNEWMAN_H_
#define GIRVANNEWMAN_H_
#include <vector>
#include <set>
using namespace std;

#include "NewmanGraph.h"
#include "connection.h"
#include "betweenness.h"
typedef vector<vector<int> > communityV;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000000
#endif

void girvanNewmanAlgo(const string& ifilename, const string& ofilename);

#endif /* GIRVANNEWMAN_H_ */
