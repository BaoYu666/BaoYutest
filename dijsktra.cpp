#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int DefaultVertices = 30;
const int maxWeight = 99999;   //��ʼȨֵ

struct Station
{
	int ID;                 //�ؼ���
	string IP;              //IP��ַ
	int NextStation[15];    //��һ������
	int dst[15];            //Ŀ�ľ���
	ostream & operator =(Station B)
	{
		ID = B.ID;
		IP = B.IP;
		for (int i = 0; i < 10; i++)
			NextStation[i] = B.NextStation[i];
		return cout;
	}
};

Station Sta[15];               //·�����ṹ��

template <class T, class E>

class Graph
{
	//friend istream & operator >>(istream & in ,Graph<T,E> & G);
	friend ostream & operator <<(ostream & out, Graph<int, int> & G);
public:
	Graph(int sz = DefaultVertices);
	T getValue(int i)
	{
		return i >= 0 && i <= numVertices ? VerticesList[i] : NULL;
	}
	E getWeight(int v1, int v2)
	{
		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
	}
	int getFirstNeibor(int v);                  //ȡ��һ��
	int getNextNeibor(int v, int w);             //ȡ�ڶ���
	int NumberOfVertices()
	{
		return numVertices;
	}
	int NumberOfEdges()
	{
		return numEdges;
	}
	bool insertVertex(const T & vertex);        //���붥��
	bool insertEdge(int v1, int v2, E cost);      //�����
	bool removeVertex(int v);                   //ɾ������
	bool removeEdge(int v1, int v2);             //ɾ����
	void PrintJu();
private:
	T * VerticesList;//�����
	E ** Edge;       //�ڽӾ���
	int numEdges;    //��ǰ����
	int numVertices; //��ǰ������
	int maxVertices; //��󶥵���
	int getVertexPos(T vertex)
	{
		for (int i = 0; i < numVertices; i++)
		if (VerticesList[i] == vertex) return i;
		return -1;
	}
};


template<class T, class E>

void Dijkstra(Graph<T, E>&G, T v, E dist[], int path[], Station &Sta)//path����󵽵����·����dist[j]��v��j�����·������
{
	int n = G.NumberOfVertices();
	bool *S = new bool[n];//S����Ѿ���������·�����յ�
	int i, j, k;
	E w, min;
	for (i = 0; i < n; i++)
	{
		dist[i] = G.getWeight(v, i);
		S[i] = false;
		if (i != v && dist[i] < maxWeight)
			path[i] = v;
		else
			path[i] = -1;
	}
	S[v] = true;//����v���붥�㼯��
	dist[v] = 0;
	for (i = 0; i < n - 1; i++)
	{
		min = maxWeight;
		int u = v;
		for (j = 0; j < n; j++)
		{
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		int pro = u;
		//�����һ����ַ
		//****************************************
		while (path[pro] != v && path[pro] != -1)
		{
			pro = path[pro];
		}
		Sta.NextStation[u] = pro;
		Sta.dst[u] = dist[u];
		//****************************************
		S[u] = true;
		//cout<<u<<endl;
		for (k = 0; k < n; k++)
		{
			w = G.getWeight(u, k);
			if (S[k] == false && w < maxWeight && dist[u] + w < dist[k])//����kδ����S�����ƹ�u��������·��
			{
				dist[k] = dist[u] + w;
				path[k] = u;//�޸ĵ�k�����·��
			}
		}
	}
	//cout<<endl;
}

int main()
{
	return 0;
}
