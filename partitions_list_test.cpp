//  (C) Copyright Gennadiy Rozental 2001-2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile: const_string_test.cpp,v $
//
//  Version     : $Revision: 49313 $
//
//  Description : simple string class test
// ***************************************************************************

#define BOOST_TEST_MODULE partitions_list test
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <utility>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/foreach.hpp>
#include "partitions_list.h"
#include "vector_helper.h"
#include "stl_helpers.h"
#include "graph_def.h"
#include "edge_helper.h"
#include "dfs_helpers.h"
#include "boost/graph/filtered_graph.hpp"
#include "boost/graph/reverse_graph.hpp"
#include "combination_helpers.h"

using namespace std;


BOOST_AUTO_TEST_CASE( constructors_test )
{
    
	vector<pair<int, int> > myvector1;
	vector<vector<pair<int, int> > > part;
	pair<int,int> my_pair1=make_pair(1,2);
	pair<int,int> my_pair2=make_pair(3,4);
	pair<int,int> my_pair3=make_pair(5,6);
	myvector1.push_back(my_pair1);
	myvector1.push_back(my_pair2);
	myvector1.push_back(my_pair3);
	
	vector<pair<int, int> > myvector2;
	pair<int,int> my_pair4=make_pair(7,8);
	pair<int,int> my_pair5=make_pair(9,10);
	pair<int,int> my_pair6=make_pair(11,12);
	myvector2.push_back(my_pair4);
	myvector2.push_back(my_pair5);
	myvector2.push_back(my_pair6);
	
	vector<pair<int, int> > myvector3;
	pair<int,int> my_pair7=make_pair(13,14);
	pair<int,int> my_pair8=make_pair(15,16);
	pair<int,int> my_pair9=make_pair(17,18);
	myvector3.push_back(my_pair7);
	myvector3.push_back(my_pair8);
	myvector3.push_back(my_pair9);
	
	
	part.push_back(myvector1);
	part.push_back(myvector2);
	part.push_back(myvector3);
//	pl.insert(part,1);
	
//	vector<pair<int, int> > return_vector=pl.get_included(1);
	
// vector<pair< int, int> >::iterator vecit=return_vector.begin();
//	cout<<vecit->second;
//	vecit++;
//	cout<<vecit->second;
	
//	PRINT_ELEMENTS<vector<pair< int, int> > > (return_vector);

}

BOOST_AUTO_TEST_CASE(union_test)
{
	
	vector<pair<int, int> > myvector1;
	vector<vector<pair<int, int> > > part;
	pair<int,int> my_pair1=make_pair(1,2);
	pair<int,int> my_pair2=make_pair(3,4);
	pair<int,int> my_pair3=make_pair(5,6);
	pair<int,int> my_pair7=make_pair(7,8);
	pair<int,int> my_pair8=make_pair(7,9);
	myvector1.push_back(my_pair1);
	myvector1.push_back(my_pair2);
	myvector1.push_back(my_pair3);
	myvector1.push_back(my_pair7);
	myvector1.push_back(my_pair8);
	
	vector<pair<int, int> > myvector2;
	pair<int,int> my_pair4=make_pair(7,8);
	pair<int,int> my_pair9=make_pair(7,7);
	pair<int,int> my_pair5=make_pair(9,10);
	pair<int,int> my_pair6=make_pair(11,12);
	myvector2.push_back(my_pair4);
	myvector2.push_back(my_pair5);
	myvector2.push_back(my_pair6);
	myvector2.push_back(my_pair9);
	
	vector<pair<int, int> > mergetarget;
	vecunion(myvector1, myvector2, mergetarget);
	
PRINT_ELEMENTS<vector<pair< int, int> > > (mergetarget);

}


BOOST_AUTO_TEST_CASE(paritition_test)
{
	// Graph with N vertices    
	
	const int N = 4;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 3.0, G);
	add_edge(the_vertices[0], the_vertices[2], 1.5, G);
	add_edge(the_vertices[0], the_vertices[3], 1.8, G);
	add_edge(the_vertices[1], the_vertices[2], 4.3, G);
	add_edge(the_vertices[2], the_vertices[3], 2.2, G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	partitions_list pl(G, vertex_indices, weights, false); 
	
}

BOOST_AUTO_TEST_CASE(edge_union_test)
{
	std::cout<<"\n=====EDGE UNION TEST BEGIN=====\n";
	vector<Edge> edgevector1;
	vector<Edge> edgevector2;
	const int N = 4;
	Graph H(N);
	Edge cur_edge1, cur_edge2, cur_edge3;
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(H))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	cur_edge1=add_edge(the_vertices[0], the_vertices[1], 3.0, H).first;
	edgevector1.push_back(cur_edge1);
	//edgevector1.push_back(cur_edge1);
	
	
	
	cur_edge2=add_edge(the_vertices[0], the_vertices[2], 1.5, H).first;
	edgevector1.push_back(cur_edge2);
	
	cur_edge3=add_edge(the_vertices[0], the_vertices[3], 1.8, H).first;
	edgevector1.push_back(cur_edge3);
	edgevector2.push_back(cur_edge3);
	
	

	
	//edgevector2.push_back(cur_edge3);
	
	//cur_edge=add_edge(the_vertices[0], the_vertices[2], 1.5, H).first;
	//edgevector2.push_back(cur_edge);
	/*edgevector2.push_back(add_edge(the_vertices[0], the_vertices[3], 1.8, H).first);
	edgevector1.push_back(add_edge(the_vertices[1], the_vertices[2], 4.3, H).first);
	add_edge(the_vertices[2], the_vertices[3], 2.2, H);*/
	
	vector<Edge> mergetarget;
	
	std::cout<<"\nFirst before sort:\n";
	PRINT_EDGES(edgevector1, H);
	
	
	std::cout<<"\nSecond before sort:\n";
	PRINT_EDGES(edgevector2, H);
	
	edge_union(edgevector1, edgevector2, H, mergetarget);
	
	std::cout<<"\nFirst after sort:\n";
	PRINT_EDGES(edgevector1, H);
	
	
	std::cout<<"\nSecond after sort:\n";
	PRINT_EDGES(edgevector2, H);
	
	
	std::cout<<"\nMergeTarget:\n";
	PRINT_EDGES(mergetarget, H);
	
	mergetarget.clear();

	
	edge_union(edgevector1, cur_edge3, H, mergetarget);
	
	std::cout<<"\nMergeTarget:\n";
	PRINT_EDGES(mergetarget, H);
	
	
	std::cout<<"\n=====EDGE UNION TEST END=====\n";
	
	
}

BOOST_AUTO_TEST_CASE(dfs_test)
{
	
	// Graph with N vertices    
	
	const int N = 4;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 3.0, G);
	add_edge(the_vertices[0], the_vertices[2], 1.5, G);
	add_edge(the_vertices[0], the_vertices[3], 1.8, G);
	add_edge(the_vertices[1], the_vertices[2], 4.3, G);
	add_edge(the_vertices[2], the_vertices[3], 2.2, G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	dfs(G, the_vertices[0]); 
	
	
	//now let's filter
	vector<Edge> inc, exc;
	//exc.push_back(edge(the_vertices[0],the_vertices[3],G).first);
	exc.push_back(edge(the_vertices[1],the_vertices[2],G).first);
	exc.push_back(edge(the_vertices[0],the_vertices[2],G).first);
	//inc.push_back(edge(the_vertices[2],the_vertices[3],G).first);
	inc.push_back(edge(the_vertices[0],the_vertices[1],G).first);
	inc.push_back(edge(the_vertices[0],the_vertices[3],G).first);
	
	part_graph filter(G,inc,exc);


	
	filtered_graph<Graph, part_graph> fg(G, filter);
		std::vector < default_color_type > color_map(num_vertices(fg));
	std::vector < Edge > back_edges;
	
//	if (dfs(fg, the_vertices[0])==false)
//		std::cout<<"Not reachable.";
	
}


BOOST_AUTO_TEST_CASE(all_msa_test)
{
	
	// Graph with N vertices    
	
	const int N = 4;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 3.0, G);
	add_edge(the_vertices[0], the_vertices[2], 1.5, G);
	add_edge(the_vertices[0], the_vertices[3], 1.8, G);
	add_edge(the_vertices[1], the_vertices[2], 4.3, G);
	add_edge(the_vertices[2], the_vertices[3], 2.2, G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	EdgeCol best;
	partitions_list pl(G, vertex_indices, weights, false); 
	while (!pl.is_empty())
	{
		pl.print(0,G);
		pl.partition(0);
		best=pl.get_cur_best_msa();
		std::cout<<"\nCur best MSA is:\n";
		PRINT_EDGES(best.second, G);
		std::cout<<"\nwith a total weight of: "<<best.first<<"\n";
	}
	
	pl.print(0,G);
}

BOOST_AUTO_TEST_CASE(reverse_graph_test)
{
	
	// Graph with N vertices    
	
	const int N = 4;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 3.0, G);
	add_edge(the_vertices[0], the_vertices[2], 1.5, G);
	add_edge(the_vertices[0], the_vertices[3], 1.8, G);
	add_edge(the_vertices[1], the_vertices[2], 4.3, G);
	add_edge(the_vertices[2], the_vertices[3], 2.2, G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	
	
	//reverse_graph<Graph> H(G);
	
	Graph H=graph_reverse(G);
	Weights weightsH =get(boost::edge_weight_t(), H);
	Vertex_Indices vertex_indicesH =get(boost::vertex_index_t(), H);
	
	//Print the graph (or rather the edges of the graph).
	std::cout << "This is the reverse graph:\n";
	BOOST_FOREACH (Edge e, edges(H))
	{
		std::cout << "(" << boost::source(e, H) << ", "
		<< boost::target(e, H) << ")\t"
		<< get(weightsH, e) << "\n";
	}
	
	//Vertex_Indices vertex_indicesH =get(boost::vertex_index_t(), H);
	//Weights weightsH =get(boost::edge_weight_t(), H);
	try
	{
	partitions_list p2(H, vertex_indicesH, weightsH, true); 
		
	while (!p2.is_empty())
		{
		p2.print(0,H);
		p2.partition(0);
		}
	}
	catch(partitions_list::no_msa)
	{
		std::cout<<"No MSA";
	//	exit(1);
	}
	
	BOOST_CHECK_THROW(partitions_list p2(H, vertex_indicesH, weightsH, true), partitions_list::no_msa);
	
	
	
}



BOOST_AUTO_TEST_CASE(comb_in_out_test)
{
	
	// Graph with N vertices    
	
	const int N = 4;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 3.0, G);
	add_edge(the_vertices[0], the_vertices[2], 1.5, G);
	add_edge(the_vertices[0], the_vertices[3], 1.8, G);
	add_edge(the_vertices[1], the_vertices[2], 4.3, G);
	add_edge(the_vertices[2], the_vertices[3], 2.2, G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	EdgeCol best;
	partitions_list pl(G, vertex_indices, weights, false); 
	while (!pl.is_empty())
	{
		pl.print(0,G);
		pl.partition(0);
		best=pl.get_cur_best_msa();
		std::cout<<"\nCur best MSA is:\n";
		PRINT_EDGES(best.second, G);
		std::cout<<"\nwith a total weight of: "<<best.first<<"\n";
	}
	
	pl.print(0,G);
	//best.first=100;
	EdgeCol fake_best;
	vector<Edge> singleton;
	//singleton.push_back(edge(the_vertices[0],the_vertices[1],G).first);
	
	singleton.push_back(edge(the_vertices[0],the_vertices[2],G).first);
	
	vector<vector<Edge> > temp=pl.get_msas();
	comb_in_out(best, singleton, temp, G, false);
	
	cout<<"\nBest weight: "<<best.first;
	cout<<"\nBest edges: ";
	PRINT_EDGES(best.second, G);
}

BOOST_AUTO_TEST_CASE(flip_edges_test)
{
	
	// Graph with N vertices    
	
	const int N = 3;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 277317, G);
	add_edge(the_vertices[1], the_vertices[0], 26247, G);
	add_edge(the_vertices[0], the_vertices[2], 478726, G);
	add_edge(the_vertices[2], the_vertices[0], 930382, G);
	add_edge(the_vertices[1], the_vertices[2], 370287, G);
	add_edge(the_vertices[2], the_vertices[1], 112344, G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	EdgeCol best, best1;
	partitions_list pl(G, vertex_indices, weights, false); 
	while (!pl.is_empty())
	{
		pl.print(0,G);
		pl.partition(0);
		best=pl.get_cur_best_msa();
		std::cout<<"\nCur best MSA is:\n";
		PRINT_EDGES(best.second, G);
		std::cout<<"\nwith a total weight of: "<<best.first<<"\n";
	}
	
	
	Graph H=graph_reverse(G);
	Weights weightsH =get(boost::edge_weight_t(), H);
	Vertex_Indices vertex_indicesH =get(boost::vertex_index_t(), H);
	
	//Print the graph (or rather the edges of the graph).
	std::cout << "This is the reverse graph:\n";
	BOOST_FOREACH (Edge e, edges(H))
	{
		std::cout << "(" << boost::source(e, H) << ", "
		<< boost::target(e, H) << ")\t"
		<< get(weightsH, e) << "\n";
	}
	
	partitions_list p2(H, vertex_indicesH, weightsH, true); 
	while (!p2.is_empty())
	{
		p2.print(0,G);
		p2.partition(0);
		best1=p2.get_cur_best_msa();
		std::cout<<"\nCur best MSA in reverse is:\n";
		PRINT_EDGES(best1.second, H);
		std::cout<<"\nwith a total weight of: "<<best.first<<"\n";
	}
	
	
	
	best1=p2.get_cur_best_msa();
	vector<Edge> edges=best1.second;
	vector<Edge> rev_edges=flip_edges(edges, G);
	cout<<"\nFlipped Edges:\n";
	PRINT_EDGES(rev_edges, G);
	
	EdgeCol last;
	last=edge_union(best.second, rev_edges, G); 
	std::cout<<"\nAfter combining:\n";
	PRINT_EDGES(last.second, G);
	std::cout<<"\nwith a total weight of: "<<last.first;
}

BOOST_AUTO_TEST_CASE(find_SCSS_test)
{
	
	// Graph with N vertices    
	
	const int N = 3;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 277317, G);
	add_edge(the_vertices[1], the_vertices[0], 26247, G);
	add_edge(the_vertices[0], the_vertices[2], 478726, G);
	add_edge(the_vertices[2], the_vertices[0], 930382, G);
	add_edge(the_vertices[1], the_vertices[2], 370287, G);
	add_edge(the_vertices[2], the_vertices[1], 112344, G);
	EdgeCol result=find_scss(G);
	
	std::cout<<"\nAnd the final result is:\n";
	PRINT_EDGES(result.second, G);
	std::cout<<"\nWith a total weight of: "<<result.first;

}

BOOST_AUTO_TEST_CASE(find_SCSS_test1)
{
	
	// Graph with N vertices    
	
	const int N = 4;
	Graph J(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(J))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 619, J);
	add_edge(the_vertices[0], the_vertices[2], 837, J);
	add_edge(the_vertices[0], the_vertices[3], 765, J);
	add_edge(the_vertices[1], the_vertices[0], 850, J);
	add_edge(the_vertices[1], the_vertices[2], 69, J);
	add_edge(the_vertices[1], the_vertices[3], 106, J);
	
	add_edge(the_vertices[2], the_vertices[0], 1, J);
	add_edge(the_vertices[2], the_vertices[1], 841, J);
	add_edge(the_vertices[2], the_vertices[3], 877, J);
	add_edge(the_vertices[3], the_vertices[0], 117, J);
	add_edge(the_vertices[3], the_vertices[1], 580, J);
	add_edge(the_vertices[3], the_vertices[2], 873, J);
	
	
	
	EdgeCol result=find_scss(J);
	
	std::cout<<"\nAnd the final result is:\n";
	PRINT_EDGES(result.second, J);
	std::cout<<"\nWith a total weight of: "<<result.first;
	
}


BOOST_AUTO_TEST_CASE(graph_reverse_vertex_test)
{
	std::cout<<"\n=========================================================\n";
	std::cout<<"\nREVERSE GRAPH TESTING FOR VERTEX . . . TESTING FOR VERTEX\n";
	// Graph with N vertices    
	
	const int N = 4;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 3.0, G);
	add_edge(the_vertices[0], the_vertices[2], 1.5, G);
	add_edge(the_vertices[0], the_vertices[3], 1.8, G);
	add_edge(the_vertices[1], the_vertices[2], 4.3, G);
	add_edge(the_vertices[2], the_vertices[3], 2.2, G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	//Now do a reverse graph
	Graph H=graph_reverse(G);
	Weights weightsH =get(boost::edge_weight_t(), H);
	Vertex_Indices vertex_indicesH =get(boost::vertex_index_t(), H);
	
	//Print the graph (or rather the edges of the graph).
	std::cout << "This is the reverse graph:\n";
	BOOST_FOREACH (Edge e, edges(H))
	{
		std::cout << "(" << boost::source(e, H) << ", "
		<< boost::target(e, H) << ")\t"
		<< get(weightsH, e) << "\n";
	}
	
	vector<Edge> the_edges;
	BOOST_FOREACH (Edge e, edges(G))
	{
		the_edges.push_back(e);	
	}
	
	vector<Edge> the_edgesH;
	BOOST_FOREACH (Edge e, edges(H))
	{
		the_edgesH.push_back(e);	
	}
	

	std::cout<<(vertex_indices[2]==vertex_indicesH[2]);
	
	std::cout<<(edge(the_vertices[0],the_vertices[1],G).first==edge(the_vertices[0],the_vertices[1],H).first);

	vector<Edge> flipped=flip_edges(the_edges, G);
	vector<Edge> flipped1=flip_edges(the_edges, H);
	vector<Edge> mergetarget;
	PRINT_EDGES(flipped, H);
	PRINT_EDGES(flipped1, H);
	edge_union(the_edgesH, the_edges, H, mergetarget);
	
	std::cout<<"\n";
	PRINT_EDGES(mergetarget, H);
}

BOOST_AUTO_TEST_CASE(test_input_file)
{
	
	const int N = 60;
	Graph G;
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	read_inputfile("20_1.txt", G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	EdgeCol result=find_scss(G);
	
	std::cout<<"\nAnd the final result is:\n";
	PRINT_EDGES(result.second, G);
	std::cout<<"\nWith a total weight of: "<<result.first;
	
}

BOOST_AUTO_TEST_CASE(partitioning_problem)
{
	
	// Graph with N vertices    
	
	const int N = 3;
	Graph G(N);
	
	// Create a vector to keep track of all the vertices and enable us
	// to index them. As a side note, observe that this is not
	// necessary since Vertex is probably an integral type. However,
	// this may not be true of arbitrary graphs and I think this code
	// is a better illustration of a more general case.
	Vertices the_vertices;
	
	BOOST_FOREACH (Vertex v, vertices(G))
	{
		the_vertices.push_back(v);
	}
	
	// add a few edges with weights to the graph
	add_edge(the_vertices[0], the_vertices[1], 277317, G);
	add_edge(the_vertices[1], the_vertices[0], 26247, G);
	add_edge(the_vertices[0], the_vertices[2], 478726, G);
	add_edge(the_vertices[2], the_vertices[0], 930382, G);
	add_edge(the_vertices[1], the_vertices[2], 370287, G);
	add_edge(the_vertices[2], the_vertices[1], 112344, G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	EdgeCol result=find_scss(G);
	
	std::cout<<"\nAnd the final result is:\n";
	PRINT_EDGES(result.second, G);
	std::cout<<"\nWith a total weight of: "<<result.first;

}

BOOST_AUTO_TEST_CASE(msa_dup)
{
	Graph G;
	Vertices the_vertices;
	
		read_inputfile("12_3.txt", G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	EdgeNameMap machines =get(boost::edge_name_t(), G);
	
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	
	EdgeCol best;
	partitions_list pl(G, vertex_indices, weights, false); 

	while (!pl.is_empty())
	{
		pl.print(0,G);
		pl.partition(0);
		best=pl.get_cur_best_msa();
		std::cout<<"\nIn main loop.  Cur best MSA is:\n";
		PRINT_EDGES(best.second, G);
		std::cout<<"\nwith a total weight of: "<<best.first<<"\n";
	}
	
	pl.print(0,G);
}

BOOST_AUTO_TEST_CASE(read_input)
{
	
	//const int N = 60;
	Graph G;
	Vertices the_vertices;
	
//	BOOST_FOREACH (Vertex v, vertices(G))
//	{
//		the_vertices.push_back(v);
//	}
	
	read_inputfile("catalog2.txt", G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	EdgeNameMap machines =get(boost::edge_name_t(), G);

	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t"
		<< get(weights, e) << "\n";
	}
	
	EdgeCol result=find_scss(G);
	
	std::cout<<"\nAnd the final result is:\n";
	PRINT_EDGES(result.second, G);
	std::cout<<"\nWith a total weight of: "<<result.first;
	
}



// EOF
 
