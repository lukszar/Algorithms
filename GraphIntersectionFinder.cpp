//
//  graphIntersectionFinder.cpp
//
//  Divide graph into 2 sub-graphs.
//  Every node contain value "0" or "1".
//  Algorithm find the biggest intersection for given graph, simulating various combination of nodes where each of 2 nodes in one edge contain another value.

//  Created by Lukasz Szarkowicz on 08.12.2014.
//  Copyright (c) 2014 Lukasz Szarkowicz. All rights reserved.
//

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include <queue>

#define MAX_LOOP 1000000
#define ITERATOR 10000

// MAX_LOOP - number of max algorithm iterations
// ITERATOR - number of algorithm iterations without finding better solution
using namespace std;

class Node {
    
public:
    char    name;
    int     graphIdentity;
    
    Node (char nodeName);
};

Node::Node(char nodeName) {
    
    name = nodeName;
    graphIdentity = -1;
    
    cout << "\nConstruct Node with name: '" << this->name << "'";
}

class Edge {
    
public:
    Node*   start;
    Node*   end;
    
    Edge (Node* startNode, Node* endNode);
    bool nodesFromDifferentSubgraphs();
};

Edge::Edge(Node* startNode, Node* endNode) {
    
    start = startNode;
    end = endNode;
    
    cout << "\nConstruct Edge: <" << this->start->name << ", " << this->end->name << ">";
};

bool Edge::nodesFromDifferentSubgraphs() {
    
    if (start->graphIdentity != end->graphIdentity)
        return true;
    else
        return false;
};

class Flow {
    
public:
    vector< Node * >  nodes;
    vector< Edge * >  edges;
    int maxIntersection = 0;
    int simulationCounter = 0; // if algorithm find not better solution, iterator is increased;
    
    void addNode (char nodeName);
    Node* getNode (char nodeName);
    void addEdge (char startName, char endName);
    
    void createGraph ();
    void simulate ();
};

void Flow::addNode(char nodeName) {
    
    Node *newNode = new Node(nodeName);
    nodes.push_back(newNode);
};

Node* Flow::getNode(char nodeName) {
    
    for( int i = 0; i < this->nodes.size(); i++ )
    {
        if (nodes[i]->name == nodeName) return nodes[i];
    }
    
    return nullptr;
};

void Flow::addEdge(char startName, char endName) {
    
    Node* start = getNode(startName);
    Node* end   = getNode(endName);
    
    Edge* edge = new Edge(start, end);
    edges.push_back(edge);
};

void Flow::createGraph() {
  
    addNode('a');
    addNode('b');
    addNode('c');
    addNode('d');
    addNode('e');
    addNode('f');
    
    
    addEdge('a','b');
    addEdge('a','c');
    addEdge('a','d');
    addEdge('b','d');
    addEdge('c','d');
    addEdge('d','e');
    addEdge('e','f');
};

void Flow::simulate() {
    
    //simulating subgraphs
    for (int i = 0; i < nodes.size(); i++) {
        
        Node * tmp = nodes[i];
        tmp->graphIdentity = rand() % 2;
    }
    
    //counting edges with nodes from different subgraphs on both ends
    
    int counter = 0;
    
    for (int i = 0; i < edges.size(); i++) {
        Edge * tmp = edges[i];
        
        if (tmp->nodesFromDifferentSubgraphs())
            counter++;
    }
    
    if (counter > maxIntersection) {
        maxIntersection = counter;
        simulationCounter = 0;
        
        cout << "\n\nAlgorithm found better solution:";
        
        for (int i = 0; i < nodes.size(); i++) {
            
            Node * tmp = nodes[i];
            cout << "\nNode: \"" << tmp->name << "\" with value: " << tmp->graphIdentity;
        }
        
        cout << "\nCurrent max intersection = " << maxIntersection << "\n";
    } else {
        simulationCounter++;
    }
};

int main(int argc, const char * argv[])
{
    /* initialize random seed: */
    srand ((unsigned int)time(NULL));
    
    Flow flow;
    flow.createGraph();
    
    int loopIterator = 0;
    while (flow.simulationCounter < ITERATOR || loopIterator < MAX_LOOP)
    {
        flow.simulate();
        loopIterator++;
    }
    cout << "END OF ALGORITHM";
    
    // pause program
    int z;
    cin >> z;
    return 0;
}