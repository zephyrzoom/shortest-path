/*
 * @author 707<707472783@qq.com>
 * This program searches the shortest path.
 */
#include <vector>

#include "short_path.h"

Node &createTree(char **topo, int edgeNum, char *demand)
{
    std::vector<Node> result;

    int **sortedTopo = sortByIn(topo);

    int start = getStart(demand);
    int **arcs = findArcs(start);

    // first layer
    Node &root(NULL, NULL, NULL, arcs[0][1], NULL);

    // secend layer
    Node nextRoot = insertFirstNode(&root, arcs[0]);
    for (int i = 0; arcs[i][1] == arcs[i+1][1]; ++i)
    {
        insertNode(&root, arcs[i], arcs[i+1]);
    }

    // third layer
    root = nextRoot;
    start = getStart(root.data);
    arcs = findArcs(start);

    if (arcs != NULL)
    {
        nextRoot = insertFirstNode(&root, arcs[0]);
        if (nextRoot.data == aim)
        {
            nextRoot = NULL;
        }
    }
    else
    {
        root = root->rChild;
        while (root != NULL)
        {
            start = getStart(root.data);
            arcs = findArcs(start);

            if (arcs != NULL)
            {
                nextRoot = insertFirstNode(&root, arcs[0]);
                if (nextRoot.data == aim)
                {
                    nextRoot = NULL;
                }
            }
            root = root->rChild;
        }
        if (root == NULL)
        {
            return result;
        }
    }
    
    Node lastInsert = nextRoot;
    for (int i = 0; arcs[i][1] == arcs[i+1][1]; ++i)
    {
        Node beforeLastInsert = lastInsert;
        lastInsert = insertNode(&root, lastInsert, arcs[i+1]);
        if (lastInsert.data == aim)
        {
            result.push_back(lastInsert);
            beforeLastInsert.rChild = NULL;
        }
    }

    // redo
    std::vector<Node> result;

    int **sortedTopo = sortByIn(topo);

    int start = getStart(demand);
    int **arcs = findArcs(start);

    Node root(NULL, NULL, NULL, arcs[0][1], NULL);
    Node nextRoot = root;

    while (nextRoot != NULL)
    {
        root = nextRoot;
        nextRoot = NULL;

        while (root != NULL)
        {
            start = getStart(root.data);
            arcs = findArcs(start);

            if (arcs != NULL)
            {
                for (int i = 0; arcs[i][1] == arcs[i+1][1]; ++i)
                {
                    if (nextRoot == NULL)
                    {
                        if (!nodeExist(arcs[i], &root))
                        {
                            nextRoot = insertFirstNode(&root, arcs[i]);
                            lastInsert = nextRoot;
                            if (nextRoot.data == aim)
                            {
                                result.push_back(lastInsert);
                                nextRoot = NULL;
                            }
                        }
                    }
                    else
                    {
                        if (!nodeExist(arcs[i], &root))
                        {
                            Node beforeLastInsert = lastInsert;
                            lastInsert = insertNode(&root, lastInsert, arcs[i]);
                            if (lastInsert.data == aim)
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
}
