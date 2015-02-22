/*
 *  edge_helper.h
 *  containertest
 *
 *  Created by Jon Lederman on 3/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef EDGE_HELPER_H
#define EDGE_HELPER_H
#include <vector>
#include "graph_def.h"
using namespace std;
void edge_union(vector<Edge> &first,  vector<Edge> &second, Graph &g, vector<Edge> &mergetarget);
#endif