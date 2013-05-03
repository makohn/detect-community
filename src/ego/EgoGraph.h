/*
 * EgoGraph.h
 *
 *  Created on: Apr 22, 2013
 *      Author: ronaflx
 */

#ifndef EGOGRAPH_H_
#define EGOGRAPH_H_
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;
namespace ego {

class EgoGraph {
public:
	EgoGraph(const string& node_feature_file, const string& self_feature_file,
			const string& cluster_file, const string& edge_file, int which = 0);
	virtual ~EgoGraph();
	vector<set<int> > cluster_;
	set<pair<int, int> > edge_;
	map<pair<int, int>, map<int, int>*> edge_features_;
	vector<vector<int> > feature_;
	int num_nodes_;
	int num_features_;
	int get_node(int index) const;
	int get_index(int node) const;
private:
	map<int, int> node_index_;
	map<int, int> index_node_;
	vector<int> read_list(const string& self_feature);
	void read_node_feature(const string& node_feature_file,
			const string& self_feature_file);
	void read_edge(const string& edge_file);
	void read_cluster(const string& cluster_file);
};

} /* namespace ego */
#endif /* EGOGRAPH_H_ */
