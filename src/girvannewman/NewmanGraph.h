/*
 * NewmanGraph.h
 *
 *  Created on: May 3, 2013
 *      Author: ronaflx
 */

#ifndef NEWMANGRAPH_H_
#define NEWMANGRAPH_H_

#include <map>
#include <vector>
#include <cstdio>
using namespace std;
class NewmanGraph {
public:
	NewmanGraph();
	virtual ~NewmanGraph();
	const vector<vector<int> >& get_graph();
	int get_node(int index) const;
	int get_index(int node) const;
	void add_edge(int u, int v);
	void remove_edge(int u, int v);
	void read_graph(FILE* filp);
	void write_graph(FILE* filp);
	void clear();
private:
	int add_node(int u);
	map<int, int> node_index_;
	map<int, int> index_node_;
	vector<vector<int> > g_;
};

#endif /* NEWMANGRAPH_H_ */
