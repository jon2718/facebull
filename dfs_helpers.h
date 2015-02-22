/*
 *  dfs_helpers.h
 *  containertest
 *
 *  Created by Jon Lederman on 3/5/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <boost/graph/depth_first_search.hpp>
using namespace boost;

template < typename OutputIterator > 
class back_edge_recorder : public default_dfs_visitor
{
public:
	back_edge_recorder(OutputIterator out):m_out(out) { }
	
	template < typename Edge, typename Graph >
	void back_edge(Edge e, const Graph &)
	{
		*m_out++ = e;
	//	std::cout<<"finding back edge ";
	}
	
	template < typename Edge, typename Graph >
	void examine_edge(Edge e, const Graph &g)	{
	//	std::cout<<"\nFinding tree edge:\t "<<"("<<source(e,g)<<","<<target(e,g)<<")";
	}
private:
	OutputIterator m_out;
};

// object generator function
template < typename OutputIterator >
back_edge_recorder < OutputIterator >
make_back_edge_recorder(OutputIterator out)
{
	//std::cout<<"in back edge recorder ";
	return back_edge_recorder < OutputIterator > (out);
}

template <typename GR> inline bool dfs(const GR & g, Vertex &vert)    // A container of sets of vertices
{
	bool all_vertices_reachable=true;
//	std::cout<<"\nIn DFS ";
	std::vector < Edge > back_edges;
	std::vector < default_color_type > color_map(num_vertices(g));
	//color_map_t cmap;
	
	dfs_init(g, make_back_edge_recorder(std::back_inserter(back_edges)), make_iterator_property_map(color_map.begin(),
																									get(vertex_index, g), color_map[0]));
	
/*	cout<<"\n Color map is: \n";
	BOOST_FOREACH (const Vertex &v, vertices(g))	
	std::cout<<color_map[v];*/
	
	depth_first_visit(g, vert,
					  make_back_edge_recorder(std::back_inserter(back_edges)),
					  make_iterator_property_map(color_map.begin(),
											 get(vertex_index, g), color_map[0]));
//		depth_first_visit(g, vert,make_back_edge_recorder(std::back_inserter(back_edges)),
//						 cmap);
	
/*		cout<<"\n Color map is: \n";
	BOOST_FOREACH (const Vertex &v, vertices(g))
	std::cout<<color_map[v];*/
	
	BOOST_FOREACH (const Vertex &v, vertices(g))
	{
		if (color_map[v]==Color::black())
			continue;
		else
		{
			all_vertices_reachable=false;
			break;
		}
		
					
	}
	
	//std::cout<<all_vertices_reachable;
	return all_vertices_reachable;

}
template <class VertexListGraph, class DFSVisitor, class ColorMap> 
void dfs_init(const VertexListGraph& g, DFSVisitor vis, ColorMap color) 
{ 
	function_requires<DFSVisitorConcept<DFSVisitor, VertexListGraph> >(); 
//	typedef typename property_traits<ColorMap>::value_type ColorValue; 
//	typedef color_traits<ColorValue> Color; 
	typename graph_traits<VertexListGraph>::vertex_iterator ui, ui_end; 
	for (tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) { 
       put(color, *ui, Color::white()); 
        vis.initialize_vertex(*ui, g); 
	} 
//	std::cout<<"Color type white is: "<<Color::white();
//	std::cout<<"Color type gray is: "<<Color::gray();
//	std::cout<<"Color type black is: "<<Color::black();
} 
