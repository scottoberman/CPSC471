/*****************************************************************************
* CPSC 471 Project 3
*
*   Dijkstra's Algorithm through a directed graph
*
******************************************************************************/

#include <iostream>
#include <map>
#include <queue>
#include <vector>

class Node
{
public:
    bool AddEdge(const int ID, const unsigned int WEIGHT);
private:
    int id;
    vector<Edge> edges;
};

class Edge
{
public:
    Node* GetSource();
    Node* GetDestination();
    unsigned int GetLength();

private:
    Node* source;
    Node* destination;
    unsigned int length;
};

class Graph
{
public: 
private:
    bool 

};



using namespace std;

int main()
{
    Node activeNode;
    map<int, Node> nodes;

    vector<Node> nodesRemaining;
    priority_queue<Edge*> edgesRemaining;

    nodes.push_back()



}