/*
 *  combination_helpers.h
 *  containertest
 *
 *  Created by Jon Lederman on 3/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "boost/graph/transpose_graph.hpp"

using namespace std;
using std::string;

void read_inputfile(char *  filename, Graph &G)
{
	set<string> compounds;
	set<string> machines;
	set<string>::iterator src,tgt;
	string machine, orig_compound, new_compound, price;
	int machine_i,orig_compound_i, new_compound_i;
	double price_d;
	int min_machine, max_machine, min_compound, max_compound, num_compounds, num_machines;
	bool mach_contig, comp_contig;
	EdgeNameMap edgenamemap=get(boost::edge_name_t(), G);
	VertexNameMap vertexnamemap=get(boost::vertex_name_t(), G);
	Vertex_Indices the_vertices =get(boost::vertex_index_t(), G);
		
	
	ifstream ifs(filename, ios::in);
	
	//Scan file to find number of compounds and machines
	
	while (ifs >> machine >> orig_compound >> new_compound >> price)
	{
		compounds.insert(orig_compound);
		compounds.insert(new_compound);
		machines.insert(machine);
	}
	ifs.close();
	
	Vertex source;
	int i;
	BOOST_FOREACH(string compound, compounds)
	{
		source=add_vertex(G);
		vertexnamemap[source]=compound;
		//std::cout<<the_vertices[source];
	}
	
	
	
	num_machines=machines.size();
	num_compounds=compounds.size();
	
	Vertex target;
    //  std::cout<<"machines size: "<<num_machines<<"\n";
	  //std::cout<<"num compounds: "<<num_compounds<<"\n";
	
	ifs.open(filename, ios::in);
	while (ifs >> machine >> orig_compound >> new_compound >> price)
	{
		machine_i=atoi((machine.substr(1,machine.length())).c_str());
		orig_compound_i=atoi((orig_compound.substr(1,orig_compound.length())).c_str());
		new_compound_i=atoi((new_compound.substr(1,new_compound.length())).c_str());
		price_d=strtod(price.c_str(), NULL);
		cout<<orig_compound_i<<" "<<new_compound_i<<" "<<price_d<<" \n";
		
		
		//edgenamemap[add_edge(source, target, price_d, G).first]=machine;
				
		// add edge
		//add_edge(the_vertices[orig_compound_i], the_vertices[new_compound_i], price_d, G);
		src=compounds.find(orig_compound);
		tgt=compounds.find(new_compound);
		//std::cout<<"\n Distance to source: "<<distance(compounds.begin(), src)<<"\n";
		//std::cout<<"\n Distance to target: "<<distance(compounds.begin(), tgt)<<"\n";
		edgenamemap[add_edge(the_vertices[distance(compounds.begin(),src)], 
				 the_vertices[distance(compounds.begin(),tgt)],
				 price_d, G).first]=machine;
	//	edgenamemap[e]=machine;
	
	}
	
	
	
		
}

inline void comb_in_out (EdgeCol &best,  vector<Edge> &msa, vector<vector<Edge> > &msa_list, Graph &graph, bool is_reversed)
{
	vector<Edge> mergetarget, flipped;
	
	double total;
	Weights weights=get(boost::edge_weight_t(), graph);
	
	//std::cout<<"MSAS size in comb_in_out is: "<<msa_list.size()<<"\n";
	
	BOOST_FOREACH(vector<Edge> cur_msa, msa_list)
	{	
		if (is_reversed)
		{
			flipped=flip_edges(cur_msa,graph);
			edge_union(msa, flipped, graph, mergetarget);
		}
		else
		{	
			edge_union(msa, cur_msa, graph, mergetarget);
			//std::cout<<"non_reversed";
		}
	
	total=total_weight(weights, mergetarget);
	//	std::cout<<"\nTOTAL in COMB is: "<<total; 
	if (total<best.first)
	{
		best=pair<double, vector<Edge> >(total, mergetarget);	
		std::cout<<"REPLACING!";
		
	}
		mergetarget.clear();
	}
	
}

EdgeCol find_scss(Graph &g)
{
	//Graph h=graph_reverse(g);
	Graph h;
	boost::transpose_graph(g,h);
	print_graph(h);
	bool gen_out_trees=true;
	bool gen_in_trees=true;
	vector<Edge> best_msa_f, best_msa_r;
	EdgeCol cur_SCSS, cur_best_msa_in, cur_best_msa_out;
	vector<vector<Edge> >msas_in, msas_out;
	partitions_list plf(g, get(boost::vertex_index_t(),g), get(boost::edge_weight_t(), g), 0, false);
	partitions_list plr(h, get(boost::vertex_index_t(),h), get(boost::edge_weight_t(), h), 0, false);
	best_msa_f=plf.get_cur_best_msa().second;
	best_msa_r=plr.get_cur_best_msa().second;
	
	std::cout<<"\nBest initial MSA forward is: \n";
	PRINT_EDGES(best_msa_f, g);
	vector<Edge> flipped=flip_edges(best_msa_r, g);
	std::cout<<"\nBest initial MSA reverse is: \n";
	PRINT_EDGES(flipped, h);
	cur_SCSS=edge_union(best_msa_f, flipped, g);
	std::cout<<"\nAfter combining:\n";
	PRINT_EDGES(cur_SCSS.second, g);
	std::cout<<"\nwith a total weight of: "<<cur_SCSS.first;
	
	
	
	while (gen_in_trees==true or gen_out_trees==true)
	{
		cur_best_msa_out=plf.get_cur_best_msa();
		cur_best_msa_in=plr.get_cur_best_msa();
		
		if (plf.exhausted_msa())
		{
			std::cout<<"Exhausted out trees!";
			gen_out_trees=false;
		}
		
		if (plr.exhausted_msa())
		{
			std::cout<<"Exhausted in trees!";
			gen_in_trees=false;
		}
		if (gen_out_trees==true)
		{
			std::cout<<"\nIn gen out trees:\n";
			std::cout<<"\nCurrent best out MSA is: "<<cur_best_msa_out.first<<"\n";
			std::cout<<"\nCurrent best SCSS is: "<<cur_SCSS.first<<"\n";
			PRINT_EDGES(cur_SCSS.second, g);
			
			
			//plf.partition(0);
			cur_best_msa_out=plf.get_cur_best_msa();
			
			
			if (cur_best_msa_out.first<cur_SCSS.first)
			{
			msas_in=plr.get_msas();
			comb_in_out(cur_SCSS, cur_best_msa_out.second, msas_in,g, true);
	
			}
			else 
			{
				std::cout<<"\nCurrent best out MSA is: "<<cur_best_msa_out.first<<"\n";
				std::cout<<"\nCurrent best SCSS is: "<<cur_SCSS.first<<"\n";
				std::cout<<"Stopping generating out trees!\n";
				gen_out_trees=false;
			}
			
			plf.partition(0);

		}
		if (gen_in_trees==true)
		{	
			std::cout<<"\nIn gen in trees:\n";
			std::cout<<"\nCurrent best in MSA is: "<<cur_best_msa_in.first<<"\n";
			std::cout<<"\nCurrent best SCSS is: "<<cur_SCSS.first<<"\n";
			
			
			//plr.partition(0);
			cur_best_msa_in=plr.get_cur_best_msa();
			if (cur_best_msa_in.first<cur_SCSS.first)
			{
				msas_out=plf.get_msas();
				best_msa_r=cur_best_msa_in.second;
				flipped=flip_edges(best_msa_r, g);
				comb_in_out(cur_SCSS, flipped, msas_out, g, false);
			}
			else 
			{
				std::cout<<"\nCurrent best in MSA is: "<<cur_best_msa_in.first<<"\n";
				std::cout<<"\nCurrent best SCSS is: "<<cur_SCSS.first<<"\n";
				std::cout<<"Stopping generating in trees!\n";
				gen_in_trees=false;
			
			}
			plr.partition(0);
		}
		
	}
	std::cout<<"\n=================================================\n";
	 std::cout<<"\nRequired machines:\n";
	 PRINT_EDGES(cur_SCSS.second, g);
	 std::cout<<"\nWith a total weight of: "<<cur_SCSS.first<<"\n";
	 
	
return cur_SCSS;
}
	
	
	
	
