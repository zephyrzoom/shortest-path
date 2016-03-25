/*
 * @author 707<707472783@qq.com>
 * This program searches the shortest path.
 */

##include <vector>

class Node
{
public:
    Node *lChild;
    Node *rChild;
    Node *parent;
    int num;
    int arc;
    unsigned int exist[20];

    Node(const Node *lChild_, const Node *rChild_, const Node *parent_,
        const int &data_, const int &arc_):
        lChild(lChild_), rChild(rChild_), parent(parent_), data(data_), arc(arc_) {}
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

Node &createTree(char **topo, int edgeNum, char *demand);
std::vector<Arc> sortByIn(char **topo, int edgeNum);
std::vector<Arc>::iterator findArcs(int inNode, std::vector<Arc> arcs);
Node &insertNode(Node &root, Node &lastInsert, std::vector<Arc>::iterator arc);
Node &insertFirstNode(Node &root, std::vector<Arc>::iterator arc);
std::vector<Arc> restore2Int(char **topo, int edgeNum);
std::vector<int> getDemand(char *demand);
bool nodeExist(int out, Node &root);
void printPath(std::vector<Node> result);