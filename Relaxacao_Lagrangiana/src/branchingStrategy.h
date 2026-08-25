#pragma once
#include <list>
#include <queue>
#include "node.h"

OneTree strategyBFS(list<OneTree>& tree);
OneTree strategyDFS(list <OneTree>& tree);
OneTree strategyBBS(priority_queue<OneTree, vector<OneTree>, greater<OneTree>>& tree_BBS);

OneTree DFS_or_BFS(string strategy, list<OneTree>& tree);