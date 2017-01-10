#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
template<class T,class E>

void Dijkstra(Graph<T, E>&G, T v, E dist[], int path[],Station &Sta)//path����󵽵����·����dist[j]��v��j�����·������
{
	cout << "1.10" << endl;
	int n = G.NumberOfVertices();
	bool *S = new bool[n];//S����Ѿ���������·�����յ�
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
	S[v] = true;//����v���붥�㼯��
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
		//�����һ����ַ
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
			if (S[k] == false && w < maxWeight && dist[u] + w < dist[k])//����kδ����S�����ƹ�u��������·��
			{
				dist[k] = dist[u] + w;
				path[k] = u;//�޸ĵ�k�����·��
			}
		}
	}
	//cout<<endl;
}

template <class T,class E>

void PrintShortesPath(Graph<T,E> & G,int v,E dist[],int path[])
{
    cout<<"�Ӷ���"<<G.getValue(v)<<"����������������·��Ϊ:"<<endl;
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
            cout<<"����"<<G.getValue(i)<<"�����·��Ϊ:"<<G.getValue(v)<<" ";
            while(k > 0){ cout<<G.getValue(d[ -- k ])<<" ";}
            cout<<"���·������Ϊ:"<<dist[i]<<endl;
        }
}




#endif // DIJKSTRA_H_INCLUDED
