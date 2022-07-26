#pragma once
/*程序内封装用户界面所使用的类的声明*/
#include"database.h"

//用户界面类
class userinterface
{
private:
	database* people_database;
public:
	userinterface();
	~userinterface();

	//运行与交互主函数
	bool running();

	//功能函数，欢迎 退出 增删查改 排序 增和改考虑要按照不同类型雇员进行扩展
	void welcome();
	bool start();
	bool searchPeople();//查找人员
	bool insertPeople();//录入人员
	bool deletePeople();//删除人员
	bool updatePeople();//更新人员信息
	bool saveInfo();//保存人员信息
	bool saveInfo_new();//在新建文件中保存人员信息
	bool loadnew();//从指定文件中重新加载
	bool showAll();//显示某一类人员
	bool deleteDatabase();//清空当前数据库
	bool setPassword();//设置密码
	bool setRelationship();//设置导师与研究生关系
	bool sortPeople();//排序人员信息
	void quit();

	//暂停函数
	void pause();
};