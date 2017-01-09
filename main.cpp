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
    cout<<endl<<"\t\t\t\t欢迎使用路由表生成查询系统！"<<endl;
    FileIn();//从文件导入
    while(1)
    {
        if(!PrintChoose()) break;
    }
}


