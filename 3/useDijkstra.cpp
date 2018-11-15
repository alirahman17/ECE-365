#include "graph.h"
#include <fstream>
#include <string>

using namespace std;

int main(){
  int dist;
  ifstream graphFile;
  ofstream outFile;
  Graph g(100);
  string graphName, buf, vertex, outputFile, v1, v2;
  cout << "Enter name of graph file: ";
  getline(cin, graphName);
  graphFile.open(graphName.c_str());
  //Error Checking
  if(!graphFile){
    cout << "Error: Unable to open graph file " << graphName << endl;
    return(-1);
  }
  cout << "Enter a valid vertex id for the starting vertex: ";
  getline(cin,vertex);
  clock_t t1 = clock();
  while (graphFile >> v1 >> v2 >> dist){
    g.insert (v1, v2, dist);
  }
  g.Dijkstra(vertex);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;
  cout << "Enter name of output file: ";
  getline(cin,outputFile);
  outFile.open(outputFile.c_str());
  if(!outFile){
    cout << "Error: Unable to open output file " << outputFile << endl;
    return(-1);
  }
  //Show path to File
  g.print_path(outFile);
  return 0;
}
