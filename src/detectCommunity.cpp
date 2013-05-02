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
#include "girvannewman/connection.h"
#include "girvannewman/community.h"
#include "girvannewman/graphOperation.h"
#include "ego/Cluster.h"
#include "ego/EgoGraph.h"
FILE * logger;
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
	print_info(cluster, logger);
}

int main() {
	/*undirected_graph g;
	 communityV cmtyV;
	 FILE * filp = fopen("data/0.edges", "r");
	 read_graph(g, filp);
	 fclose(filp);
	 clock_t start = clock();
	 double Q = GirvanNewman(g, cmtyV);
	 printf("Modularity is %lf\n", Q);
	 write_community(cmtyV, stdout);
	 clock_t end = clock();
	 printf("%lf\n", double(end - start) / CLOCKS_PER_SEC);*/
	logger = fopen("res.out", "w");
	test_ego(3, 1, 1, 50, 5, "data/698");
	fclose(logger);
	return 0;
}
