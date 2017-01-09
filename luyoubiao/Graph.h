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
    int getFirstNeibor(int v);                  //取第一个
    int getNextNeibor(int v,int w);             //取第二个
    int NumberOfVertices()
        {   return numVertices;}
    int NumberOfEdges()
        {   return numEdges;}
    bool insertVertex(const T & vertex);        //插入顶点
    bool insertEdge(int v1,int v2,E cost);      //插入边
    bool removeVertex(int v);                   //删除顶点
    bool removeEdge(int v1,int v2);             //删除边
    void PrintJu();
private:
    T * VerticesList;//顶点表
    E ** Edge;       //邻接矩阵
    int numEdges;    //当前边数
    int numVertices; //当前顶点数
    int maxVertices; //最大顶点数
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
    VerticesList[v] = VerticesList[ numVertices - 1 ];    //取最后一个
    for(int i = 0 ; i < numVertices ; i ++ )              //减边操作
        if(Edge[i][v] > 0 && Edge[i][v] < maxWeight) numEdges -- ;
    for(int i = 0 ; i < numVertices ; i ++ )              //最后一列填补
        Edge[i][v] = Edge[i][ numVertices - 1 ];
    numVertices -- ;
    for(int j = 0 ; j < numVertices ; j ++ )              //最后一行填补
        Edge[v][j] = Edge[numVertices][j];
    //最外一层重新置为最大

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
    out<<"节点数和边数为："
       <<n<<"."<<m<<endl;
    out<<"所有的边为:(节点1,节点2,距离)"<<endl;
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
