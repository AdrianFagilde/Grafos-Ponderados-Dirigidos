#include <iostream>
#include <queue>
#include "Graph.h"

using namespace std;



Graph::Graph(int newMaxSize)
{
    size = 0;
    maxSize = newMaxSize;
    vertexList = new Vertex [maxSize];
}


Graph::Graph(const Graph& other)
{
    *this = other;
}


Graph& Graph::operator=(const Graph& other)
{
    if (this == &other)
        return *this;

    if (!empty())
        delete[] vertexList;

    size = other.size;
    maxSize = other.maxSize;
    vertexList = new Vertex [maxSize];

    for (int i = 0; i < size; i++)
        vertexList[i] = other.vertexList[i];

    return *this;
}


Graph::~Graph()
{
    delete[] vertexList;
}


void Graph::insertVertex(const string& v)
{
    if (full())
        return;

    Vertex newVertex;
    newVertex.setLabel(v);

    for (int i = 0; i < size ; i++)
    {
        if (newVertex.getLabel() == vertexList[i].getLabel())
        {
            vertexList[i] = newVertex;
            return;
        }
    }

    vertexList[size] = newVertex;
    size++;
}


void Graph::insertEdge(const string& v1, const string& v2, const int wt)
{
    int idx = getIndex(v1);
    if (idx == -1) return;

    Vertex vtx;

    if (searchVertex(v2, vtx))
    {
        for (unsigned i = 0;
             i < vertexList[idx].edges.size();
             i++)
        {
            if (v2 == vertexList[idx].edges[i].second.getLabel())
            {
                vertexList[idx].edges[i].first = wt;
                return;
            }
        }

        vertexList[idx].edges.push_back(make_pair(wt, vtx));
    }
}


bool Graph::searchVertex(const string& v, Vertex& returnVertex) const
{
    for (int i = 0; i < size; i++)
    {
        if (v == vertexList[i].getLabel())
        {
            returnVertex = vertexList[i];
            return true;
        }
    }

    return false;
}


bool Graph::searchEdge(const string& v1, const string& v2, int& wt) const
{
    int idx1 = getIndex(v1),
        idx2 = getIndex(v2);

    if (idx1 == -1 || idx2 == -1)
        return false;

    for (int i ;  i < vertexList[idx1].edges.size() ; i++)
    {
        if (v2 == vertexList[idx1].edges[i].second.getLabel())
        {
            wt = vertexList[idx1].edges[i].first;
            return true;
        }
    }

    return false;
}


bool Graph::removeVertex(const string& v)
{
    int idx = getIndex(v);

    if (idx == -1)
        return false;

    for (int i = idx; i < size-1; i++)
        vertexList[i] = vertexList[i+1];

    size--;

    for (int i = 0; i < size; i++)
    {
        for (unsigned j = 0;
             j < vertexList[i].edges.size();
             j++)
        {
            if (v == vertexList[i].edges[j].second.getLabel())
            {
                swap(vertexList[i].edges[0],
                     vertexList[i].edges[j]);

                vertexList[i].edges.erase(vertexList[i].edges.begin());
            }
        }
    }

    return true;
}


bool Graph::removeEdge(const string& v1, const string& v2)
{
    int idx1 = getIndex(v1),
        idx2 = getIndex(v2);

    if (idx1 == -1 || idx2 == -1)
        return false;

    vertexList[idx1].edges.erase(vertexList[idx1].edges.begin()
                                    + idx2);
    return true;
}


void Graph::clear()
{
    delete[] vertexList;
    vertexList = new Vertex [maxSize];
    size = 0;
}


bool Graph::empty() const
{
    return (size == 0);
}


bool Graph::full() const
{
    return (size == maxSize);
}


void Graph::showGraph() const
{
    if (empty())
    {
        cout << "Empty Graph" << endl;
        return;
    }


    cout << "Vertex list:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << '\t' << i << '\t'
             << vertexList[i].getLabel() << endl;
    }
    cout << endl;

    cout << "Adjacency list:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << '\t' << vertexList[i].getLabel();

        for (int j = 0 ; j < vertexList[i].edges.size() ; j++)
        {
            cout << " --> [" << vertexList[i].edges[j].second.getLabel()
                 << ", " << vertexList[i].edges[j].first << ']';
        }
        cout << endl;
    }
}


void Graph::bfs(const string& src, const string& dest) const
{
    int src_idx = getIndex(src),
        dest_idx = getIndex(dest);

    if (src_idx == -1 ||
        dest_idx == -1)
        return;

    queue<int> q;
    vector<bool> visited(size, false);

    q.push(src_idx);
    visited[src_idx] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        cout << ' ' << vertexList[u].getLabel() << " - " << vertexList[u].edges[0].first << endl;

        if (u == dest_idx)
            return;

        for (int i ; i < vertexList[u].edges.size(); i++)
        {
            int v = getIndex(vertexList[u].edges[i].second.getLabel());

            if (!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}


void Graph::dijkstra(const string& src, const string& dest) const
{
	string letter;
	vector <string> vertices;
    typedef pair<int,int> vtx; // vertices 
    priority_queue<vtx,
                   vector<vtx>,
                   greater<vtx> > pq; // no se todavia 

    vector<int> dist(size, INF);

    int src_idx = getIndex(src),
        dest_idx = getIndex(dest);
    if (src_idx == -1 ||
        dest_idx == -1)
        return;

    dist[src_idx] = 0; // inicializo el vector distancias
    pq.push(make_pair(0, src_idx)); // push a el 0 y el valor a buscar

	
    while (!pq.empty())
    {
        int u = pq.top().second; // obtenemos el mas alto
        pq.pop(); // borramos en mas alto  
        
        if (u == dest_idx){
        	vertices.push_back(getIndexLabel(u));
        	break;
		}
            
		
        for (int i = 0 ; i < vertexList[u].edges.size() ; i++) // va recorrer la cantidad de conexiones
        {
            int v = getIndex(vertexList[u].edges[i].second.getLabel()); // indice de el vertice 
            int wt = vertexList[u].edges[i].first; // ponderacion de la conexion

            if (dist[v] > dist[u] + wt) // si la distacia en v es menor a  [u] + wt
            {
                dist[v] = dist[u] + wt; // 
                pq.push(make_pair(dist[v], v));
                cout << vertexList[u].getLabel();
                vertices.push_back(vertexList[u].getLabel());
                cout << " --> [" << vertexList[u].edges[i].second.getLabel()
                 << ", " << dist[v] << ']' ;
                 
                cout << endl;
            }   
        }
        
    }

    for (int i = 0; i < vertices.size() ; i++)
    {
        if(i == 0){
        	cout << vertices.at(i) << "-->" ;
        	letter = vertices.at(i);
		}
		if(i > 0 && vertices.at(i).compare(letter) != 0){
			cout << vertices.at(i) << "-->" ;
		}
    }
    cout << dist[getIndex(vertices.at(vertices.size() - 1))];
    cout << endl;
}


int Graph::getIndex(const string& v) const
{
    for (int i = 0; i < size; i++)
        if (v == vertexList[i].getLabel())
            return i;

    return -1;
}
std::string Graph::getIndexLabel(int index) const
{
	return vertexList[index].getLabel();
}

