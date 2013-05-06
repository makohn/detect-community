/*
 * graph_match.h
 *
 *  Created on: May 6, 2013
 *      Author: ronaflx
 */

#ifndef GRAPH_MATCH_H_
#define GRAPH_MATCH_H_

#include <vector>
#include <set>
using namespace std;

int SetSimilarty(const set<int>& one, const set<int>& that);

int GraphMatch(const vector<set<int> >& one, const vector<set<int> >& that);
#endif /* GRAPH_MATCH_H_ */
