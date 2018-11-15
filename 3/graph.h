#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <list>
#include "heap.h"

using namespace std;

class Graph {
  private:
    class Node;
    class Edge{
      public:
        int cost;           // Edge cost to next Node
        Node* next;         // Pointer to next Node
    };
    class Node{
      public:
        string name;        // Name of Vertex
        int dist;           // Distance to starting vertex (for Dijkstra)
        bool known;         // Known value (for Dijkstra)
        list <Edge> adj;    // Adjacency List
        list <Node *> path;
    };
    list <Node *> node_list;  // List with all nodes of Graph
    hashTable *vertices;  // hashTable mapping of all verticies in Graph
  public:
    int filled;           // Indicates the amount of Nodes in Graph

    Graph(int capacity);  // Constructor to initialize hashTable & filled size

    /*  insert:
     *  Checks to see if source and destination nodes exist and creates them
     *  if they do not.  Creates an edge between source and destination nodes,
     *  and adds edge to source node's adjacency list.  */
    void insert(const string &s1, const string &s2, int dist);

    /*  findNode:
     *  Returns True if Node with name s1 exists
     *  Returns False otherwise */
    bool findNode(const string &s1);

    /*  print_path:
     *  Loops through all nodes and outputs the path from the starting to node
     *  to current node.  If no path exists, outputs NO PATH. */
    void print_path(ofstream &outfile);

    void Dijkstra(const string &s1);  // Implementation of Dijkstra's Algorithm
};

#endif //_HEAP_H
