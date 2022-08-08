#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include "Graph.h"
#include "Files.h"

// Adrian Fagilde 27.638.256

using namespace std;

void printMatrix(int matrix[][10], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }
}
int max(int a, int b) {
	if(a > b)
	 return(a); else
	 return(b);
}

int main()
{
	Files file;
	file.read();	
	int wt;
	Graph graph(100);
	Graph::Vertex *vertex;
	

	graph.loadVertices(file.getVertices());	
	
	cout << endl;
	
	graph.loadEdge(file.getInits(),file.getEnds(),file.getValues());  

	int size = graph.getSize();
    int matrix[size][10];
	 // cargando matriz para warshall
	while(true){
		
	
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
	cout << endl;
	
    graph.showGraph();

    cout << endl;
    
    cout<<"Que operacion desea realizar?"<<endl;
    cout<<"1- Eliminar un nodo por teclado"<<endl;
    cout<<"2- Buscar ruta optima entre 2 nodos insertados por teclado"<<endl;
    bool ward2 = false;
    while(true){
    	if(kbhit()){
			char key = getch();
			string node, nodeF;
			switch(int(key)){
				case 49:
					cout<<"ingrese el nodo que desea eliminar (mayusculas sensibles)"<<endl;
					fflush(stdin);
					cin>>node;
					fflush(stdin);
					if(graph.removeVertex(node)){
						cout<<"Nodo eliminado"<<endl<<endl;
					} else {
						cout<<"Nodo no encontrado"<<endl<<endl;
					}
					ward2 = true;
					break;
				case 50:
					cout<<"Ingrese el nodo inicial de la ruta (mayusculas sensibles)"<<endl;
					fflush(stdin);
					cin>>node;
					fflush(stdin);
					cout<<"Ingrese el nodo final o de llegada (mayusculas sensibles)"<<endl;
					fflush(stdin);
					cin>>nodeF;
					fflush(stdin);
					graph.dijkstra(node,nodeF);
					ward2 = true;
					break;
			}
			if(ward2){
				break;
			}
		}
	}
	system("pause");
    system("cls");
}
    return 0;
}

