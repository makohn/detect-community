/*
 * graph_match.cpp
 *
 *  Created on: May 6, 2013
 *      Author: ronaflx
 */
#include <set>
#include <vector>
#include <limits>
#include <algorithm>
#include "graph_match.h"

using namespace std;

int SetSimilarty(const set<int>& one, const set<int>& that) {
	int match = 0;
	for (const auto & i : one) {
		if (that.find(i) != that.end()) {
			match++;
		}
	}
	return match;
}

static vector<vector<int> > g;
static vector<int> lx, ly, my;
static vector<bool> visx, visy;
static const int INF = numeric_limits<int>::max() / 2;

static void Initial(int num_node) {
	g = vector<vector<int> >(num_node, vector<int>(num_node));
	my = vector<int>(num_node, -1);
	ly = vector<int>(num_node);
	lx = vector<int>(num_node);
	visy = vector<bool>(num_node);
	visx = vector<bool>(num_node);
}

static bool FindPath(int x, const int n) {
	visx[x] = true;
	for (int i = 0; i < n; i++) {
		if (!visy[i] && lx[x] + ly[i] == g[x][i]) {
			visy[i] = true;
			if (my[i] == -1 || FindPath(my[i], n)) {
				my[i] = x;
				return true;
			}
		}
	}
	return false;
}

static int SolveMatch(int n) {
	for (int i = 0; i < n; i++) {
		lx[i] = *max_element(g[i].begin(), g[i].end());
	}
	int dx, sum = 0;
	for (int i = 0; i < n; i++) {
		while (true) {
			fill(visx.begin(), visx.end(), false);
			fill(visy.begin(), visy.end(), false);
			if (FindPath(i, n)) {
				break;
			}
			dx = INF;
			for (int j = 0; j < n; j++) {
				if (!visx[j]) {
					continue;
				}
				for (int k = 0; k < n; k++) {
					if (visy[k]) {
						continue;
					}
					dx = min(dx, lx[j] + ly[k] - g[j][k]);
				}
			}
			for (int j = 0; j < n; j++) {
				if (visx[j]) {
					lx[j] -= dx;
				}
				if (visy[j]) {
					ly[j] += dx;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		sum += g[my[i]][i];
	}
	return sum;
}

int GraphMatch(const vector<set<int> >& one, const vector<set<int> >& that) {
	int n = int(one.size());
	int m = int(that.size());
	int num_node = max(n, m);
	Initial(num_node);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			g[i][j] = SetSimilarty(one[i], that[j]);
		}
	}
	return SolveMatch(num_node);
}
