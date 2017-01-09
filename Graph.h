#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED


template <class T,class E>

class Graph
{
//friend istream & operator >>(istream & in ,Graph<T,E> & G);
friend ostream & operator <<(ostream & out,Graph<int,int> & G);
public:
    Graph(int sz = DefaultVertices);
    T getValue(int i)
        { return i >= 0 && i <= numVertices ? VerticesList[i] : NULL;}
    E getWeight(int v1,int v2)
        { return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;}
    int getFirstNeibor(int v);                  //ȡ��һ��
    int getNextNeibor(int v,int w);             //ȡ�ڶ���
    int NumberOfVertices()
        {   return numVertices;}
    int NumberOfEdges()
        {   return numEdges;}
    bool insertVertex(const T & vertex);        //���붥��
    bool insertEdge(int v1,int v2,E cost);      //�����
    bool removeVertex(int v);                   //ɾ������
    bool removeEdge(int v1,int v2);             //ɾ����
    void PrintJu();
private:
    T * VerticesList;//�����
    E ** Edge;       //�ڽӾ���
    int numEdges;    //��ǰ����
    int numVertices; //��ǰ������
    int maxVertices; //��󶥵���
    int getVertexPos(T vertex)
    {
        for(int i = 0 ; i < numVertices ; i ++ )
            if(VerticesList[i] == vertex) return i;
        return -1;
    }
};

template <class T,class E>

Graph<T,E> :: Graph(int sz)
{
    maxVertices = sz;
    numVertices = numEdges = 0 ;
    VerticesList = new T[maxVertices];
    Edge = (E **) new E * [maxVertices];
    for(int i = 0 ; i < maxVertices ; i ++ )
        Edge[i] = new E[maxVertices];
    for(int i = 0 ; i < maxVertices ; i ++ )
        for(int j = 0 ; j < maxVertices ; j ++ )
        Edge[i][j] = (i == j) ? 0 : maxWeight;
}

template <class T,class E>

int Graph<T,E> :: getFirstNeibor(int v)
{
    if(v != -1)
    {
        for(int col = 0 ; col < numVertices ; col ++ )
            if(Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
    }
    return -1;
}

template <class T,class E>

int Graph<T,E> :: getNextNeibor(int v,int w)
{
    if(v != -1 && w != -1)
    {
        for(int col = w + 1 ; col < numVertices ; col ++ )
            if(Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
    }
    return -1;
}

template <class T,class E>

bool Graph<T,E> :: insertVertex(const T & vertex)
{
    if(numVertices == maxVertices) return false;
    VerticesList[ numVertices ++ ] = vertex;
    return true;
}

template <class T,class E>

bool Graph<T,E> :: removeVertex(int v)
{
    if(v < 0 || v > numVertices) return false;
    if(numVertices == 1) return false;
    VerticesList[v] = VerticesList[ numVertices - 1 ];    //ȡ���һ��
    for(int i = 0 ; i < numVertices ; i ++ )              //���߲���
        if(Edge[i][v] > 0 && Edge[i][v] < maxWeight) numEdges -- ;
    for(int i = 0 ; i < numVertices ; i ++ )              //���һ���
        Edge[i][v] = Edge[i][ numVertices - 1 ];
    numVertices -- ;
    for(int j = 0 ; j < numVertices ; j ++ )              //���һ���
        Edge[v][j] = Edge[numVertices][j];
    //����һ��������Ϊ���

    for(int i = 0 ; i < numVertices ; i ++ )
            Edge[ numVertices ][i] = Edge[i][ numVertices ] = maxWeight;

    return true;
}

template <class T,class E>

bool Graph<T,E> :: insertEdge(int v1,int v2,E cost)
{

    if(v1 > -1 && v1 < numVertices &&
        v2 > -1 && v2 < numVertices && Edge[v1][v2] == maxWeight)
    {
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numEdges ++ ;
        return true;
    }
    else return false;
}

template <class T,class E>

bool Graph<T,E> :: removeEdge(int v1,int v2)
{
    if(v1 > -1 && v1 < numVertices &&
        v2 > -1 && v2 < numVertices &&
        Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight)
    {
        Edge[v1][v2] = Edge[v2][v1] = maxWeight;
        numEdges -- ;
        return true;
    }
    else return false;
}



ostream & operator <<(ostream & out,Graph<int,int> & G)
{
    int n,m;int e1,e2;int w;
    n = G.NumberOfVertices();
    m = G.NumberOfEdges();
    out<<"�ڵ����ͱ���Ϊ��"
       <<n<<"."<<m<<endl;
    out<<"���еı�Ϊ:(�ڵ�1,�ڵ�2,����)"<<endl;
    for(int i = 0 ; i < n ; i ++ )
        for(int j = i + 1 ; j < n ; j ++ )
    {
        w = G.getWeight(i,j);
        if(w > 0 && w < maxWeight)
        {
            e1 = G.getValue(i); e2 = G.getValue(j);
            out<<"("<<Sta[e1].ID<<","<<Sta[e2].ID<<","<<w<<")"<<endl;
        }
    }
    return cout;
}


#endif // GRAPH_H_INCLUDED
