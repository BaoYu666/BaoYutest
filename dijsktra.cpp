#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int DefaultVertices = 30;
const int maxWeight = 99999;   //初始权值

struct Station
{
	int ID;                 //关键码
	string IP;              //IP地址
	int NextStation[15];    //下一跳数组
	int dst[15];            //目的距离
	ostream & operator =(Station B)
	{
		ID = B.ID;
		IP = B.IP;
		for (int i = 0; i < 10; i++)
			NextStation[i] = B.NextStation[i];
		return cout;
	}
};

Station Sta[15];               //路由器结构体

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
	int getFirstNeibor(int v);                  //取第一个
	int getNextNeibor(int v, int w);             //取第二个
	int NumberOfVertices()
	{
		return numVertices;
	}
	int NumberOfEdges()
	{
		return numEdges;
	}
	bool insertVertex(const T & vertex);        //插入顶点
	bool insertEdge(int v1, int v2, E cost);      //插入边
	bool removeVertex(int v);                   //删除顶点
	bool removeEdge(int v1, int v2);             //删除边
	void PrintJu();
private:
	T * VerticesList;//顶点表
	E ** Edge;       //邻接矩阵
	int numEdges;    //当前边数
	int numVertices; //当前顶点数
	int maxVertices; //最大顶点数
	int getVertexPos(T vertex)
	{
		for (int i = 0; i < numVertices; i++)
		if (VerticesList[i] == vertex) return i;
		return -1;
	}
};


template<class T, class E>

void Dijkstra(Graph<T, E>&G, T v, E dist[], int path[], Station &Sta)//path存放求到的最短路径，dist[j]是v到j的最短路径长度
{
	int n = G.NumberOfVertices();
	bool *S = new bool[n];//S存放已经求出的最短路径的终点
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
	S[v] = true;//顶点v加入顶点集合
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
		//求解下一跳地址
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
			if (S[k] == false && w < maxWeight && dist[u] + w < dist[k])//顶点k未加入S，且绕过u可以缩短路径
			{
				dist[k] = dist[u] + w;
				path[k] = u;//修改到k的最短路径
			}
		}
	}
	//cout<<endl;
}

int main()
{
	return 0;
}
