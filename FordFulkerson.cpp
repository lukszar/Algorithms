/*
 Ford-Fulkerson Algorithm - count max flow of network.
 
 Created by Łukasz Szarkowicz
 email: szarkowicz@gmail.com
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// define helper for bsf algorithm
#define WHITE 0
#define GRAY 1 //visited
#define BLACK 2 // end

class Node {
   
   public:
      char     name;
      int      color;
      Node*    parent;

      Node(char nodeName);
};

Node::Node(char nodeName) {
   
   name = nodeName;
   color = WHITE;
   parent = nullptr;
    
   cout << "\nConstruct Node with name: '" << this->name << "'";
}

class Edge {

   public:
      Node*    start;
      Node*    end;
      int      capacity;
      int      flow;

      Edge(Node* startNode, Node* endNode, int capacityValue);
};

Edge::Edge(Node* startNode, Node* endNode, int capacityValue) {
   
   start    = startNode;
   end      = endNode;
   capacity = capacityValue;
   flow     = 0;
   
   cout << "\nConstruct Edge: <" << this->start->name << ", " << this->end->name << "> with capacity: " << this->capacity;
}

class Flow {
   
   public:
      vector< Node * >  nodes;
      vector< Edge * >  edges;

      void              addNode(char nodeName);
      Node*             getNode(char nodeName);

      void              addEdge(char startName, char endName, int capacityValue);
      vector< Edge * >  getEdges(Node* startNode);
      Edge*             getEdge(Node* startNode, Node* endNode);

      int               bfs(char source, char dest);
      int               countMaxFlow(char startName, char endName);
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

void Flow::addEdge(char startName, char endName, int capacityValue) {
   
    Node* start = getNode(startName);
    Node* end   = getNode(endName);
    
    Edge* edge = new Edge(start, end, capacityValue);
    edges.push_back(edge);
};

vector< Edge *> Flow::getEdges(Node* startNode) {
   
   vector < Edge * > searchedEdges;
   searchedEdges.clear();
   
   for( int i = 0; i < edges.size(); i++ ) {
      
      if (edges[i]->start == startNode) searchedEdges.push_back(edges[i]);
   }
   
   return searchedEdges;
};

Edge* Flow::getEdge(Node* startNode, Node* endNode) {
   
   if (startNode && endNode) {
      
      for ( int i = 0; i < edges.size(); i++ ) {
         
         if (edges[i]->start == startNode &&
             edges[i]->end   == endNode)
            
            return edges[i];
      }
   }

   cout << "\nOne of arguments probably were NULL\n";
   return nullptr;
}

int Flow::bfs(char source, char dest) {
   
   queue < Node * > nodesQueue;
   Node *sourceNode = getNode(source);

   for ( int j=0; j<nodes.size(); j++ ) {
      
      nodes[j]->color = WHITE;
   }

   cout << "\n\n==============================================\nStart BFS with node: " << sourceNode->name;
   
   nodesQueue.push(sourceNode);
   sourceNode->color = GRAY;
   sourceNode->parent = nullptr;

   while (! nodesQueue.empty())
   {
      Node *nodeTmp = nodesQueue.front();
      nodesQueue.pop();
      nodeTmp->color = BLACK;

      vector<Edge *> currentEdges = getEdges(nodeTmp);
      
      for ( int j=0; j<currentEdges.size(); j++ ) {
         
         int capacity   = currentEdges[j]->capacity;
         int flow       = currentEdges[j]->flow;
         
         cout << "\nEdge < " << currentEdges[j]->start->name << ", " << currentEdges[j]->end->name
         << " > : capacity = " << currentEdges[j]->capacity << " and flow = " << currentEdges[j]->flow;
         
         if ( currentEdges[j]->end->color == WHITE  &&  capacity-flow > 0)
         {
             nodesQueue.push(currentEdges[j]->end);
             currentEdges[j]->end->color = GRAY;
             currentEdges[j]->end->parent = nodeTmp;
         }
      }
   }

   Node *destNode = getNode(dest);
   return destNode->color == BLACK;
};

int Flow::countMaxFlow(char startName, char endName) {
   
   Node* u;
   int maxFlow = 0;

   while (bfs(startName, endName))
   {
      // count how much we can increment the flow
      int increment = INT_MAX;
     
      for ( u = getNode(endName); u->parent; u = u->parent ) {
         
         Edge* tmpEdge = getEdge(u->parent, u);
         if (tmpEdge) increment = min(increment, tmpEdge->capacity - tmpEdge->flow);
      }

      // incrementing flow
      for ( u = getNode(endName); u->parent; u = u->parent ) {
         
         Edge* tmpEdge = getEdge(u->parent, u);
         if (tmpEdge) tmpEdge->flow += increment;
      }

      // Path trace
      cout << "\n\nPath trace:\n";
      for ( u = getNode(endName); u; u = u->parent ) {
         
         cout << u->name << " -> ";
      }

      maxFlow += increment;
      cout << "\n\nMax flow were incremented by " << increment << " and now Flow = " << maxFlow;
   }

   return maxFlow;
   
};


int main()
{
   Flow flow;

   flow.addNode('a');
   flow.addNode('b');
   flow.addNode('c');
   flow.addNode('d');
   flow.addNode('e');
   flow.addNode('f');


   flow.addEdge('a','b', 4);
   flow.addEdge('b','c', 4);
   flow.addEdge('c','d', 4);
   flow.addEdge('b','e', 4);
   flow.addEdge('e','d', 4);
   flow.addEdge('a','f', 4);
   flow.addEdge('f','c', 4);


   int max = flow.countMaxFlow('a', 'g');
   cout << "\n\n==============================================\n\nMax Flow is equal: "
      << max << "\n\n==============================================";

   // pause program
   int z;
   cin >> z;
   return 0;
}
