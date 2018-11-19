/*
Ali Rahman
DSA II Coding Assignment 3
This programming assignment contains a class used to define a graph which is
separated into a header and source file which are based on a previous
implementation of a hashTable and a binary heap.  These files are used in this
program which executes Dijkstra's algorithm to find the shortest cost path to
all nodes in a graph.  The program prompts the user for a a text file that is
formatted with vertices that are connected with a cost, and a starting vertex
for Dijkstra's algorithm.  The program records the system time used for the
alogirthm to execute and reports the paths to a specified output file.
*/

#include "graph.h"
#include <fstream>
#include <string>

using namespace std;

int main(){
  // Local Vars
  ifstream graphFile;
  ofstream outFile;
  string graphName, buf, vertex, outputFile;

  Graph g(100);

  // Input File Information
  cout << "Enter name of graph file: ";
  getline(cin, graphName);
  graphFile.open(graphName.c_str());
  // Error Checking
  if(!graphFile){
    cout << "Error: Unable to open graph file " << graphName << endl;
    return(-1);
  }

  // Reading File And Inserting To Graph
  string v1, v2;
  int dist;
  while (graphFile >> v1 >> v2 >> dist){
    g.insert (v1, v2, dist);
  }

  //Starting Vertex
  bool vertexB = false;
  while(vertexB == false){
    cout << "Enter a valid vertex id for the starting vertex: ";
    getline(cin,vertex);
    vertexB = g.findNode(vertex);
  }

  // Clocking Time For Algorithm
  clock_t t1 = clock();
  g.Dijkstra(vertex);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;
  // End Timing

  // Output File Information
  cout << "Enter name of output file: ";
  getline(cin,outputFile);
  outFile.open(outputFile.c_str());
  // Error Checking
  if(!outFile){
    cout << "Error: Unable to open output file " << outputFile << endl;
    return(-1);
  }
  // Printing path to Output File
  g.print_path(outFile);

  return 0;
}
