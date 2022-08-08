#ifndef Archivo_H
#define Archivo_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 

using namespace std;

class Files
{
private:
    string name;
    vector<string> lineas, vertices, inits, ends;
    typedef pair<string,string> vPair;
    vector<vPair> edges;
    vector<int> values;
    int MAX;

public:
    Files()
    {
        this->name = "nodos.txt";
    }
    vector<string> read();
    void separarDatos();
    void setVertices(string vertice);
    vector<int> getValues();
    vector<string> getVertices();
    vector<string> getInits();
    vector<string> getEnds();
    int getMax();
};

vector<string>Files::read()
{
    ifstream file;
    vector<string> cadenas;
    file.open(name.c_str(), ios::in | ios::binary);
    
    string linea;
    
    	while(!file.eof())
		{
    		getline(file,linea);
    		lineas.push_back(linea);
		}
  
    file.close();
	
	separarDatos();

    return cadenas;
}


void Files::separarDatos(){
	const char *aux = lineas.at(0).c_str();
	
	MAX = aux[0] - '0';
	string primero;
	primero.push_back(lineas[1][0]);
	vertices.push_back(primero);
	
	for(int i = 1 ; i < lineas.size() ; i++){
		
		string init,dest;
		int value = lineas[i][6] - '0';
		init.push_back(lineas[i][0]);
		dest.push_back(lineas[i][3]);
		setVertices(init);
		setVertices(dest);
		inits.push_back(init);
		ends.push_back(dest);
		values.push_back(value);
//		cout << init << "->" << dest << " " << values.at(i - 1) << endl;	
	}
		
}

void Files::setVertices(string vertice){
	bool repet = false;
	int i = 0;
	while(repet != true &&  i < vertices.size()){
		if(vertice == vertices.at(i) ){
			repet = true;
		}
		i++;
	}
	
	if(repet == false){
		vertices.push_back(vertice);
	}
}
vector<int> Files::getValues(){
	return values;
}
vector<string> Files::getVertices(){
	return vertices;
}


vector<string> Files::getInits(){

	return inits;
}


vector<string> Files::getEnds(){

	return ends;
}
int Files::getMax(){
	return MAX;
}




#endif // Archivos_H
