//============================================================================
// Name        : detectCommunity.cpp
// Author      : ronaflx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <ctime>
#include <cstdio>
#include <time.h>
#include <algorithm>
using namespace std;
#include "girvannewman/girvannewman.h"
#include "ego/Cluster.h"
#include "ego/EgoGraph.h"
//FILE * logger;
void print_info(const ego::Cluster& cluster, FILE * log) {
	fprintf(log, "nodes : %d feature : %d\n", cluster.graph_->num_nodes_,
			cluster.graph_->num_features_);
	vector<set<int> > chat = cluster.chat_;
	for (size_t i = 0; i < chat.size(); i++) {
		const set<int>& group = chat[i];
		fprintf(log, "group %u\n", i + 1);
		fprintf(log, "size : %u\n", group.size());
		for (const auto & index : group) {
			int person = cluster.graph_->get_node(index);
			fprintf(log, "%d ", person);
		}
		fprintf(log, "\n");
	}
}

void test_ego(int K, int lamda, int reps, int gradientReps, int improveReps,
		const string& name) {
	const string nodeFeatureFile = name + ".feat";
	const string selfFeatureFile = name + ".egofeat";
	const string clusterFile = name + ".circles";
	const string edgeFile = name + ".edges";
	ego::EgoGraph graph(nodeFeatureFile, selfFeatureFile, clusterFile,
			edgeFile);
	ego::Cluster cluster(&graph);
	cluster.train(K, reps, gradientReps, improveReps, lamda, 1);
	//print_info(cluster, logger);
}
int main() {

	//logger = fopen("res.out", "w");
	//test_ego(3, 1, 1, 50, 5, "data/698");
	//fclose(logger);
	girvanNewmanAlgo("data/0.edges", "result/0.newman.data");
	girvanNewmanAlgo("data/107.edges", "result/107.newman.data");//too large
	girvanNewmanAlgo("data/348.edges", "result/348.newman.data");
	girvanNewmanAlgo("data/414.edges", "result/414.newman.data");
	girvanNewmanAlgo("data/686.edges", "result/686.newman.data");
	girvanNewmanAlgo("data/698.edges", "result/698.newman.data");
	girvanNewmanAlgo("data/1684.edges", "result/1684.newman.data");//too large
	girvanNewmanAlgo("data/1912.edges", "result/1912.newman.data");//too large
	girvanNewmanAlgo("data/3437.edges", "result/3437.newman.data");//too large
	girvanNewmanAlgo("data/3980.edges", "result/0.newman.data");

	return 0;
}
