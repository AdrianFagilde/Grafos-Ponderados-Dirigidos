#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

void printMatrix(int matrix[][10], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }
}
int max(int a,int b) {
	if(a>b)
	 return(a); else
	 return(b);
}
void warshal(int matrix[][10], int size, Graph graph) {
	
}

void generateMatrix(int size, Graph graph) // number of vertex
{
	int matrix[size][10], wt;
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(graph.searchEdge(graph.getIndexLabel(i), graph.getIndexLabel(j), wt)){
				matrix[i][j] = 1;
			} else {
				matrix[i][j] = 0;
			}
		}
	}
	// algoritmo warshall
	int i,j,k;
	bool ward = false;
	for (k = 0; k < size; k++)
	  for (i = 0; i < size; i++)
	   for (j = 0; j < size; j++)
	    matrix[i][j]=max(matrix[i][j],matrix[i][k]&&matrix[k][j]);
	
	printMatrix(matrix, size); // eliminar despues

	for(i = 0;i < size; i++){
		for(j = 0; j < size; j++){
			if(i != j && matrix[i][j] == 0 && !ward) {
				cout<<"Matriz no fuertemente conexa"<<endl;
				ward=true;
			}
		}
	}
	if(!ward) {
		cout<<"Matriz fuertemente conexa"<<endl;
	} else {
		int cont, cont2;
		bool ward1 = false;
		for(i = 0; i < size; i++){
			cont = 0, cont2 = 0;
			for(j = 0; j < size; j++){
				if(matrix[j][i] == 0){
					cont++;
				}
				if(matrix[i][j] == 0){
					cont2++;
				}
				if(cont == size){
					cout<<graph.getIndexLabel(i)<<" es un nodo fuente"<<endl;
				}
				if(cont2 == size){
					cout<<graph.getIndexLabel(i)<<" es un nodo pozo"<<endl;
				}
			}
		}
	}
}

int main()
{
    Graph graph(100);
    Graph::Vertex *vertex;
	int wt = 0;
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertEdge("A","A",0);
    graph.insertEdge("A","B",4);
    graph.insertEdge("B","D",4);
    graph.insertEdge("A","C",3);
    graph.insertEdge("C","D",3);
    graph.insertEdge("A","D",5);
    
    graph.showGraph();
    cout << endl;
    graph.dijkstra("A","C");
    
    
    return 0;
}

