/*
 *  vector_helper.cpp
 *  containertest
 *
 *  Created by Jon Lederman on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <vector>
#include <utility>
#include <algorithm>
#include "vector_helper.h"


using namespace std;

struct sort_pred
{
	bool operator () (const pair<int, int> & left,  const pair <int, int> & right)
	{	
		if (left.first==right.first)
		return left.second < right.second;
		else 
			return left.first<right.first;
	

	}
};


vector<pair<int, int > > vecunion(vector<pair<int, int> > &first,  vector<pair<int, int> > &second, vector<pair<int, int> > &mergetarget)
{

	
	sort(first.begin(), first.end(), sort_pred());
	sort(second.begin(), second.end());
	
	set_union(first.begin(),first.end(), second.begin(), second.end(), back_inserter(mergetarget));
	
	return mergetarget;
	
	
}

