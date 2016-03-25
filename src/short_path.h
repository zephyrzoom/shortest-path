/*
 * @author 707<707472783@qq.com>
 * This program searches the shortest path.
 */
class Node
{
public:
    Node *lChild;
    Node *rChild;
    Node *parent;
    int data;
    int arc;
    int exist[20];

    Node(const Node *lChild_, const Node *rChild_, const Node *parent_,
        const int &data_, const int &arc_):
        lChild(lChild_), rChild(rChild_), parent(parent_), data(data_), arc(arc_) {}
};

int *findPath(const Node *root, char *demand);
Node &createTree(char **topo, int edgeNum, char *demand);
int **sortByIn(char **topo);
char **findArcs(char inNode);
Node &insertNode(Node &root, Node &pre char *arc);
insertFirstNode(Node &root, char *arc);