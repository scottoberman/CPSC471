/*****************************************************************************
* CPSC 471 Project 3
*
*   Dijkstra's Algorithm through a directed graph
*
******************************************************************************/

#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Edge;

class Node
{
public:
    bool AddEdge(const char OTHER_ID, const unsigned int WEIGHT);
    unsigned int GetWeight() const;
    void SetWeight(const int WEIGHT);
    char GetParent() const;
    void SetParent(const char PARENT_ID);
    vector<Edge> edges;

    bool operator< (const Node &RHS) const;
private:
    char id;
    
    unsigned int weight;
    char parentId;
};

bool Node::AddEdge(const char OTHER_ID, const unsigned int WEIGHT)
{
    //Edge newEdge(id, OTHER_ID, WEIGHT);

    //edges.emplace_back(newEdge);

    return true;
}

unsigned int Node::GetWeight() const
{
    return weight;
}

void Node::SetWeight(const int WEIGHT)
{
    weight = WEIGHT;
}

char Node::GetParent() const
{
    return parentId;
}

void Node::SetParent(const char PARENT_ID)
{
    parentId = PARENT_ID;
}

bool Node::operator< (const Node &RHS) const
{
    return weight < RHS.GetWeight();
}

class Edge
{
public:
    Edge(const char SOURCE_ID, const char DEST_ID, const unsigned int LENGTH);
    char GetSource() const;
    char GetDestination() const;
    unsigned int GetLength() const;

private:
    char sourceId;
    char destId;
    unsigned int length;
};

Edge::Edge(const char SOURCE_ID, const char DEST_ID, const unsigned int LENGTH)
{
    sourceId = SOURCE_ID;
    destId = DEST_ID;
    length = LENGTH;
}

char Edge::GetSource() const
{
    return sourceId;
}

char Edge::GetDestination() const
{
    return destId;
}

unsigned int Edge::GetLength() const
{
    return length;
}



class Graph
{
public:
    unsigned int FindShortestPath(map<char, Node>& nodes, const char START, const char DEST);

private:
    map<char, Node> nodes;

};

unsigned int Graph::FindShortestPath(map<char, Node>& nodes, const char START, const char DEST)
{
    priority_queue<Node*> nodesRemaining;
    map<char, char> nodesVisited;
    Node* nodeStart = &(nodes.find(START)->second);
    Node* nodeDest = &(nodes.find(DEST)->second);
    nodeStart->SetWeight(0);

    nodesRemaining.emplace(nodeStart);

    // Make all nodes unvisited
    for (map<char, Node>::iterator mapIter = nodes.begin(); mapIter != nodes.end(); mapIter++)
    {
        mapIter->second.SetWeight(std::numeric_limits<unsigned int>::max());
        nodesRemaining.emplace(&mapIter->second);
    }

    // Execute Dijkstras
    Node* iter;
    while (!nodesRemaining.empty())
    {
        // Go to each edge and check weights to see if changes are necessary
        unsigned int tempWeight;
        Node* edgeDest;
        for (vector<Edge>::iterator edgeIter = (nodesRemaining.top()->edges.begin()); edgeIter != nodesRemaining.top()->edges.end(); edgeIter++)
        {
            tempWeight = nodesRemaining.top()->GetWeight() + edgeIter->GetLength();
            edgeDest = &(nodes.find(edgeIter->GetDestination()))->second;

            // If the length of the edge from the current node is shorter than the previous weight, change the destination node weight
            if (nodesVisited.find(edgeIter->GetDestination()) !=nodesVisited.end()  && tempWeight < nodes.find(edgeIter->GetDestination())->second.GetWeight())
            {
                edgeDest->SetWeight(tempWeight);
            }
        }
        nodesRemaining.pop();
    }


    // Output path from destination node to source node
    cout << "Path from selected source node to destination node: " << endl;
    stack<Node> path;
    iter = nodeDest;
    while (iter)
    {
        path.emplace(*iter);
        iter = &(nodes.find(DEST)->second);
    }


    //

    return 5;
}

int main()
{
    Node activeNode;
    map<int, Node> nodes;
    char start;
    char end;

    priority_queue<Node> nodesRemaining;

    cout << "Enter character of starting node (A-F): ";
    cin.get(start);

    cout << "Enter character of destination node (A-F): ";
    cin.get(end);

   // nodes.push_back();



}