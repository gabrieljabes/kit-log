#pragma once
#include <list>
#include <queue>
#include "node.h"

Node strategyBFS(list<Node>& tree);
Node strategyDFS(list <Node>& tree);
Node strategyBBS(priority_queue <Node>& tree_BBS);

Node DFS_or_BFS(string strategy, list<Node>& tree);