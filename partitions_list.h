/*
 *  partitions_list.h
 *  Edmondstest
 *
 *  Created by Jon Lederman on 2/8/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef PARTITIONS_LIST_DEF_H
#define PARTITIONS_LIST_DEF_H
#include <map>
#include <vector>
#include <set>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include "graph_def.h"

using namespace std;

class partitions_list
{
public:
//	partitions_list(Graph const &G, Vertex_Indices const &vertex_indices, Weights const &weights)
//	:Graph(G), graph_vertices(vertex_indices), graph_weights(weights);

	partitions_list(Graph G, Vertex_Indices vertex_indices, Weights weights, int root, bool reversed);
	void insert(vector<vector<Edge > > elem, double key);
	vector<vector<Edge> > &get_entry(int entry);
	vector<Edge>& get_included (int entry);
	set<Edge> get_included1 (int entry);
	vector<Edge>& get_excluded(int entry);
	set<Edge> get_excluded1 (int entry);
	vector<Edge>& get_msa (int entry);
	vector<Edge> next_best_msa();
	set<Edge> get_msa1 (int entry);
	vector<vector<Edge> > &get_msas();
	void partition(int entry);
	void print(int entry, Graph G);
	bool is_empty();
	double get_weight (int entry);
	class no_msa {};
	EdgeCol get_cur_best_msa();
	bool exhausted_msa();
	
	
private:
	multimap<double, vector<vector<Edge> > > partitions;
	multimap<Weights::value_type, vector<set<Edge> > > new_partitions;
	vector<vector<Edge> > msas;
	vector<vector<int> > machine_msas;
	Graph graph;
	Vertex_Indices graph_vertices;
	Vertices the_vertices;
	Weights graph_weights;
	EdgeCol cur_best_msa;
	int root;
	bool is_reversed;
	vector<Edge> branching;
	
	
	
};

#endif