/*
 *  stl_helpers.h
 *  containertest
 *
 *  Created by Jon Lederman on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
/*
 *  stl_helpers.cpp
 *  containertest
 *
 *  Created by Jon Lederman on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef STL_HELPERS_H
#define STL_HELPERS_H
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>


using namespace std;
using std::string;


/*PRINT_ELEMENTS( )
 *-prints optional C-string optcstr followed by
 *-all elements of the collection coll
 *-separated by spaces
 */
template <class T>
inline void PRINT_ELEMENTS (const T& coll, const char* optcstr="")
{
	typename T::const_iterator pos;
	std::cout << optcstr;
	for (pos=coll.begin() ; pos!=coll.end() ; ++pos) {
		std::cout << "<" << pos->first <<  "," << pos->second << ">" << ' ';
	}
	std::cout << std::endl;
}

inline void PRINT_EDGES(vector<Edge> &some_edges,  Graph &G)
{
	vector<string> machine_names;
	vector<int> machine_numbers;
	EdgeNameMap machines=get(boost::edge_name_t(), G);
	VertexNameMap vertices=get(boost::vertex_name_t(), G);
	if (some_edges.empty())
		cout<<"Empty";
		else
		{
			BOOST_FOREACH (Edge e, some_edges)
    {
        std::cout << "(" << vertices[boost::source(e, G)] << ", "
		<< vertices[boost::target(e, G)] << ")\n";
	
	}
			std::cout<<"\n";
	
			vector<Edge>::iterator pos;
			/*for (pos=some_edges.begin() ; pos!=some_edges.end() ; ++pos)
			{
				//Edge a=*pos;
				std::cout<<"\n"<<machines[*pos];
				//std::cout<<a;
			}*/
			
			BOOST_FOREACH (Edge e, some_edges)
			{
				std::string a=machines[e];
				a=a.substr(1);
				machine_numbers.push_back(atoi(a.c_str()));
			machine_names.push_back(machines[e]);
			//std::cout<< machines[e]<<" ";
			}
			sort(machine_names.begin(), machine_names.end());
			sort(machine_numbers.begin(), machine_numbers.end());
			std::cout<<"\n";
			
			int x;
		BOOST_FOREACH (int s, machine_numbers)
			{
			//	x=atoi(s.c_str());
				std::cout<<s<<" ";
			//	std::cout<<"in here";
			
			}
			
		
		}
}

/*INSERT_ELEMENTS (collection, first, last)
 *-fill values from first to last into the collection
 *-NOTE: NO half-open range
 */
template <class T>
inline void INSERT_ELEMENTS (T& coll, int first, int last)
{
	for (int i=first; i<=last; ++i) 
	{
		coll.insert(coll. end(), i);
	}
}

#endif /*STL_HELPERS_H*/
