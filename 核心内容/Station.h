#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED

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
        for(int i = 0 ; i < 10 ; i ++ )
            NextStation[i] = B.NextStation[i];
        return cout;
    }
};


Station Sta[15];               //路由器结构体


#endif // STATION_H_INCLUDED
