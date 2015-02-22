/*
 *  partitions_list.cpp
 *  Edmondstest
 *
 *  Created by Jon Lederman on 2/8/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/properties.hpp>
#include <boost/foreach.hpp>
#include "partitions_list.h"
#include "edmonds_optimum_branching.hpp"
#include "stl_helpers.h"
//#include "graph_def.h"
#include "dfs_helpers.h"
#include "boost/graph/filtered_graph.hpp"

using namespace std;
 

partitions_list::partitions_list(Graph G, Vertex_Indices vertex_indices, Weights weights, int root, bool reversed)
:graph(G), graph_vertices(vertex_indices), graph_weights(weights), is_reversed(reversed), root(root)
{	
	//Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(graph))
	{
		the_vertices.push_back(v);
	}
	
	
	if (dfs(graph, the_vertices[root])==false) throw no_msa();
	
	
    // Find the maximum branching.
   // std::vector<Edge> branching;
	vector<Edge> empty;
 
	
	edmonds_optimum_branching<false, true, false>(graph,
												  empty,
												  empty,
                                                  graph_vertices,
                                                  graph_weights,
                                                  vertices(graph).first+root,
                                                  vertices(graph).first+root+1,
                                                  std::back_inserter(branching));
	
	msas.push_back(branching);
	std::cout<<"\nIn PL constuctor. Initial branching: \n";
	PRINT_EDGES(branching, graph);
	
	vector<vector<Edge > > elem(3);
	elem.insert(elem.begin(), empty);
	elem.insert(elem.begin()+1, empty);
	elem.insert(elem.begin()+2, branching);
	
	double tw=total_weight(weights, branching);
	
		
	//insert(elem, total_weight(weights, branching));
	 insert(elem, tw);
	
	//cur_best_msa=make_pair<double, vector<Edge> >(tw, branching);
	cur_best_msa=make_pair<double, vector<Edge> >(get_weight(0), get_msa(0));
	
};

vector<vector<Edge> >& partitions_list::get_entry(int entry)
{

  return partitions.begin()->second;
};

vector<Edge>& partitions_list::get_included (int entry)
{
	
  return *(partitions.begin()->second.begin());
	

}

set<Edge> partitions_list::get_included1 (int entry)
{
	
	return *(new_partitions.begin()->second.begin());
		
}


vector<Edge>& partitions_list::get_excluded (int entry)
{
	return *(partitions.begin()->second.begin()+1);
	
}

set<Edge> partitions_list::get_excluded1 (int entry)
{
	return *(new_partitions.begin()->second.begin());
}

vector<Edge> &partitions_list::get_msa (int entry)
{
	return *(partitions.begin()->second.begin()+2);
	
}

double partitions_list::get_weight (int entry)
{
	return (partitions.begin()->first);
	
}

set<Edge> partitions_list::get_msa1 (int entry)
{
	return *(new_partitions.begin()->second.begin()+2);
	
}


vector<vector<Edge> >& partitions_list::get_msas()
{
	return msas;
}
vector<Edge> partitions_list::next_best_msa()
{
	return(*msas.begin());
}

EdgeCol partitions_list::get_cur_best_msa()
{
	return cur_best_msa;
}

void partitions_list::partition(int entry)
{
	
	//Get best MSA	
	vector<Edge> included=get_included(0);
	vector<Edge> excluded=get_excluded(0);
	vector<Edge> msa=get_msa(0);
	vector<vector<Edge > > element(3);
	vector<Edge> mergetarget;
	Weights::value_type tw;
	//mergetarget.clear();
	vector<Edge> open;
	
	
	sort(msa.begin(), msa.end(), sort_pred(graph));
	msas.push_back(msa);
	std::cout<<"\nMSAS size is: "<<msas.size()<<"\n"; 
	std::cout<<"Putting on MSAS list now is: \n";
	PRINT_EDGES(msa, graph);
	//std::cout<<"\n";
	cout<<" with total weight: "<<get_weight(0)<<"\n";
		
	
	//Remove best MSA partition
	partitions.erase(partitions.begin());
	
	edge_difference(msa, included, graph, open);
	
	//Partition removed partition by best MSA
	vector<Edge>::iterator pos;
	for (pos=open.begin(); pos!=open.end(); ++pos) 
	{	
		
		excluded.push_back(*pos);
		
				
		part_graph filter(graph,included,excluded);
		filtered_graph<Graph, part_graph> fg(graph, filter);
		
		
		if (dfs(fg, the_vertices[root])==true)
		{
		branching.clear();
		
	
		
		edmonds_optimum_branching<false, true, false>(graph,
														  included,
														  excluded,
														  graph_vertices,
														  graph_weights,
														  vertices(graph).first+root,
														  vertices(graph).first+root+1,
														  std::back_inserter(branching));
			
			
		//write
		element.insert(element.begin(),included);
		element.insert(element.begin()+1, excluded);
		element.insert(element.begin()+2, branching);
		
		
		tw=total_weight(graph_weights, branching);
			
	
		partitions.insert(make_pair(tw, element));
		//cur_best_msa=make_pair<double, vector<Edge> >(get_weight(0), get_msa(0));
		
		tw=0;
		}
		
		//update

		edge_union(included, *pos, graph, mergetarget);
		included.clear();
		included=mergetarget;
		excluded.erase(excluded.end());
		element.clear();
		mergetarget.clear();
		//cout<<"partitioning";
	}
	
	if (!partitions.empty())
	{
	cur_best_msa=make_pair<double, vector<Edge> >(get_weight(0), get_msa(0));
	//std::cout<<"Updating best msa";
	}	
}


void partitions_list::print(int entry, Graph G)
{
	multimap<double, vector<vector<Edge> > >::iterator pos;
	for (pos=partitions.begin() ; pos!=partitions.end() ; ++pos) 
	{
	cout<<"\nTotal weight: "<<pos->first<<"\n";
	cout<<"\n\nIncluded Edges:\n";
	PRINT_EDGES(*(pos->second.begin()), G);
	cout<<"\n\nExcluded Edges:\n";
	PRINT_EDGES(*(pos->second.begin()+1), G);
	cout<<"\n\nMSA:\n";
	PRINT_EDGES(*(pos->second.begin()+2), G);

	}
	cout<<"\n=========================================\n";
	cout<<"MSA's:\n";
	vector<vector<Edge > >::iterator pos1;
	for (pos1=msas.begin() ; pos1!=msas.end() ; ++pos1) 
	{
		
		PRINT_EDGES(*pos1,G);
		cout<<"\n";
		
	}
	
}


void partitions_list::insert(vector<vector<Edge > > elem, double key)
{
	partitions.insert(make_pair(key, elem));
	
}


bool partitions_list::is_empty()
{
	return partitions.empty();
}


bool partitions_list::exhausted_msa()
{
	return partitions.empty();
}