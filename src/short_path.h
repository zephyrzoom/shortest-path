/*
 * @author 707<707472783@qq.com>
 * This program searches the shortest path.
 */
#pragma once
#include <vector>

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


class Node
{
public:
    Node *parent;
    // node number
    int num;
    // arc number
    int arc;
    // the path weight
    int weight;
    // store the exist node by bit.
    std::vector<unsigned int> exist;
    // nodes that have not visited.
    std::vector<Arc> notVisit;

    Node(Node *parent_,
        int num_,
        int arc_,
        std::vector<Arc> notVisit_
        ):
        parent(parent_),
        num(num_),
        arc(arc_),
        notVisit(notVisit_) {}

    Node(Node *parent_,
        int num_,
        int arc_,
        int weight_,
        std::vector<unsigned int> exist_,
        std::vector<Arc> notVisit_
        ):
        parent(parent_),
        num(num_),
        arc(arc_),
        weight(weight_),
        exist(exist_),
        notVisit(notVisit_) {}
    void addExistNode(int num);
};



std::vector<int> findPath(const char **topo, const int edgeNum, const char *demand);
std::vector<Arc> sortByIn(const char **topo, const int edgeNum);
std::vector<int> getDemand(const char *demand);
std::vector<Arc> findArcs(int inNode, std::vector<Arc> arcs);
Node *insertNode(Node *root, std::vector<Arc>::iterator &arc, std::vector<Arc> &arcs);
std::vector<Arc> restore2Int(const char **topo, const int edgeNum);
bool nodeAlreadyExist(int out, Node *root);
void printPath(std::vector<int> result);
void calTheShortestPath(std::vector<int> &path, Node *node,
    int &pathWeight, std::vector<int> &demand);