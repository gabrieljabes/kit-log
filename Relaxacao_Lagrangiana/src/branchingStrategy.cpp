#include "branchingStrategy.h"
#include "OneTree.h"
#include <queue>

OneTree strategyBFS(list<OneTree>& tree){
    OneTree next_tree = tree.front();
    tree.pop_front();

    return next_tree;
}

OneTree strategyDFS(list <OneTree>& tree){
    OneTree next_tree = tree.back();
    tree.pop_back();

    return next_tree;
}

OneTree strategyBBS(priority_queue<OneTree, vector<OneTree>, greater<OneTree>>& tree_BBS){
    OneTree next_tree = tree_BBS.top();
    tree_BBS.pop();

    return next_tree;
}

OneTree DFS_or_BFS(string strategy, list<OneTree>& tree){
    if(strategy == "BFS")
        return strategyBFS(tree);
    if(strategy == "DFS")
        return strategyDFS(tree);
}
