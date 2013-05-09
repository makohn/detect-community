//============================================================================
// Name        : graph_match.h
// Author      : ronaflx
// Version     : 1.0
// Copyright   : GNU GPL
// Description : detect community in ego-network
//============================================================================

#ifndef SRC_EGO_GRAPH_MATCH_H_
#define SRC_EGO_GRAPH_MATCH_H_

#include <vector>
#include <set>

int SetSimilarty(const std::set<int>& one, const std::set<int>& that);

int GraphMatch(const std::vector<std::set<int> >& one,
        const std::vector<std::set<int> >& that);
#endif  // SRC_EGO_GRAPH_MATCH_H_
