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
        // "1,0,2000,2\n",
        // "2,0,3,1\n",
        // "3,2000,1,3\n",
        // "4,3,1,1\n",
        // "5,2000,3,1\n",
        // "6,3,2000,1\n"
        
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
    //const char *demand = "0,1,2000|3";
    const char *demand = "2,19,3|5|7|11|13|17";
    std::vector<Node*> result = createTree(topo, edgeNum, demand);
    std::vector<int> dmd = getDemand(demand);
    printPath(result, dmd);
    return 0;
}

std::vector<Node*> createTree(const char **topo, const int edgeNum, const char *demand)
{
    std::vector<Node*> result;

    std::vector<Arc> sortedTopo = sortByIn(topo, edgeNum);

    std::vector<int> dmd = getDemand(demand);
    int start = dmd[0];
    std::vector<Arc> arcs = findArcs(start, sortedTopo);

    Node *root = new Node(NULL, NULL, NULL, arcs[0].in, 0, 0);
    root->addExistNode(arcs[0].in);
    Node *nextRoot = root;

    // current layer has node.
    while (nextRoot != NULL)
    {
        root = nextRoot;
        nextRoot = NULL;
        Node *lastInsert = NULL;


        while (root != NULL)
        {
            std::vector<Arc> arcs = findArcs(root->num, sortedTopo);
            if (!arcs.empty())
            {
                for (std::vector<Arc>::iterator arc = arcs.begin(); arc != arcs.end(); ++arc)
                {
                    if (nextRoot == NULL)
                    {
                        if (!nodeExist(arc->out, root))
                        {
                            nextRoot = insertFirstNode(root, arc);
                            lastInsert = nextRoot;
                            if (nextRoot->num == dmd[1])
                            {
                                result.push_back(lastInsert);
                                nextRoot = NULL;
                            }
                        }
                    }
                    else
                    {
                        if (!nodeExist(arc->out, root))
                        {
                            Node *beforeLastInsert = lastInsert;
                            // new node and old node point the same address!!!
                            // why???
                            lastInsert = insertNode(root, lastInsert, arc);
                            if (lastInsert->num == dmd[1])
                            {
                                result.push_back(lastInsert);
                                beforeLastInsert->rChild = NULL;
                                lastInsert = beforeLastInsert;
                            }
                        }
                    }
                }
            }
            root = root->rChild;
        }
    }
    return result;
}


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

bool nodeExist(int out, Node *root)
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

Node *insertFirstNode(Node *root, std::vector<Arc>::iterator arc)
{
    Node *node = new Node(NULL, NULL, root, arc->out, arc->num, arc->weight + root->weight, root->exist);
    node->addExistNode(arc->out);
    root->lChild = node;
    return node;
}


Node *insertNode(Node *root, Node *lastInsert, std::vector<Arc>::iterator arc)
{
    Node *node = new Node(NULL, NULL, root, arc->out, arc->num, arc->weight + root->weight, root->exist);
    node->addExistNode(arc->out);
    lastInsert->rChild = node;
    return node;
}

void printPath(std::vector<Node*> result, std::vector<int> demand)
{
    Node *shortest = new Node(NULL, NULL, NULL, 0, 0, 10000000);

    for (std::vector<Node*>::iterator i = result.begin(); i != result.end(); ++i)
    {
        bool satisfy = true;
        for (std::vector<int>::iterator j = demand.begin()+2; j != demand.end(); ++j)
        {
            if (!nodeExist(*j, *i))
            {
                satisfy = false;
                break;
            }
        }
        if (satisfy)
        {
            if ((*i)->weight < shortest->weight)
            {
                shortest = (*i);
            }
            while (*i != NULL)
            {
                std::cout << (*i)->num << " ";
                *i = (*i)->parent;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "=================================\n";
    while (shortest != NULL)
    {
        std::cout << shortest->num << " ";
        shortest = shortest->parent;
    }
    std::cout << std::endl;
}

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