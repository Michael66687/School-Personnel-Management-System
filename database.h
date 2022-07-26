#pragma once
/*程序中作为数据库所使用的类的声明*/
#include<string>
#include"linkedlist.h"
#include"people.h"
#include"student.h"
#include"teacher.h"
#include"graduate.h"
#include"TA.h"
#include"prof.h"
#include"fileexception.h"
using std::string;

enum PeopleType
{
	PEOPLE_TYPE,
	STUDENT_TYPE,
	TEACHER_TYPE,
	GRADUATE_TYPE,
	TA_TYPE,
	PROF_TYPE,
};

//数据库类，对程序使用的数据结构进行封装
class database
{
private:
	//数据成员为不同种类雇员的对象链表
	linkedlist<student>stuList;
	linkedlist<teacher>teaList;
	linkedlist<graduate>gradList;
	linkedlist<TA>TAList;
	linkedlist<Prof>profList;
	//数据库密码
	string password;
public:
	//构造函数与析构函数
	database();
	~database();

	//文件读写函数
	void load();
	void save();

	//新建文件进行读写
	void save_new();

	//从指定文件中读取数据
	void load_new();

	//加载人员信息
	void loadStudent(const string& fileName);
	void loadTeacher(const string& fileName);
	void loadGraduate(const string& fileName);
	void loadTA(const string& fileName);
	void loadProf(const string& fileName);

	//加载数据库密码
	void loadPassWord(const string& fileName);

	//保存人员信息
	void saveStudent(const string& fileName);
	void saveTeacher(const string& fileName);
	void saveGraduate(const string& fileName);
	void saveTA(const string& fileName);
	void saveProf(const string& fileName);

	//保存数据库密码
	void savePassWord(const string& fileName);

	//删除人员函数,可根据id进行删除
	bool deletePeople(const string& id);

	//添加人员函数。由于每类人员信息不同，各有不同的添加函数
	void addStudent();
	void addTeacher();
	void addGraduate();
	void addTA();
	void addProf();

	//排序函数，可按编号或工资，或学生综合成绩排序
	void sortByPay(enum PeopleType, int direction);
	void sortByNo(enum PeopleType, int direction);
	void sortByScore(enum PeopleType, int direction);
	//基础排序函数
	void sortNo(people** head, int length, int direction);
	void sortPay(teacher** head, int length, int direction);
	void sortScore(student** head, int length, int direction);
	//比较函数
	int compareNo(people* p1, people* p2, int direction);
	int comparePay(teacher* t1, teacher* t2, int direction);
	int compareScore(student* s1, student* s2, int direction);

	//设置导师和研究生的关系
	bool setRelationship(int gradNo, int profNo);

	//显示所有人员
	int showAll(enum PeopleType);

	//用于用户操作的添加人员函数
	void addPeople(enum PeopleType);

	//更新信息函数
	bool updatePeople(const string& id);

	//查找函数，可按编号、id或姓名查找,返回查找到的人员数量
	int search_No(const int& No);
	int search_id(const string& id);
	int search_name(const string& name);

	//清空数据库
	bool deleteAll();

	//设置数据库密码
	bool setPassword(const string& inputPassword);

	//获取数据库密码
	string getPassword() { return password; };

};