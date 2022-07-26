/*student类的定义*/
#include"student.h"
#include<string>
#include<iostream>
using namespace std;

//含参构造函数
student::student(string inputName, int inputNumber, string inputSex, string inputId, float inputScore, date inputBirth, string inputClassNo) :
	people(inputName, inputNumber, inputSex, inputId, inputBirth)
{
	classNo = inputClassNo;
	score = inputScore;
}

//析构函数
student::~student()
{
	//cout << "调用了student类析构函数" << endl;
}

//输出信息
void student::printInfo()
{
	date d;
	d = getBirth();
	cout << "编号\t姓名\t人员类型\t班级\t性别\tID\t\t综合成绩\t出生日期" << endl;
	cout << getPeoNo() << '\t' << getName() << '\t' << "学生" << '\t' << '\t' << getClassNo() << '\t' << getSex() << '\t' << getId() << '\t' << getScore() << '\t' << '\t' << d << endl << endl;
}

//更新、输入信息函数
void student::updateInfo()
{
	cout << "输入编号为" << getPeoNo() << "的学生的姓名、班级、性别、ID、综合成绩、出生日期：" << endl;
	string name;
	string classNo;
	string sex;
	string id;
	float score;
	date birthday;

	cin >> name;
	cin >> classNo;
	cin >> sex;
	cin >> id;
	cin >> score;
	cin >> birthday;

	setName(name);
	setClassNo(classNo);
	setSex(sex);
	setId(id);
	setScore(score);
	setBirth(birthday);
}

//运算符重载
istream& operator>>(istream& input, student& stu)
{
	string name;
	int number;
	string sex;
	date birthday;
	string id;
	float score;
	string classNo;

	input >> number;
	input >> name;
	input >> classNo;
	input >> sex;
	input >> id;
	input >> score;
	input >> birthday;

	stu.setPeoNo(number);
	stu.setName(name);
	stu.setClassNo(classNo);
	stu.setSex(sex);
	stu.setId(id);
	stu.setScore(score);
	stu.setBirth(birthday);

	return input;
}

ostream& operator<<(ostream& output, student& stu)
{
	date d;
	d = stu.getBirth();
	output << endl << stu.getPeoNo() << '\t' << stu.getName() << '\t' << stu.getClassNo() << '\t' << stu.getSex() << '\t' << stu.getId() << '\t' << stu.getScore() << '\t' << d;
	return output;
}