#include <iostream>
#include <windows.h>
using namespace std;

const int DefaultVertices = 30;
const int maxWeight = 99999;   //��ʼȨֵ


struct Station
{
	int ID;                 //�ؼ���
	string IP;              //IP��ַ
	int NextStation[10];    //��һ������
	ostream & operator =(Station B)
	{
		ID = B.ID;
		IP = B.IP;
		for (int i = 0; i < 10; i++)
			NextStation[i] = B.NextStation[i];
		return cout;
	}
};

Station Sta[10];               //·�����ṹ��

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

template <class T, class E>

Graph<T, E> ::Graph(int sz)
{
	maxVertices = sz;
	numVertices = numEdges = 0;
	VerticesList = new T[maxVertices];
	Edge = (E **) new E *[maxVertices];
	for (int i = 0; i < maxVertices; i++)
		Edge[i] = new E[maxVertices];
	for (int i = 0; i < maxVertices; i++)
	for (int j = 0; j < maxVertices; j++)
		Edge[i][j] = (i == j) ? 0 : maxWeight;
}

template <class T, class E>

int Graph<T, E> ::getFirstNeibor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
		if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
	}
	return -1;
}

template <class T, class E>

int Graph<T, E> ::getNextNeibor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < numVertices; col++)
		if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
	}
	return -1;
}

template <class T, class E>

bool Graph<T, E> ::insertVertex(const T & vertex)
{
	if (numVertices == maxVertices) return false;
	VerticesList[numVertices++] = vertex;
	return true;
}

template <class T, class E>

bool Graph<T, E> ::removeVertex(int v)
{
	if (v < 0 || v > numVertices) return false;
	if (numVertices == 1) return false;
	VerticesList[v] = VerticesList[numVertices - 1];
	for (int i = 0; i < numVertices; i++)
	if (Edge[i][v] > 0 && Edge[i][v] < maxWeight) numEdges--;
	for (int i = 0; i < numVertices; i++)
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;
	for (int j = 0; j < numVertices; j++)
		Edge[v][j] = Edge[numVertices][j];
	return true;
}

template <class T, class E>

bool Graph<T, E> ::insertEdge(int v1, int v2, E cost)
{

	if (v1 > -1 && v1 < numVertices &&
		v2 > -1 && v2 < numVertices && Edge[v1][v2] == maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost;
		numEdges++;
		return true;
	}
	else return false;
}

template <class T, class E>

bool Graph<T, E> ::removeEdge(int v1, int v2)
{
	if (v1 > -1 && v1 < numVertices &&
		v2 > -1 && v2 < numVertices &&
		Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		numEdges--;
		return true;
	}
	else return false;
}



ostream & operator <<(ostream & out, Graph<int, int> & G)
{
	int n, m; int e1, e2; int w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	out << "�ڵ����ͱ���Ϊ��"
		<< n << "." << m << endl;
	out << "��֮��Ĺ�ϵΪ:" << endl;
	for (int i = 0; i < n; i++)
	for (int j = i + 1; j < n; j++)
	{
		w = G.getWeight(i, j);
		if (w > 0 && w < maxWeight)
		{
			e1 = G.getValue(i); e2 = G.getValue(j);
			out << "(" << Sta[e1].ID << "," << Sta[e2].ID << "," << w << ")" << endl;
		}
	}
	return cout;
}

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
		//****************************************
		S[u] = true;
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
}

template <class T, class E>

void PrintShortesPath(Graph<T, E> & G, int v, E dist[], int path[])
{
	cout << "�Ӷ���" << G.getValue(v) << "����������������·��Ϊ:" << endl;
	int j, k, n = G.NumberOfVertices();
	int * d = new int[n];
	for (int i = 0; i < n; i++)
	if (i != v)
	{
		j = i; k = 0;
		while (j != v && j != -1){
			d[k++] = j;
			j = path[j];
		}
		cout << "��һ���ĵ�ַΪ:" << d[k - 1] << endl;
		cout << "����" << G.getValue(i) << "�����·��Ϊ:" << G.getValue(v) << " ";
		while (k > 0){ cout << G.getValue(d[--k]) << " "; }
		cout << "���·������Ϊ:" << dist[i] << endl;
	}
}




Graph<int, int>G(10);

int dist[10];
int path[10];


void InsertValue()
{
	string temp;
	int i = G.NumberOfVertices();
	cout << "������·�ɱ��ı��:";
	cin >> Sta[i + 1].ID;
	cout << "������·�ɱ���IP:";
	cin >> temp;
	G.insertVertex(i + 1);
}

void InsertWeight()
{
	int a, b, p, k, w;
	p = k = 0;
	int num = G.NumberOfVertices();
	cout << "������·�ɱ�a��IP:";
	cin >> a;
	cout << "������·�ɱ�b��IP:";
	cin >> b;
	cout << "���������˵����:";
	cin >> w;
	while (Sta[p].ID != a)  p++;
	while (Sta[k].ID != b)  k++;
	G.insertEdge(p, k, w);
	for (int i = 0; i < num - 1; i++)
		Dijkstra(G, i, dist, path, Sta[i]);
}

void DeleteVertex()
{
	int ID, p = 0;
	string choose;
	string temp;
	int num = G.NumberOfVertices();
	cout << "������·�ɱ��ı��:";
	cin >> ID;
	while (Sta[p].ID != ID)  p++;
	cout << "�������Ϣ�˶�:" << endl;
	cout << "·����IPΪ:" << Sta[p].IP << endl;
	cout << "��1ȷ��ɾ�����������˻�" << endl;
	cin >> choose;
	if (choose != "1") return;
	G.removeVertex(p);
	for (int i = p; i < num - 1; i++)
		Sta[i] = Sta[i + 1];
	for (int i = 0; i < num - 1; i++)
		Dijkstra(G, i, dist, path, Sta[i]);
}

void DeleteEdge()
{
	int a, b, p, k;
	p = k = 0;
	cout << "������·�ɱ�a��IP:";
	cin >> a;
	cout << "������·�ɱ�b��IP:";
	cin >> b;
	while (Sta[p].ID != a)  p++;
	while (Sta[k].ID != b)  k++;
	G.removeEdge(p, k);
}

void PrintGra()
{
	cout << G << endl;
}

void Print()
{
	int i, num = G.NumberOfVertices();
	int p = 0;
	cout << "������·�������:";
	cin >> i;
	while (Sta[p].ID != i)  p++;
	cout << "·����" << Sta[p].ID << "��·�ɱ�Ϊ" << endl;
	cout << "·�������    IP��ַ ��һ����� ��һ����ַ" << endl;
	for (int j = 0; j < num; j++)
	{
		if (j != p)
		{
			cout << Sta[j].ID << "\t     ";
			cout << Sta[j].IP << "\t";
			cout << Sta[Sta[p].NextStation[j]].ID << "\t";
			cout << Sta[Sta[p].NextStation[j]].IP << "\t" << endl;
		}
	}
}

int PrintChoose()
{
	cout << "1.�����  2.�����  3.ɾ���� "
		<< " 4.ɾ����  5.�鿴ͼ 6.�鿴·�ɱ�" << endl
		<< "�������ֽ��в���( ):\b\b\b";
	int choose;
	cin >> choose;
	switch (choose)
	{
	case 0: {cout << "��лʹ�ã�" << endl; return 0; }
	case 1: InsertValue(); break;
	case 2: InsertWeight(); break;
	case 3: DeleteVertex(); break;
	case 4: DeleteEdge(); break;
	case 5: PrintGra(); break;
	case 6: Print(); break;
	default: cout << "��������" << endl;
	}
	return true;
}

int main()
{
	string temp;
	cout << "������·�ɱ���IP����ͼ��" << endl;
	for (int i = 0; i < 9; i++)
	{
		cin >> temp;
		G.insertVertex(i);
		Sta[i].ID = i + 1;
		Sta[i].IP = temp;
	}
	cout << "������·�ɱ���źͱ߳�������" << endl;
	for (int i = 0; i < 15; i++)
	{
		int a, b, p, k, w;
		p = k = 0;
		cin >> a >> b >> w;
		while (Sta[p].ID != a)  p++;
		while (Sta[k].ID != b)  k++;
		G.insertEdge(p, k, w);
	}
	for (int i = 0; i < 9; i++)
	{
		Dijkstra(G, i, dist, path, Sta[i]);
		//PrintShortesPath(G,i,dist,path);
	}
	system("cls");
	while (1)
	{
		if (!PrintChoose()) break;
	}
}



/*
for(int i = 0 ; i < 9 ; i ++ )
{
cout<<"·����"<<Sta[i].ID<<"��·�ɱ�Ϊ"<<endl;
cout<<"·�������    IP��ַ   ��һ����ַ"<<endl;
for(int j = 0 ; j < 9 ; j ++ )
{
cout<<Sta[j].ID<<"\t     ";
cout<<Sta[j].IP<<"\t";
cout<<Sta[ Sta[i].NextStation[j] ].ID<<"\t";
cout<<Sta[ Sta[i].NextStation[j] ].IP<<"\t"<<endl;
}
}
}



G.insertVertex(0);
G.insertVertex(1);
G.insertVertex(2);
G.insertVertex(3);
G.insertVertex(4);
G.insertVertex(5);
G.insertVertex(6);
G.insertVertex(7);
G.insertVertex(8);
G.insertVertex(9);
G.insertEdge(1,2,2);
G.insertEdge(1,6,1);
G.insertEdge(1,7,1);
G.insertEdge(2,3,2);
G.insertEdge(2,4,4);
G.insertEdge(3,6,3);
G.insertEdge(3,7,2);
G.insertEdge(3,4,1);
G.insertEdge(4,7,6);
G.insertEdge(4,5,1);
G.insertEdge(4,8,5);
G.insertEdge(4,9,2);
G.insertEdge(5,6,5);
G.insertEdge(6,7,1);
G.insertEdge(8,9,2);
*/