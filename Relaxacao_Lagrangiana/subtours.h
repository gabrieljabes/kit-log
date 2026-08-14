#pragma once
#include <vector>
#include <algorithm>
#include "hungarian.h"
#include "Data.h"
#include <climits>

vector<int> Subtour(hungarian_problem_t& p, int i, Data& data, vector<int>& visitados);
vector<vector<int>> All_Subtour(hungarian_problem_t& p, Data& data);
int index_min_subtour(vector<vector<int>>& all_subtour);