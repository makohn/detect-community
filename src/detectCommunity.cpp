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
#include "ego/ego_ml_algo.h"
int main() {
	ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/698", "result/698.ML.data");
	//logger = fopen("res.out", "w");
	//test_ego(3, 1, 1, 50, 5, "data/698");
	//fclose(logger);
//	girvanNewmanAlgo("data/0.edges", "result/0.newman.data");
//	girvanNewmanAlgo("data/107.edges", "result/107.newman.data"); //too large > 1000
//	girvanNewmanAlgo("data/348.edges", "result/348.newman.data");
//	girvanNewmanAlgo("data/414.edges", "result/414.newman.data");
//	girvanNewmanAlgo("data/686.edges", "result/686.newman.data");
//	girvanNewmanAlgo("data/698.edges", "result/698.newman.data");
//	girvanNewmanAlgo("data/1684.edges", "result/1684.newman.data"); //too large > 700
//	girvanNewmanAlgo("data/1912.edges", "result/1912.newman.data"); //too large > 700
//	girvanNewmanAlgo("data/3437.edges", "result/3437.newman.data");
//	girvanNewmanAlgo("data/3980.edges", "result/3980.newman.data");
	return 0;
}
