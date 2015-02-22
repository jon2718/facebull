/*
 *  stl_helpers.cpp
 *  containertest
 *
 *  Created by Jon Lederman on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef STL_HELPERS_CPP
#define STL_HELPERS_CPP

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

#endif