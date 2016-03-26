/*
 * @author 707<707472783@qq.com>
 * This program searches the shortest path.
 */
#pragma once
#include <vector>

class Node
{
public:
    Node *lChild;
    Node *rChild;
    Node *parent;
    int num;
    int arc;
    unsigned int exist[20];

    Node() {}
    Node(Node *lChild_, Node *rChild_, Node *parent_,
        int num_, int arc_):
        lChild(lChild_), rChild(rChild_), parent(parent_), num(num_), arc(arc_) {}
};

class Arc
{
public:
    int num;
    int in;
    int out;
    int weight;

    Arc(int num_, int in_, int out_, int weight_):
        num(num_), in(in_), out(out_), weight(weight_) {}
};


std::vector<Node*> createTree(const char **topo, const int edgeNum, const char *demand);
std::vector<Arc> sortByIn(const char **topo, const int edgeNum);
std::vector<int> getDemand(const char *demand);
std::vector<Arc> findArcs(int inNode, std::vector<Arc> arcs);
Node *insertNode(Node *root, Node *lastInsert, std::vector<Arc>::iterator arc);
Node *insertFirstNode(Node *root, std::vector<Arc>::iterator arc);
std::vector<Arc> restore2Int(const char **topo, const int edgeNum);
bool nodeExist(int out, Node *root);
void printPath(std::vector<Node*> result);