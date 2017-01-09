#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED


//�������ĺ���
void PrintTree(int v,int path[],int num,int depth)
{
    for(int i = 0 ; i < num ; i ++ )
    {
        if(path[i] == v && path[i] != -1)
        {
            for(int j = 0 ; j < depth ; j ++ )
            cout<<"---";
            cout<<Sta[i].ID<<endl;
            PrintTree(i,path,num,depth + 1);
        }
    }
}

void Set(Station & Sta,int j)
{
    Sta.ID = NULL;
    Sta.IP = "0.0.0.0";
    for(int i = 0 ; i < 15 ; i ++ )
    {
        if(j == i) Sta.dst[i] = 0;
        else Sta.dst[i] = maxWeight;
        Sta.NextStation[i] = 15;
    }
}

Graph<int,int>G(15);

int dist[15];
int path[15];


void FileIn()
{
    ifstream in;
    in.open("��������.txt");
    int num = 0;
    //���ļ���ȡ���ݣ�����ȡ���������浽temp������
    int VerticesNum;
    in>>VerticesNum;
    //cout<<VerticesNum<<endl;
    for(int i = 0 ; i < VerticesNum ; i ++ )
    {
        Set(Sta[i],i);
        G.insertVertex(i);
        in>>Sta[i].ID;
        in>>Sta[i].IP;
    }
    while(!in.eof())
    {
        int a,b,p,k,w;
        p = k = 0;
        in>>a>>b>>w;
        //cout<<a<<b<<w<<endl;
        while(Sta[p].ID != a)  p ++ ;
        while(Sta[k].ID != b)  k ++ ;
        //cout<<p<<k<<endl;
        G.insertEdge(p,k,w);
    }
    for(int j = 0 ; j < VerticesNum ; j ++ )
    {
        Dijkstra(G,j,dist,path,Sta[j]);
        //PrintShortesPath(G,i,dist,path);
    }
    in.close();
}


void FileOut()
{
    ofstream out;
    out.open("��������.txt");
    int VerticesNumber = G.NumberOfVertices();
    out<<VerticesNumber<<endl;
    for(int i = 0 ; i < VerticesNumber ; i ++ )
        out<<Sta[i].ID<<endl<<Sta[i].IP<<endl;
    int e1,e2,w;
    for(int i = 0 ; i < VerticesNumber ; i ++ )
        for(int j = i + 1 ; j < VerticesNumber ; j ++ )
    {
        w = G.getWeight(i,j);
        if(w > 0 && w < maxWeight)
        {
            e1 = G.getValue(i); e2 = G.getValue(j);
            out<<Sta[e1].ID<<" "<<Sta[e2].ID<<" "<<w<<endl;
        }
    }
    cout<<"����ɹ���"<<endl<<endl<<endl;
    out.close();
}

void InsertValue()
{
    string temp;
    int i = G.NumberOfVertices();
    int ID;
    Set(Sta[i],i);
    cout<<"������·�ɱ�ı��:";
    cin>>ID;
    cout<<"������·�ɱ��IP:";
    cin>>temp;
    int p = 0;
    //���װ��
    while(Sta[p].ID != ID && Sta[p].IP != temp && p < 15)  p ++ ;
    if(p != 15)
    { cout<<"·�����Ѵ���!"<<endl<<endl; return ;}
    Sta[i].ID = ID;
    Sta[i].IP = temp;
    G.insertVertex(i);
    int num = G.NumberOfVertices();
    for(int i = 0 ; i < num; i ++ )
        Dijkstra(G,i,dist,path,Sta[i]);
    cout<<"����ɹ���"<<endl<<endl<<endl;
    //G.PrintJu();
}

void InsertWeight()
{
    int a,b,p,k,w;
    p = k = 0;
    int num = G.NumberOfVertices();
    cout<<"������·�ɱ�a�ı��:";
    cin>>a;
    cout<<"������·�ɱ�b�ı��:";
    cin>>b;
    cout<<"���������˵����:";
    cin>>w;
    while(Sta[p].ID != a && p < 15)  p ++ ;
    while(Sta[k].ID != b && k < 15)  k ++ ;
    if(p == 15 || k == 15)
    { cout<<"�˵���������!"<<endl<<endl; return ;}
    G.insertEdge(p,k,w);
    for(int i = 0 ; i < num; i ++ )
        Dijkstra(G,i,dist,path,Sta[i]);
    cout<<"����ɹ���"<<endl<<endl<<endl;
}

void DeleteVertex()
{
    int ID,p = 0;
    string choose;
    string temp;
    int num = G.NumberOfVertices();
    cout<<"������·�����ı��:";
    cin>>ID;
    while(Sta[p].ID != ID && p < 15)  p ++ ;
    if(p == 15)
    { cout<<"·����������!"<<endl<<endl; return ;}
    cout<<"�������Ϣ�˶�:"<<endl;
    cout<<"·����IPΪ:"<<Sta[p].IP<<endl;
    cout<<"��1ȷ��ɾ�����������˻�"<<endl;
    cin>>choose;
    if(choose != "1") {cout<<"��ȡ��!"<<endl<<endl;return;}
    G.removeVertex(p);
    Sta[p] = Sta[ num - 1 ];
    Set(Sta[ num - 1 ],num - 1);
    for(int i = 0 ; i < num - 1 ; i ++ )
    {
        Sta[i].dst[ num - 1 ] = maxWeight;
        Sta[i].NextStation[ num - 1 ] = 15;
    }
    for(int i = 0 ; i < num ; i ++ )
        Dijkstra(G,i,dist,path,Sta[i]);
    cout<<"ɾ���ɹ���"<<endl<<endl<<endl;
    //G.PrintJu();
}

void DeleteEdge()
{
    int a,b,p,k;
    p = k = 0;
    cout<<"������·�ɱ�a��IP:";
    cin>>a;
    cout<<"������·�ɱ�b��IP:";
    cin>>b;
    while(Sta[p].ID != a && p < 15)  p ++ ;
    while(Sta[k].ID != b && k < 15)  k ++ ;
    if(p == 15 || k == 15)
    { cout<<"�˵���������!"<<endl<<endl; return ;}
    G.removeEdge(p,k);
    //G.PrintJu();
    int num = G.NumberOfVertices();
    for(int i = 0 ; i < num ; i ++ )
        Sta[i].dst[p] = Sta[i].dst[k] = maxWeight;
    for(int i = 0 ; i < 15 ; i ++ )
        Sta[k].dst[i] = Sta[p].dst[i] = maxWeight;
    for(int i = 0 ; i < num ; i ++ )
        Dijkstra(G,i,dist,path,Sta[i]);
    cout<<"ɾ���ɹ���"<<endl<<endl<<endl;
}

void PrintGra()
{
    cout<<G<<endl;
}

void Print()
{
    int i,num = G.NumberOfVertices();
    int p = 0;
    cout<<"������·�������:";
    cin>>i;
    while(Sta[p].ID != i && p != 15)  p ++ ;
    //���װ��
    if(p == 15)
        {cout<<"·���������ڣ�"<<endl<<endl;return;}
    cout<<"·����"<<Sta[p].ID<<"��·�ɱ�Ϊ"<<endl;
    cout<<"________________________________________________________________"<<endl;
    cout<<"|Ŀ��·���� | Ŀ��IP��ַ  |   ����  | ��һ�����  | ��һ����ַ |"<<endl;
    for(int j = 0 ; j < num ; j ++ )
    {
        cout<<"|"<<setfill(' ')<<setw(5)<<Sta[j].ID;
        cout<<"      |"<<setfill(' ')<<setw(9)<<Sta[j].IP;
        if(Sta[p].dst[j] == maxWeight && j != p)
            cout<<"    |"<<setfill(' ')<<setw(5)<<"���ɵ���";
        else
            cout<<"    |"<<setfill(' ')<<setw(5)<<Sta[p].dst[j];
        if(j != p)
        {
            if(Sta[p].dst[j] == maxWeight)
                cout<<" |"<<setfill(' ')<<setw(14);
            else
                cout<<"    |"<<setfill(' ')<<setw(7)<<Sta[ Sta[p].NextStation[j] ].ID;

            cout<<"      |"<<setfill(' ')<<setw(11)<<Sta[ Sta[p].NextStation[j] ].IP;
        }
        else
        {
            cout<<"    |"<<setfill(' ')<<setw(14);
            cout<<"|"<<setfill(' ')<<setw(11)<<"ֱ�ӽ���";
        }
        cout<<" |"<<endl;
    }
    cout<<"________________________________________________________________"<<endl;
    cout<<endl<<endl;
}



void Tree()
{
    int i,num = G.NumberOfVertices();
    //cout<<G.NumberOfVertices()<<endl;
    int p = 0;
    cout<<"������·�������:";
    cin>>i;
    //���װ��
    while(Sta[p].ID != i && p != 15)  p ++ ;
    if(p == 15)
        {cout<<"·���������ڣ�"<<endl<<endl;return;}
    cout<<"·����"<<Sta[p].ID<<"�����·��������Ϊ"<<endl;
    cout<<endl<<Sta[p].ID<<endl;
    Dijkstra(G,p,dist,path,Sta[p]);
    PrintTree(p,path,num,1);
    cout<<endl<<endl;
}

int PrintChoose()
{
    cout<<"*******************************"
        <<"*******************************"
        <<"*******************************"<<endl
        <<"1.�����  2.�����  3.ɾ����  4.ɾ����  "
        <<"5.�鿴ͼ 6.�鿴·�ɱ� 7.������ 8.�����޸�"<<endl
        <<"*******************************"
        <<"*******************************"
        <<"*******************************"<<endl
        <<"�������ֽ��в���( ):\b\b\b";
    int choose;
    cin>>choose;
    switch(choose)
    {
    case 0 : {cout<<"��лʹ�ã�"<<endl;return 0;}
    case 1 : InsertValue();break;
    case 2 : InsertWeight();break;
    case 3 : DeleteVertex();break;
    case 4 : DeleteEdge();break;
    case 5 : PrintGra();break;
    case 6 : Print();break;
    case 7 : Tree();break;
    case 8 : FileOut();break;
    default : cout<<"��������"<<endl;
    }
    return true;
}


#endif // FUNCTION_H_INCLUDED
