#include "branchingStrategy.h"

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