#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Graph::Graph(int capacity){
  this->filled = 0;
  vertices = new hashTable(capacity*2);   // HashTable Initialization
}

void Graph::insert(const string &s1, const string &s2, int dist){
  Node* V1;
  Node* V2;
  if(findNode(s1) == false){
    V1 = nullptr;                // Setting Pointer to Null to be updated later
  } else{
    V1 = (Node *)vertices->getPointer(s1);    // Obtaining Pointer of Node
  }
  if(findNode(s2) == false){
    V2 = nullptr;                // Setting Pointer to Null to be updated later
  } else{
    V2 = (Node *)vertices->getPointer(s2);    // Obtaining Pointer of Node
  }
  Edge edge;                  // Creating new Edge
  if(V1 == nullptr){
    //Source doesn't exist, creating new node
    V1 = new Node;
    V1->name = s1;
    V1->dist = 2000000;
    V1->known = false;
    vertices->insert(s1,V1);  // Adding Node to HashTable with pointer to Node
    node_list.push_back(V1);  // Adding Node to list of all Nodes
    filled++;                 // Increasing filled number of nodes
  }

  if(V2 == nullptr){
    //Destination doesn't exist, creating new node
    V2 = new Node;
    V2->name = s2;
    V2->dist = 2000000;
    V2->known = false;
    vertices->insert(s2,V2);  // Adding Node to HashTable with pointer to Node
    node_list.push_back(V2);  // Adding Node to list of all Nodes
    filled++;                 // Increasing filled number of nodes
  }
  edge.cost = dist;           // Updating Edge Cost
  edge.next = V2;             // Updating Edge Pointer to Next Node
  V1->adj.push_back(edge);    // Adding Edge to Source adjacency list
}

bool Graph::findNode(const string &s1){
  // Checking HashTable for entry of node with name s1
  if(vertices->contains(s1))
    return true;
  else
    return false;
}

void Graph::print_path(ofstream &outfile){
  // Loop through all nodes to print path to each from starting node
  for (list<Node *>::iterator it = node_list.begin(); it != node_list.end(); ++it) {
    outfile << ((*it)->name) << ": ";
    if((*it)->dist == 2000000)
			outfile << "NO PATH" << endl;    // No Path Exists to Node it
    else{
      outfile  << ((*it)->dist) << " [";
      // Printing each element of the path to Node it
      for(list<Node *>::iterator it2 = (*it)->path.begin(); it2 != (*it)->path.end(); ++it2) {
        if(it2 == (*it)->path.begin()){
          outfile << ((*it2)->name);
        } else{
          outfile << ", " << ((*it2)->name);
        }
      }
      outfile << "]\n";
    }
  }
}


void Graph::Dijkstra(const string &s1){
  Node* start = (Node *)vertices->getPointer(s1);
  start->dist = 0;
  start->path.push_back(start);
  // Creating Binary Heap with elements of list of nodes
  heap Heap(filled);
  Heap.insert(s1,start->dist,start);
  for (list<Node *>::iterator it = node_list.begin(); it != node_list.end(); ++it) {
    // Adding each element of node list to Heap
    if ((*it)->name != s1){
      Heap.insert((*it)->name, (*it)->dist, *it);
    }
  }
  Node *n;  // Temporary Node to be used as a placeholder for deleteMin
  for(int i = 0; i < filled; ++i){
    Heap.deleteMin (NULL, NULL, &n);  // Obtaining Pointer for lowest edge
		for (list<Edge>::iterator it = n->adj.begin(); it != n->adj.end() && n->dist != 2000000; ++it){
			if (!it->next->known && it->next->dist > (it->cost + n->dist)) {
        // Updating Path if new distance is less than old distance
				it->next->path.clear();
				it->next->path.insert(it->next->path.begin(), n->path.begin(), n->path.end());
				it->next->path.push_back(it->next);
				it->next->dist = (it->cost + n->dist);
        // Updating key of Node it in Binary Heap
				Heap.setKey(it->next->name, (it->cost + n->dist));
			}
		}
    n->known = true;  // Marking Vertex as visited
  }

}
