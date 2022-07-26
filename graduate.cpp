/*graduate类的定义*/
#include"database.h"
#include"graduate.h"
#include<iostream>
using namespace std;

graduate::graduate(string inputName, int inputNumber, string inputSex, string inputId, float inputScore, date inputBirth, string inputClassNo, string inputSubject, Prof* inputAdvisor) :
	student(inputName, inputNumber, inputSex, inputId, inputScore, inputBirth, inputClassNo)
{
	subject = inputSubject;
	advisor = inputAdvisor;
}

graduate::~graduate()
{
	//cout << "调用了graduate类析构函数" << endl;
}

void graduate::printInfo()
{
	cout << "编号\t姓名\t人员类型\t导师\t专业\t班级\t性别\tID\t\t综合成绩\t出生日期" << endl;

	date d;
	d = getBirth();
	if (getAdvisor() == NULL)
	{
		cout << getPeoNo() << '\t' << getName() << '\t' << "研究生" << '\t' << '\t' << "无" << '\t' << getSubject() << '\t' << getClassNo() << '\t' << getSex() << '\t' << getId() << '\t' << getScore() << '\t' << '\t' << d << endl << endl;
	}
	else
	{
		advisorNo = getAdvisor()->getPeoNo();
		cout << getPeoNo() << '\t' << getName() << '\t' << "研究生" << '\t' << '\t' << advisorNo << '\t' << getSubject() << '\t' << getClassNo() << '\t' << getSex() << '\t' << getId() << '\t' << getScore() << '\t' << '\t' << d << endl << endl;
	}
}

//设置导师函数
void graduate::setAdvisor(Prof* inputAdvisor)
{
	if (advisor != NULL)
	{
		advisor->deletegraduate(getPeoNo());
	}
	if (inputAdvisor != NULL)
	{
		inputAdvisor->addgraduate(getPeoNo());
	}
	advisor = inputAdvisor;
	advisorNo = inputAdvisor->getPeoNo();
}

//更新、输入信息函数,导师信息通过关系设置函数更新
void graduate::updateInfo()
{
	cout << "输入编号为" << getPeoNo() << "的研究生的姓名、专业、班级、性别、ID、综合成绩、出生日期" << endl;
	string name;
	string sex;
	date birthday;
	string id;
	float score;
	string classNo;
	string subject;

	cin >> name;
	cin >> subject;
	cin >> classNo;
	cin >> sex;
	cin >> id;
	cin >> score;
	cin >> birthday;

	setName(name);
	setSubject(subject);
	setClassNo(classNo);
	setSex(sex);
	setId(id);
	setScore(score);
	setBirth(birthday);
}

//运算符重载
istream& operator>>(std::istream& input, graduate& gra)
{
	string name;
	int number;
	string sex;
	date birthday;
	string id;
	float score;
	string classNo;
	string subject;
	int advisorNo;

	input >> number;
	input >> name;
	input >> subject;
	input >> classNo;
	input >> sex;
	input >> id;
	input >> score;
	input >> advisorNo;
	input >> birthday;

	gra.setPeoNo(number);
	gra.setName(name);
	gra.setClassNo(classNo);
	gra.setSex(sex);
	gra.setId(id);
	gra.setScore(score);
	gra.setBirth(birthday);
	gra.setSubject(subject);
	gra.setAdvisorNo(advisorNo);

	return input;
}

ostream& operator<<(std::ostream& output, graduate& gra)
{
	date d;
	d = gra.getBirth();
	int advisorNo;
	if (gra.getAdvisor() == NULL)
	{
		advisorNo = -1;
	}
	else
	{
		advisorNo = gra.getAdvisor()->getPeoNo();
	}
	output << endl << gra.getPeoNo() << '\t' << gra.getName() << '\t' << gra.getSubject() << '\t' << gra.getClassNo() << '\t' << gra.getSex() << '\t' << gra.getId() << '\t' << gra.getScore() << '\t' << advisorNo << '\t' << d;
	return output;
}