/*****************************************************************************
* CPSC 471 Project 3
*
*   Dijkstra's Algorithm through a directed graph
*
*   By: Scott Oberman
******************************************************************************/

#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

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

class Node
{
public:
    Node(const char ID);
    bool AddEdge(const char OTHER_ID, const unsigned int WEIGHT);
    char GetId() const;
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

Node::Node(const char ID)
{
    id = ID;
    parentId = '0';
}

bool Node::AddEdge(const char OTHER_ID, const unsigned int WEIGHT)
{
    Edge newEdge(id, OTHER_ID, WEIGHT);

    edges.emplace_back(newEdge);

    return true;
}

char Node::GetId() const
{
    return id;
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

unsigned int Edge::GetLength() const
{
    return length;
}

unsigned int FindShortestPath(map<char, Node>& nodes, const char START, const char DEST)
{
    vector<Node*> nodesRemaining;
    map<char, char> nodesVisited;
    Node* nodeStart = &(nodes.find(START)->second);
    Node* nodeDest = &(nodes.find(DEST)->second);
    //nodeStart->SetWeight(0);

    nodesRemaining.emplace_back(nodeStart);
    nodesRemaining.back()->SetWeight(0);

    // Make all nodes unvisited
    for (map<char, Node>::iterator mapIter = nodes.begin(); mapIter != nodes.end(); mapIter++)
    {
        if (mapIter->first != nodeStart->GetId())
        {
            mapIter->second.SetWeight(1000);
            nodesRemaining.emplace_back(&mapIter->second);
        }
    }

    // Execute Dijkstras
    vector<Node*>::iterator iter = nodesRemaining.begin();
    int index = 0;
    Node* tempDest;
    unsigned int tempWeight;
    while (!nodesRemaining.empty())
    {
        // Check each edge of the active node
        for (int x = 0; x < (*iter)->edges.size(); x++)
        {
            tempDest = &nodes.find((*iter)->edges[x].GetDestination())->second;
            tempWeight = (*iter)->GetWeight() + (*iter)->edges[x].GetLength();
            // If the node across an edge has not been resolved, resolve it
            if (nodesVisited.find((*iter)->edges[x].GetDestination()) == nodesVisited.end())
            {
                // If the weight of an edge from the active node to the node across this edge is
                // less than the weight of the node across the edge, set a new node for that edge.
                // Also, make the active node its parent.
                if (tempWeight < tempDest->GetWeight())
                {
                    tempDest->SetWeight(tempWeight);
                    tempDest->SetParent((*iter)->GetId());
                }
            }
        }

        // Add the just resolved node to the map of resolved nodes
        nodesVisited.emplace((*iter)->GetId(), (*iter)->GetId());

        // Remove the just resolved node from the vector of unsrolved nodes
        nodesRemaining.erase(iter);

        // If there are more nodes to resolve, find the next node of least weight
        if (!nodesRemaining.empty())
        {
            iter = nodesRemaining.begin();
            // Find the next node of least weight
            for (vector<Node*>::iterator nextNodeCheck = nodesRemaining.begin(); nextNodeCheck != nodesRemaining.end(); nextNodeCheck++)
            {
                if ((*iter)->GetWeight() > (*nextNodeCheck)->GetWeight())
                {
                    iter = nextNodeCheck;
                }
            }
        }
    }

    // Output path from destination node to source node
    cout << "Path from selected source node to destination node: " << endl;
    stack<Node> path;
    Node* outputIter = nodeDest;

    if (nodeDest->GetWeight() < 100)
    {
        // Reverse the order to be output
        while (outputIter->GetParent() != '0')
        {
            path.push(*outputIter);

            outputIter = &(nodes.find(outputIter->GetParent())->second);
        }

        path.push(outputIter->GetId());



        // Output the path
        while (!path.empty())
        {
            cout << path.top().GetId() << " ";

            if (path.top().GetParent() != '0')
            {
                cout << path.top().GetWeight() << endl;
            }
            else
            {
                cout << endl;
            }

            path.pop();
        }
        cout << "Total Weight: " << nodeDest->GetWeight();
    }
    else
    {
        cout << "Path could not be resolved." << endl;
    }

    return nodeDest->GetWeight();
    
}

int main()
{
    Node* newNode;
    map<char, Node> nodes;
    char start;
    char end;

    // Node A
    newNode = new Node('a');
    newNode->AddEdge('b', 7);
    newNode->AddEdge('c', 11);
    newNode->AddEdge('d', 2);
    nodes.emplace(newNode->GetId(), *newNode);
    delete newNode;

    // Node B;
    newNode = new Node('b');
    newNode->AddEdge('d', 10);
    nodes.emplace(newNode->GetId(), *newNode);
    delete newNode;

    // Node C
    newNode = new Node('c');
    newNode->AddEdge('f', 8);
    nodes.emplace(newNode->GetId(), *newNode);
    delete newNode;

    // Node D
    newNode = new Node('d');
    newNode->AddEdge('c', 6);
    newNode->AddEdge('e', 18);
    newNode->AddEdge('f', 17);
    nodes.emplace(newNode->GetId(), *newNode);
    delete newNode;

    // Node E *has no outgoing edges*
    newNode = new Node('e');
    nodes.emplace(newNode->GetId(), *newNode);
    delete newNode;

    // Node F
    newNode = new Node('f');
    newNode->AddEdge('e', 1);
    nodes.emplace(newNode->GetId(), *newNode);
    delete newNode;

    cout << "Enter character of starting node (A-F): ";
    cin.get(start);

    cin.ignore(100, '\n');

    cout << "Enter character of destination node (A-F): ";
    cin.get(end);

    FindShortestPath(nodes, start, end);

    cin.ignore(100, '\n');
    cin.get();

}