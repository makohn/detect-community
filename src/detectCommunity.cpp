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
undirected_graph g;
communityV cmtyV;
int main() {
	FILE * filp = fopen("data/0.edges", "r");
	read_graph(g, filp);
	fclose(filp);
	clock_t start = clock();
	double Q = GirvanNewman(g, cmtyV);
	printf("Modularity is %lf\n", Q);
	write_community(cmtyV, stdout);
	clock_t end = clock();
	printf("%lf\n", double(end - start) / CLOCKS_PER_SEC);
	return 0;
}
