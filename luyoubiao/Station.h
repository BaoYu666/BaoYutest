#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED

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
        for(int i = 0 ; i < 10 ; i ++ )
            NextStation[i] = B.NextStation[i];
        return cout;
    }
};


Station Sta[15];               //·�����ṹ��


#endif // STATION_H_INCLUDED
