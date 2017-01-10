#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
template<class T,class E>

void Dijkstra(Graph<T, E>&G, T v, E dist[], int path[],Station &Sta)//path存放求到的最短路径，dist[j]是v到j的最短路径长度
{
	cout << "1.10" << endl;
	int n = G.NumberOfVertices();
	bool *S = new bool[n];//S存放已经求出的最短路径的终点
	int i, j, k;
	E w, min;
	for (i = 0 ; i < n ; i ++ )
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
	for (i = 0 ; i < n - 1 ; i ++ )
	{
		min = maxWeight;
		int u = v;
		for (j = 0 ; j < n ; j ++ )
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
		while(path[pro] != v && path[pro] != -1)
        {
            pro = path[pro];
        }
        Sta.NextStation[u] = pro;
        Sta.dst[u] = dist[u];
        //****************************************
		S[u] = true;
		//cout<<u<<endl;
		for (k = 0 ; k < n ; k ++ )
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

template <class T,class E>

void PrintShortesPath(Graph<T,E> & G,int v,E dist[],int path[])
{
    cout<<"从顶点"<<G.getValue(v)<<"到其他各定点的最短路径为:"<<endl;
    int j,k,n = G.NumberOfVertices();
    int * d = new int[n];
    for(int i = 0 ; i < n ; i ++ )
        if(i != v)
        {
            j = i ; k = 0 ;
            while(j != v && j != -1){
                    d[ k ++ ] = j ;
                    j = path[j];
                    }
            cout<<"顶点"<<G.getValue(i)<<"的最短路径为:"<<G.getValue(v)<<" ";
            while(k > 0){ cout<<G.getValue(d[ -- k ])<<" ";}
            cout<<"最短路径长度为:"<<dist[i]<<endl;
        }
}




#endif // DIJKSTRA_H_INCLUDED
