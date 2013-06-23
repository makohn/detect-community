//============================================================================
// Name        : detectCommunity.cpp
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : detect community in ego-network
//============================================================================

#include <vector>
#include <ctime>
#include <cstdio>
#include <algorithm>

#include "girvannewman/girvannewman.h"
#include "ego/ego_ml_algo.h"
#include "ego/profiletree.h"
#ifndef EGO
#define EGO
#endif
int main() {
#ifdef EGO
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/0", "result/0.ML.data");
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/348", "result/348.ML.data");
    ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/414", "result/414.ML.data");
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/686", "result/686.ML.data");
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/698", "result/698.ML.data");
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/3437", "result/3437.ML.data");
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/3980", "result/3980.ML.data");
    // graph 107 is too large (#nodes > 1000)
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/107", "result/107.ML.data");
    // graph 1684 is too large (#node > 700)
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/1684", "result/1684.ML.data");
    // graph 1912 is too large (#node > 700)
    // ego::EgoMLAlgo(3, 1, 25, 50, 5, "data/1912", "result/1912.ML.data");
#else
    girvanNewmanAlgo("data/0.edges", "result/0.newman.data");
    // graph 107 is too large (#nodes > 1000)
    girvanNewmanAlgo("data/107.edges", "result/107.newman.data");
    girvanNewmanAlgo("data/348.edges", "result/348.newman.data");
    girvanNewmanAlgo("data/414.edges", "result/414.newman.data");
    girvanNewmanAlgo("data/686.edges", "result/686.newman.data");
    girvanNewmanAlgo("data/698.edges", "result/698.newman.data");
    // graph 1684 is too large (#node > 700)
    girvanNewmanAlgo("data/1684.edges", "result/1684.newman.data");
    // graph 1912 is too large (#node > 700)
    girvanNewmanAlgo("data/1912.edges", "result/1912.newman.data");
    girvanNewmanAlgo("data/3437.edges", "result/3437.newman.data");
    girvanNewmanAlgo("data/3980.edges", "result/3980.newman.data");
#endif
    return 0;
}
