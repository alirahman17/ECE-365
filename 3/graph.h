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
        int cost;
        Node* next;
    };
    class Node{
      public:
        string name;
        int dist;
        bool known;
        list <Edge> adj;
        list <Node *> path;
    };
    list <Node *> node_list;
    hashTable *vertices;
    string vertex;
  public:
    int filled;
    Graph(int capacity);
    void insert(const string &s1, const string &s2, int dist);
    bool findNode(const string &s1);
    void print_path(ofstream &outfile);
    void Dijkstra(const string &s1);
};
#endif //_HEAP_H
