/*
 * connection.h
 *
 *  Created on: Apr 10, 2013
 *      Author: ronaflx
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_
#include <vector>
using namespace std;
typedef vector<int> community;
typedef vector<community> communityV;

// get weak connected component though node
community& get_node_wcc(const vector<vector<int> >& g, int node,
		community& wcc);

// judge weather v and u are connected
bool is_connected(const vector<vector<int> >& g, int v, int u);

// get all weak connected component in undirected graph
communityV& get_wcc(const vector<vector<int> >& g, communityV& cmtv);
#endif /* CONNECTION_H_ */
