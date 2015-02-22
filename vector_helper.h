/*
 *  vector_helper.h
 *  containertest
 *
 *  Created by Jon Lederman on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <vector>
#include <utility>

using namespace std;
vector<pair<int, int > > vecunion(vector<pair<int, int> > &first,  vector<pair<int, int> > &second, vector<pair<int, int> > &mergetarget);