/*
 * @author 707<707472783@qq.com>
 * This program searches the shortest path.
 */
#pragma once
#include <vector>

class Node
{
public:
    // the first node of next layer.
    Node *lChild;
    // the next node of current layer.
    Node *rChild;
    Node *parent;
    // node number
    int num;
    // arc number
    int arc;
    int weight;
    // store the exist node by bit.
    std::vector<unsigned int> exist;

    Node() {}
    Node(Node *lChild_, Node *rChild_, Node *parent_,
        int num_, int arc_, int weight_):
        lChild(lChild_), rChild(rChild_), parent(parent_),
        num(num_), arc(arc_), weight(weight_) {}
    Node(Node *lChild_, Node *rChild_, Node *parent_,
        int num_, int arc_, int weight_, std::vector<unsigned int> exist_):
        lChild(lChild_), rChild(rChild_), parent(parent_),
        num(num_), arc(arc_), weight(weight_), exist(exist_) {}
    void addExistNode(int num);
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
void printPath(std::vector<Node*> result, std::vector<int> demand);