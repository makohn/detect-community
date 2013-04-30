//============================================================================
// Name        : detectCommunity.cpp
// Author      : ronaflx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <ctime>
#include <time.h>
#include <algorithm>
using namespace std;
#include "girvannewman/connection.h"
#include "girvannewman/community.h"
#include "girvannewman/graphOperation.h"
#include "ego/Cluster.h"
#include "ego/EgoGraph.h"
undirected_graph g;
communityV cmtyV;
void test_ego(int K, int lamda, int reps, int gradientReps, int improveReps,
		const string& name) {
	cout << "run on file 698" << endl;
	const string nodeFeatureFile = name + ".feat";
	const string selfFeatureFile = name + ".egofeat";
	const string clusterFile = name + ".circles";
	const string edgeFile = name + ".edges";
	ego::EgoGraph graph(nodeFeatureFile, selfFeatureFile, clusterFile,
			edgeFile);
	ego::Cluster cluster(&graph);
	cluster.train(K, reps, gradientReps, improveReps, lamda, 1);
	// test code
	/*cout << graph.num_features_ << " " << graph.num_nodes_ << endl;
	for(const auto & i : graph.edge_features_) {
		printf("%d %d\n", i.first.first, i.first.second);
		for(const auto & j : *(i.second)) {
			printf("(%d, %d) ", j.first, j.second);
		}
		printf("\n");
	}*/
	cout << "run over" << endl;
}
int main() {
	/*FILE * filp = fopen("data/0.edges", "r");
	 read_graph(g, filp);
	 fclose(filp);
	 clock_t start = clock();
	 double Q = GirvanNewman(g, cmtyV);
	 printf("Modularity is %lf\n", Q);
	 write_community(cmtyV, stdout);
	 clock_t end = clock();
	 printf("%lf\n", double(end - start) / CLOCKS_PER_SEC);*/
	test_ego(3, 1, 25, 50, 5, "data/698");
	return 0;
}
