/*
 *  edge_helper.cpp
 *  containertest
 *
 *  Created by Jon Lederman on 3/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "edge_helper.h"

struct sort_pred
{
	Graph graph;
	sort_pred(const Graph &g): graph(g) 
	{
	}
	
	bool operator () (const Edge & left,  const Edge & right)
	{	
		if (source(left,graph)==source(right,graph))
			return target(left,graph) < target(right,graph);
		else 
			return source(left,graph)<source(right,graph);
		//	return weights[left]<weights[right];
		
	}
};

void edge_union(vector<Edge> &first,  vector<Edge> &second, Graph &g, vector<Edge> &mergetarget)
{
	
	
	sort(first.begin(), first.end(), sort_pred(g));
	sort(second.begin(), second.end(), sort_pred(g));
	
	set_union(first.begin(),first.end(), second.begin(), second.end(), back_inserter(mergetarget));
	
	//	return mergetarget;
	
	
}
