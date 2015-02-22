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


int main (int argc, char * const argv[]) {
    
	Graph G;
	Vertices the_vertices;
	
	
	read_inputfile(argv[1], G);
	
	// This is how we can get a property map that gives the weights of
	// the edges.
	Weights weights =get(boost::edge_weight_t(), G);
	EdgeNameMap machines =get(boost::edge_name_t(), G);
	VertexNameMap compounds =get(boost::vertex_name_t(), G);
	
	
	// This is how we can get a property map mapping the vertices to
	// integer indices.
	Vertex_Indices vertex_indices =get(boost::vertex_index_t(), G);
	
	
	// Print the graph (or rather the edges of the graph).
/*	std::cout << "This is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t" 
		<< "("<<compounds[source(e,G)]<<","<<compounds[target(e,G)]<<")\t"
		<< machines[e] <<"\t" 
		<< get(weights, e) << "\n";
	}*/
	print_graph(G);
	
	EdgeCol result=find_scss(G);
	
	/*std::cout<<"\n=================================================\n";
	std::cout<<"\nRequired machines:\n";
	//PRINT_EDGES(result.second, G);
	std::cout<<"\nWith a total weight of: "<<result.first<<"\n";
	*/
	
	
	
    
    return 0;
}


