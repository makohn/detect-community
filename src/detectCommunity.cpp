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
using namespace std;
#include "connection.h"
#include "community.h"
#include "graphOperation.h"
undirected_graph g;
communityV cmtyV;
int main() {
	FILE * filp = fopen("data/0.edges", "r");
	read_graph(g, filp);
	fclose(filp);
	//clock_t start = clock();
	double Q = GirvanNewman(g, cmtyV);
	cout << Q << endl;
	//clock_t end = clock();
	/*printf("%d.%03d\n", (end - start) / CLOCKS_PER_SEC,
			(end - start) % CLOCKS_PER_SEC);*/
	return 0;
}
