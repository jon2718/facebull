/*
 *  graph_def.h
 *  containertest
 *
 *  Created by Jon Lederman on 2/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef GRAPH_DEF_H
#define GRAPH_DEF_H
#include <boost/foreach.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <vector>
#include <iostream>
using namespace std;
using std::string;
	
typedef boost::property<boost::edge_weight_t, double>							EdgeProperty;
typedef boost::property<boost::vertex_color_t, boost::default_color_type>		VertexProperty;
typedef boost::property<boost::vertex_name_t, string>							VertexName;
typedef boost::property<boost::edge_name_t, string>								EdgeName;


typedef boost::adjacency_list<boost::listS,boost::vecS,
boost::directedS,boost::property<boost::vertex_color_t, boost::default_color_type,
boost::property<boost::vertex_name_t, string> >,
boost::property<boost::edge_weight_t, double, 
boost::property<boost::edge_name_t, string> > >									Graph;

/*typedef boost::adjacency_list<boost::listS,boost::vecS,
 boost::directedS, VertexProperty, EdgeProperty >									Graph;*/




typedef boost::property_map<Graph, boost::vertex_name_t>::type					VertexNameMap;
typedef boost::property_map<Graph, boost::edge_name_t>::type					EdgeNameMap;


typedef boost::property_map<Graph, boost::vertex_color_t>::type					ColorMap;


typedef boost::graph_traits<Graph>::vertex_descriptor							Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor								Edge;
typedef std::vector<Vertex>														Vertices;
typedef boost::property_map<Graph, boost::vertex_index_t>::type					Vertex_Indices;
typedef boost::property_map<Graph, boost::edge_weight_t>::type					Weights; 

typedef boost::property_traits<ColorMap>::value_type							ColorValue; 
typedef boost::color_traits<ColorValue>											Color;
typedef pair<double, vector<Edge> >												EdgeCol;

typedef boost::reverse_graph<Graph, Graph>										RevGraph;
typedef boost::property_map<RevGraph, boost::edge_weight_t>::type				RevWeights; 




struct sort_pred
{
	Graph graph;
	sort_pred(const Graph &g): graph(g) 
	{
	}
	
	bool operator () (const Edge & left,  const Edge & right)
	{
	//	std::cout<<"\nsources and targets "<<source(left, graph)<<target(left, graph)<<source(right,graph)<<target(right,graph);
		if ((source(left, graph)==source(right, graph)) && (target(left, graph)==target(right, graph)))
		{	
		//	std::cout<<"first condition";
			return false;
		}
			else if (source(left,graph)==source(right,graph))
			{
		//		std::cout<<"second condition";
			return target(left,graph) < target(right,graph);
			}
				else 
			
				{
		//			std::cout<<"third condition";
					return source(left,graph)<source(right,graph);
				}
		//	return weights[left]<weights[right];
		
	}
};


inline Weights::value_type total_weight(Weights &we, vector<Edge> &branching)
{
	Weights::value_type total;
	BOOST_FOREACH (const Edge &e, branching)
	{

		total=total+we[e];
		
	}
	return total;
}


inline void edge_union(vector<Edge> &first,  vector<Edge> &second, Graph &g, vector<Edge> &mergetarget)
{
	
	
		sort(first.begin(), first.end(), sort_pred(g));
		sort(second.begin(), second.end(), sort_pred(g));
		set_union(first.begin(),first.end(), second.begin(), second.end(), back_inserter(mergetarget), sort_pred(g));
	
	
}

inline void edge_difference(vector<Edge> &first,  vector<Edge> &second, Graph &g, vector<Edge> &mergetarget)
{
	
	
	sort(first.begin(), first.end(), sort_pred(g));
	sort(second.begin(), second.end(), sort_pred(g));
	set_difference(first.begin(),first.end(), second.begin(), second.end(), back_inserter(mergetarget), sort_pred(g));
	
	
}



inline void edge_union(vector<Edge> &first, Edge &second, Graph &g, vector<Edge> &mergetarget)
{
	
	vector<Edge> singleton;
	singleton.push_back(second);
//	sort(first.begin(), first.end(), sort_pred(g));
	set_union(first.begin(),first.end(), singleton.begin(), singleton.end(), back_inserter(mergetarget), sort_pred(g));
	
	
}

inline EdgeCol edge_union(vector<Edge> &first, vector<Edge> &second, Graph &g)
{
	
	vector<Edge> mergetarget;
	vector<Edge> singleton;
	sort(first.begin(), first.end(), sort_pred(g));
	sort(second.begin(), second.end(), sort_pred(g));
	set_union(first.begin(),first.end(), second.begin(), second.end(), back_inserter(mergetarget), sort_pred(g));
	Weights weights=get(boost::edge_weight_t(),g);
	double tw=total_weight(weights, mergetarget);
	return make_pair<double, vector<Edge> > (tw, mergetarget);
	
	
}



inline EdgeCol make_edgecol(vector<Edge> edges, Graph &g)
{
	Weights weights=get(boost::edge_weight_t(), g);
	double total=total_weight(weights, edges);
	return make_pair<double, vector<Edge> >(total, edges);
}

inline Graph graph_reverse(Graph &g)
{
	//std::cout<<"In graph reverse";
	Graph h(num_vertices(g));
	EdgeNameMap edgenamemapG=get(boost::edge_name_t(), g);
	EdgeNameMap edgenamemapH=get(boost::edge_name_t(), h);
	
	VertexNameMap vertexnamemapG=get(boost::vertex_name_t(), g);
	VertexNameMap vertexnamemapH=get(boost::vertex_name_t(), h);
	Vertices the_vertices;
	Weights weights =get(boost::edge_weight_t(), g);
	Vertex cur;
	
	BOOST_FOREACH (Vertex v, vertices(g))
	{
	//	the_vertices.push_back(v);
		cur=boost::add_vertex(h);
	//	vertexnamemapH[cur]=vertexnamemapG[cur];
	}
	
	BOOST_FOREACH (Vertex v, vertices(h))
	{
			the_vertices.push_back(v);
		//cur=boost::add_vertex(h);
		//	vertexnamemapH[cur]=vertexnamemapG[cur];
	}
	
	BOOST_FOREACH (Edge e, edges(g))
	{
	//	edgenamemapH[add_edge(the_vertices[target(e,g)], the_vertices[source(e,g)], weights[e], h).first]=edgenamemapG[e];
		edgenamemapH[add_edge(the_vertices[target(e,h)], the_vertices[source(e,h)], weights[e], h).first]=edgenamemapG[e];
	//	edgenamemapH[add_edge(target(e,g), source(e,g), weights[e], h).first]=edgenamemapG[e];
		std::cout<<"!!!!!"<<edgenamemapH[e];
	}
	
	BOOST_FOREACH (Edge e, edges(h))
	{
		//	edgenamemapH[add_edge(the_vertices[target(e,g)], the_vertices[source(e,g)], weights[e], h).first]=edgenamemapG[e];
				std::cout<<"!!!!!"<<edgenamemapH[e];
	}
	/*boost::reverse_graph<Graph> i=boost::reverse_graph<Graph>(g);
	Graph h;
	RevWeights weights =get(boost::edge_property_type, i);
	BOOST_FOREACH(Edge e, edges(i))
	{
	//add_edge(source(e, i), target(e, i), weights[e], h);
	
	}*/
	return h;
}

inline vector<Edge> flip_edges(vector<Edge> &edge_list, Graph &forward)
{
	vector<Edge> flipped;
	BOOST_FOREACH (Edge e, edge_list)
	{
		//boost::property_map<Graph, boost::edge_reverse_t>::type rev=get(boost::edge_reverse, g);
		flipped.push_back(edge(target(e,forward), source(e, forward), forward).first);
	}
	
	return flipped;
}

inline void print_graph(Graph &G)
{
	Weights weights =get(boost::edge_weight_t(), G);
	EdgeNameMap machines =get(boost::edge_name_t(), G);
	VertexNameMap compounds =get(boost::vertex_name_t(), G);
	
	std::cout << "\nThis is the graph:\n";
	BOOST_FOREACH (Edge e, edges(G))
	{
		std::cout << "(" << boost::source(e, G) << ", "
		<< boost::target(e, G) << ")\t" 
		<< "("<<compounds[source(e,G)]<<","<<compounds[target(e,G)]<<")\t"
		<< machines[e] <<"\t" 
		<< get(weights, e) << "\n";
	}
	
	
}	



struct part_graph {

	part_graph() {}
	part_graph(Graph &g, vector<Edge> &included_edges, vector<Edge> &excluded_edges): g(g), inc_edges(included_edges), exc_edges(excluded_edges) {}
	bool operator() (const Edge& e) const {
		vector<Vertex> single_targets;
		BOOST_FOREACH(const Edge&e, inc_edges)
		{
			single_targets.push_back(target(e,g));
		}
		
		//if excluded edge, filter it out!
		if (find(exc_edges.begin(), exc_edges.end(), e)!=exc_edges.end())
			return false;
		
		//if edge target in single_targets AND edge NOT included, then filter it out! 
		else if (find(single_targets.begin(), single_targets.end(), target(e,g))!=single_targets.end())  //in single_targets
		{
			if (find(inc_edges.begin(), inc_edges.end(), e)==inc_edges.end())  //NOT included
				return false;
			else
				return true;
		}	
		else 
			return true;
	}
	
	Graph g;
	vector<Edge> inc_edges;
	vector<Edge> exc_edges;
};



#endif