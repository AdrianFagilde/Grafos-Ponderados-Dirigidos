#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

int main()
{
    Graph graph(100);
    Graph::Vertex vertex;

    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    
    graph.insertEdge("B","C",5);
    graph.insertEdge("A","C",6);
    
    graph.showGraph();
    return 0;
}

