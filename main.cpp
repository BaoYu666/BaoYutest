#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Graph.h"
#include "Function.h"
using namespace std;


using namespace std;


int main()
{
    cout<<endl<<"\t\t\t\t��ӭʹ��·�ɱ����ɲ�ѯϵͳ��"<<endl;
    FileIn();//���ļ�����
    while(1)
    {
        if(!PrintChoose()) break;
    }
}


