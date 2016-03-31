/*
 * @author 707<707472783@qq.com>
 * This program searches the shortest path.
 */
#include <vector>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "short_path.h"

int main(int argc, char const *argv[])
{
    const char *topo[5000] = {
        // "0,0,1,1\n",
        // "2,0,3,1\n",
        // "1,0,2,2\n",
        // "3,2,1,3\n",
        // "4,3,1,1\n",
        // "5,2,3,1\n",
        // "6,3,2,1\n"
        
        "0,0,13,15\n",
        "1,0,8,17\n",
        "2,0,19,1\n",
        "3,0,4,8\n",
        "4,1,0,4\n",
        "5,2,9,19\n",
        "6,2,15,8\n",
        "7,3,0,14\n",
        "8,3,11,12\n",
        "9,4,1,15\n",
        "10,4,5,17\n",
        "11,5,8,180\n",
        "12,5,9,14\n",
        "13,5,6,2\n",
        "14,6,17,4\n",
        "15,7,13,1\n",
        "16,7,16,19\n",
        "17,8,6,1\n",
        "18,8,12,17\n",
        "19,9,14,11\n",
        "20,10,12,1\n",
        "21,11,7,12\n",
        "22,11,4,7\n",
        "23,12,14,5\n",
        "24,13,17,12\n",
        "25,13,4,2\n",
        "26,14,19,9\n",
        "27,15,10,14\n",
        "28,15,180,2\n",
        "29,16,8,1\n",
        "30,17,9,14\n",
        "31,17,19,3\n",
        "32,17,180,10\n",
        "33,180,15,8\n",
        "34,180,3,8\n",
        "35,19,180,12\n",
        "36,2,3,20\n",
        "37,3,5,20\n",
        "38,5,7,20\n",
        "39,7,11,20\n",
        "40,11,13,20\n",
        "41,17,11,20\n",
        "42,11,19,20\n",
        "43,17,5,20\n",
        "44,5,19,20\n"
    };
    //int edgeNum = 7;
    int edgeNum = 45;
    //const char *demand = "0,1,2|3";
    const char *demand = "2,19,3|5|7|11|13|17";


    std::vector<int> result = findPath(topo, edgeNum, demand);
    printPath(result);

    return 0;
}

std::vector<int> findPath(const char **topo, const int edgeNum, const char *demand)
{
    std::vector<int> path;
    int pathWeight = 0xFFFF;

    std::vector<Arc> sortedTopo = sortByIn(topo, edgeNum);

    std::vector<int> dmd = getDemand(demand);
    int start = dmd[0];
    std::vector<Arc> arcs = findArcs(start, sortedTopo);

    // create root from the start.
    Node *root = new Node(NULL, arcs[0].in, 0, arcs);
    root->addExistNode(arcs[0].in);

    while (root != NULL)
    {
        while (root->notVisit.size() > 0)
        {
            std::vector<Arc>::iterator arc = root->notVisit.begin();
            if (!nodeAlreadyExist(arc->out, root))
            {
                Node *node = insertNode(root, arc, sortedTopo);
                if (node->num == dmd[1])
                {
                    calTheShortestPath(path, node, pathWeight, dmd);
                    delete node;
                    root->notVisit.erase(arc);
                }
                else
                {
                    root->notVisit.erase(arc);
                    root = node;
                }
            }
            else
            {
                root->notVisit.erase(arc);
            }
        }
        Node *toBeDel = root;
        root = root->parent;
        delete toBeDel;
    }
    return path;
}

/*
sort the topo list by in-degree.
use the insert sort algorithm.
 */
std::vector<Arc> sortByIn(const char **topo, const int edgeNum)
{
    std::vector<Arc> arcs = restore2Int(topo, edgeNum);

    for (std::vector<Arc>::iterator i = arcs.begin()+1; i != arcs.end(); ++i)
    {
        std::vector<Arc>::iterator j = i;
        while (j > arcs.begin() && (j-1)->in > j->in)
        {
            std::swap(*j, *(j-1));
            --j;
        }
    }

    return arcs;
}

/*
change the topo list from char to int.
 */
std::vector<Arc> restore2Int(const char **topo, const int edgeNum)
{
    std::vector<Arc> arcs;
    for (size_t i = 0; i < edgeNum; ++i)
    {
        int tmpArc[4];
        int used = 0;
        int tmp = 0;
        size_t j = 0;
        while (topo[i][j] != '\n')
        {
            if (isdigit(topo[i][j]))
            {
                tmp = tmp * 10 + (topo[i][j] - '0');
            }
            else
            {
                tmpArc[used++] = tmp;
                tmp = 0;
            }
            ++j;
        }
        tmpArc[used] = tmp;
        Arc arc(tmpArc[0], tmpArc[1], tmpArc[2], tmpArc[3]);
        arcs.push_back(arc);
    }
    return arcs;
}

/*
change the demand from char to int.
 */
std::vector<int> getDemand(const char *demand)
{
    std::vector<int> dmd;
    int tmp = 0;
    for (size_t i = 0; i < strlen(demand); ++i)
    {
        if (isdigit(demand[i]))
        {
            tmp = tmp * 10 + (demand[i] - '0');
        }
        else
        {
            dmd.push_back(tmp);
            tmp = 0;
        }
    }
    dmd.push_back(tmp);
    return dmd;
}

/*
find corresponding arcs by the in-degree node number.
 */
std::vector<Arc> findArcs(int inNode, std::vector<Arc> arcs)
{
    std::vector<Arc> found;
    for (std::vector<Arc>::iterator i = arcs.begin(); i != arcs.end(); ++i)
    {
        if (i->in == inNode)
        {
            found.push_back(*i);
        }
    }
    return found;
}

/*
test the node exist or not in the path
by compare the bit position.
 */
bool nodeAlreadyExist(int out, Node *root)
{
    if (root->exist.size() > out/32)
    {
        if ((1 << (out%32) & root->exist[out/32]) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


Node *insertNode(Node *root, std::vector<Arc>::iterator &arc, std::vector<Arc> &arcs)
{
    Node *node = new Node(root, arc->out, arc->num,
        arc->weight + root->weight, root->exist,
        findArcs(arc->out, arcs));
    node->addExistNode(arc->out);
    return node;
}

void printPath(std::vector<int> result)
{
    for (std::vector<int>::iterator i = result.begin(); i != result.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}

/*
add the node info
to the bit position.
 */
void Node::addExistNode(int num)
{
    int needed = num/32 + 1 - this->exist.size();
    if (needed > 0)
    {
        for (size_t i = 0; i < needed; ++i)
        {
            unsigned int tmp = 0;
            this->exist.push_back(tmp);
        }
    }
    this->exist[num/32] |= (1 << num);
}

void calTheShortestPath(std::vector<int> &path, Node *node,
    int &pathWeight, std::vector<int> &demand)
{

    for (std::vector<int>::iterator j = demand.begin()+2; j != demand.end(); ++j)
    {
        if (!nodeAlreadyExist(*j, node))
        {
            return;
        }
    }
    // print paths.
    // temporary.
    Node *tmp = node;
    while (tmp != NULL)
    {
        std::cout << tmp->num << " ";
        tmp = tmp->parent;
    }
    std::cout << std::endl;

    if (path.empty())
    {
        pathWeight = node->weight;
        while (node->parent != NULL)
        {
            path.insert(path.begin(), node->arc);
            node = node->parent;
        }
    }
    else
    {
        if (node->weight < pathWeight)
        {
            pathWeight = node->weight;
            path.clear();
            while (node->parent != NULL)
            {
                path.insert(path.begin(), node->arc);
                node = node->parent;
            }
        }
    }
}