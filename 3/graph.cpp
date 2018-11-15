#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Graph::Graph(int capacity){
  this->filled = 0;
  vertices = new hashTable(capacity*2);
}

void Graph::insert(const string &s1, const string &s2, int dist){
  Node* V1;
  Node* V2;
  if(findNode(s1) == false){
    V1 = nullptr;
  } else{
    V1 = (Node *)vertices->getPointer(s1);
  }
  if(findNode(s2) == false){
    V2 = nullptr;
  } else{
    V2 = (Node *)vertices->getPointer(s2);
  }
  Edge edge;
  if(V1 == nullptr){
    //Source doesn't exist
    V1 = new Node;
    V1->name = s1;
    V1->dist = 2000000;
    V1->known = false;
    vertices->insert(s1,V1);
    node_list.push_back(V1);
    filled++;
  }

  if(V2 == nullptr){
    //Destination doesn't exist
    V2 = new Node;
    V2->name = s2;
    V2->dist = 2000000;
    V2->known = false;
    vertices->insert(s2,V2);
    node_list.push_back(V2);
    filled++;
  }
  edge.cost = dist;
  edge.next = V2;
  V1->adj.push_back(edge);
}

bool Graph::findNode(const string &s1){
  if(vertices->contains(s1))
    return true;
  else
    return false;
}

void Graph::print_path(ofstream &outfile){
  for (list<Node *>::iterator it = node_list.begin(); it != node_list.end(); ++it) {
    outfile << ((*it)->name) << ": ";
    if((*it)->dist == 2000000)
			outfile << "NO PATH" << endl;
    else{
      outfile  << ((*it)->dist) << " [";
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
  heap Heap(filled);
  Heap.insert(s1,start->dist,start);
  for (list<Node *>::iterator it = node_list.begin(); it != node_list.end(); ++it) {
    if ((*it)->name != s1){
      Heap.insert((*it)->name, (*it)->dist, *it);
    }
  }
  Node *n;
  for(int i = 0; i < filled; ++i){
    Heap.deleteMin (NULL, NULL, &n);
		for (list<Edge>::iterator it = n->adj.begin(); it != n->adj.end() && n->dist != 2000000; ++it){
			if (!it->next->known && it->next->dist > (it->cost + n->dist)) {
				it->next->path.clear();
				it->next->path.insert(it->next->path.begin(), n->path.begin(), n->path.end());
				it->next->path.push_back(it->next);
				it->next->dist = (it->cost + n->dist);
				Heap.setKey(it->next->name, (it->cost + n->dist));
			}
		}
    n->known = true;
  }

}
