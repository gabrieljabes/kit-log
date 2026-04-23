#include "branchingStrategy.h"
#include <queue>

Node strategyBFS(list<Node>& tree){
    Node next_node = tree.front();
    tree.pop_front();

    return next_node;
}

Node strategyDFS(list <Node>& tree){
    Node next_node = tree.back();
    tree.pop_back();

    return next_node;
}

Node strategyBBS(priority_queue<Node>& tree_BBS){
    Node next_node = tree_BBS.top();
    tree_BBS.pop();

    return next_node;
}

Node DFS_or_BFS(string strategy, list<Node>& tree){
    if(strategy == "BFS")
        return strategyBFS(tree);
    if(strategy == "DFS")
        return strategyDFS(tree);
}
