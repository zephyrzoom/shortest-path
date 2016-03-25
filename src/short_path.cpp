/*
 * @author 707<707472783@qq.com>
 * This program searches the shortest path.
 */
#include <vector>
#include <cctype>
#include <iostream>
// #include <stdlib>

#include "short_path.h"

int main(int argc, char const *argv[])
{
    char topo[][] = {
        "0,0,1,1\n",
        "1,0,2,2\n",
        "2,0,3,1\n",
        "3,2,1,3\n",
        "4,3,1,1\n",
        "5,2,3,1\n",
        "6,3,2,1\n"
    };
    std::vector<Node> result = createTree(topo, edgeNum, demand);
    printPath(result);
    return 0;
}

std::vector<Node> createTree(char **topo, int edgeNum, char *demand)
{
    std::vector<Node> result;

    std::vector<Arc> sortedTopo = sortByIn(topo);

    std::vector<int> dmd = getDemand(demand);
    int start = dmd[0];
    std::vector<Arc>::iterator arcs = findArcs(start, sortedTopo);

    Node root(NULL, NULL, NULL, arcs->in, NULL);
    Node nextRoot = root;

    // current layer has node.
    while (nextRoot != NULL)
    {
        root = nextRoot;
        nextRoot = NULL;
        Node lastInsert = NULL;


        while (root != NULL)
        {
            std::vector<Arc>::iterator arcs = findArcs(root.num);
            if (arcs != NULL)
            {
                for (; arcs->out == (arcs+1)->out; ++arcs)
                {
                    if (nextRoot == NULL)
                    {
                        if (!nodeExist(arcs->out, root))
                        {
                            nextRoot = insertFirstNode(root, arcs);
                            lastInsert = nextRoot;
                            if (nextRoot.num == dmd[1])
                            {
                                result.push_back(lastInsert);
                                nextRoot = NULL;
                            }
                        }
                    }
                    else
                    {
                        if (!nodeExist(arcs->out, root))
                        {
                            Node beforeLastInsert = lastInsert;
                            lastInsert = insertNode(root, lastInsert, arcs);
                            if (lastInsert.num == dmd[1])
                            {
                                result.push_back(lastInsert);
                                beforeLastInsert.rChild = NULL;
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}


std::vector<Arc> sortByIn(char **topo, int edgeNum)
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


std::vector<Arc> restore2Int(char **topo, int edgeNum)
{
    std::vector<Arc> arcs;
    for (size_t i = 0, j = 0; i < edgeNum; ++i)
    {
        int tmpArc[4];
        int used = 0;
        int tmp = 0;
        while (topo[i][j] != '\n')
        {
            if (isdigit(topo[i][j]))
            {
                tmp = tmp * 10 + atoi(topo[i][j]);
            }
            else
            {
                tmpArc[used++] = tmp;
                tmp = 0;
            }
            ++j;
        }
        Arc arc(tmpArc[0], tmpArc[1], tmpArc[2], tmpArc[3]);
        arcs.push_back(arc);
    }
}

std::vector<int> getDemand(char *demand)
{
    std::vector<int> dmd;
    int tmp = 0;
    for (size_t i = 0; i < strlen(demand); ++i)
    {
        if (isdigit(demand[i]))
        {
            tmp = tmp * 10 + atoi(demand[i]);
        }
        else
        {
            dmd.push_back(tmp);
            tmp = 0;
        }
    }
}

std::vector<Arc>::iterator findArcs(int inNode, std::vector<Arc> arcs)
{
    for (std::vector<Arc>::iterator i = arcs.begin(); i != arcs.end(); ++i)
    {
        if (i->in == inNode)
        {
            return i;
        }
    }
    return NULL;
}

bool nodeExist(int out, Node root)
{
    while (root != NULL)
    {
        if (out == root.num)
        {
            return true;
        }
        root = *(root.parent);
    }
    return false;
}

Node &insertFirstNode(Node &root, std::vector<Arc>::iterator arc)
{
    Node node(NULL, NULL, &root, arc->out, arc->num);
    root.lChild = &node;
    return node;
}


Node &insertNode(Node &root, Node &lastInsert, std::vector<Arc>::iterator arc)
{
    Node node(&lastInsert, NULL, &root, arc->out, arc->num);
    lastInsert.rChild = &node;
    return node;
}

void printPath(std::vector<Node> result)
{
    for (std::vector<Node>::iterator i = result.begin(); i != result.end(); ++i)
    {
        while (i != NULL)
        {
            std::cout << i.arc << " ";
            i = *(i.parent);
        }
        std::cout << std::endl;
    }
}