/*程序主函数文件*/
#include<iostream>
#include<fstream>
#include"database.h"
#include"userinterface.h"
using namespace std;

int main()
{
	system("mode con cols=140");

	userinterface ui;

	while (ui.start());

	while (ui.running());
	
	return 0;

}
/*共4450行左右*/