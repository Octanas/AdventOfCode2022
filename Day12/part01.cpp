#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

using namespace std;

struct Node;

// Represents the paths between nodes that can be taken
struct Edge
{
    int Cost;
    Node *DestinationNode;

    Edge(int InCost, Node *InNode)
        : Cost(InCost), DestinationNode(InNode)
    {
    }
};

// Represents a square in the grid
struct Node
{

    int Height;
    vector<Edge> Connections;
    unsigned int TentativeDistance;

    Node(int InHeight)
        : Height(InHeight), Connections(), TentativeDistance(UINT_MAX)
    {
    }
};

int main()
{
    string StrMap;
    ifstream MyReadFile("input.txt");

    vector<Node *> Nodes;
    Node *StartingNode;
    Node *EndNode;

    int NumNodesInLine = 0;
    bool ReadingFirstLine = true;
    bool FirstInLine = true;

    // Parse grid squares and connections between them
    while (!MyReadFile.eof())
    {
        char C = MyReadFile.get();

        if (C == '\n')
        {
            ReadingFirstLine = false;
            FirstInLine = true;
        }
        else
        {
            Node *CurrNode;

            if (C == 'S')
            {
                CurrNode = new Node(1);
                StartingNode = CurrNode;
            }
            else if (C == 'E')
            {
                CurrNode = new Node(26);
                EndNode = CurrNode;
            }
            else
            {
                CurrNode = new Node((int)C - 96);
            }

            if (ReadingFirstLine)
            {
                ++NumNodesInLine;
            }
            else
            {
                // Create connections with node above the current node
                Node *AboveNode = Nodes[Nodes.size() - NumNodesInLine];

                // From above node to current node
                if (AboveNode->Height + 1 >= CurrNode->Height)
                {
                    AboveNode->Connections.push_back(Edge(1, CurrNode));
                }

                // From current node to above node
                if (CurrNode->Height + 1 >= AboveNode->Height)
                {
                    CurrNode->Connections.push_back(Edge(1, AboveNode));
                }
            }

            if (FirstInLine)
            {
                FirstInLine = false;
            }
            else
            {
                // Create connections with node to the left of current node
                Node *PrevNode = Nodes[Nodes.size() - 1];

                // From left node to current node
                if (PrevNode->Height + 1 >= CurrNode->Height)
                {
                    PrevNode->Connections.push_back(Edge(1, CurrNode));
                }

                // From current node to left node
                if (CurrNode->Height + 1 >= PrevNode->Height)
                {
                    CurrNode->Connections.push_back(Edge(1, PrevNode));
                }
            }

            Nodes.push_back(CurrNode);
        }
    }

    MyReadFile.close();

    // Dijkstra algorithm to find shortest path to destination
    vector<Node *> UnvisitedNodes = Nodes;
    Node *CurrentNode = StartingNode;
    CurrentNode->TentativeDistance = 0;

    while (true)
    {
        for (int i = 0; i < CurrentNode->Connections.size(); ++i)
        {
            Edge Connection = CurrentNode->Connections[i];

            // Check if target node of this connection is still unvisited
            // If so, update the tentative distance
            for (int i = 0; i < UnvisitedNodes.size(); ++i)
            {
                if (UnvisitedNodes[i] == Connection.DestinationNode)
                {
                    int DistanceValue = CurrentNode->TentativeDistance + 1;

                    if (DistanceValue < Connection.DestinationNode->TentativeDistance)
                    {
                        Connection.DestinationNode->TentativeDistance = DistanceValue;
                    }

                    break;
                }
            }
        }

        // Remove current node from unvisited nodes list
        for (int i = 0; i < UnvisitedNodes.size(); ++i)
        {
            if (UnvisitedNodes[i] == CurrentNode)
            {
                UnvisitedNodes.erase(UnvisitedNodes.begin() + i);
                break;
            }
        }

        // If current node was the destination, then the path was found
        // It can stop
        if (CurrentNode == EndNode)
        {
            break;
        }
        // Else, get new current node to traverse
        else
        {
            int LowestTentativeDistance = INT_MAX;
            int IndexLowest = -1;

            for (int i = 0; i < UnvisitedNodes.size(); ++i)
            {
                if (UnvisitedNodes[i]->TentativeDistance < LowestTentativeDistance)
                {
                    LowestTentativeDistance = UnvisitedNodes[i]->TentativeDistance;
                    IndexLowest = i;
                }
            }

            CurrentNode = UnvisitedNodes[IndexLowest];
        }
    }

    cout << EndNode->TentativeDistance << endl;
}