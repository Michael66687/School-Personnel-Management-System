/*TA类的定义*/
#include<iostream>
#include"TA.h"
using namespace std;

TA::TA(string inputName, int inputNumber, string inputSex, string inputId, float inputScore, date inputBirth, string inputClassNo, float inputAccumPay, string inputSubject, Prof* inputAdvisor, int inputRA) :
	teacher(inputName, inputNumber, inputSex, inputId, inputBirth, inputAccumPay),
	graduate(inputName, inputNumber, inputSex, inputId, inputScore, inputBirth, inputClassNo, inputSubject, inputAdvisor)
{
	RA = inputRA;
}

TA::~TA()
{
	//cout << "欢迎使用，再见！" << endl;
}

void TA::printInfo()
{
	cout << "编号\t姓名\t人员类型\t导师\t专业\t班级\t性别\tID\t\t综合成绩\t月薪\t补助\t出生日期" << endl;

	date d;
	d = getBirth();
	if (getAdvisor() == NULL)
	{
		cout << getPeoNo() << '\t' << getName() << '\t' << "助教" << '\t' << '\t' << "无" << '\t' << getSubject() << '\t' << getClassNo() << '\t' << getSex() << '\t' << getId() << '\t' << getScore() << '\t' << '\t' << getAccumPay() << '\t' << getRA() << '\t' << d << endl << endl;
	}
	else
	{	
		cout << getPeoNo() << '\t' << getName() << '\t' << "助教" << '\t' << '\t' << getAdvisor()->getPeoNo() << '\t' << getSubject() << '\t' << getClassNo() << '\t' << getSex() << '\t' << getId() << '\t' << getScore() << '\t' << '\t' << getAccumPay() << '\t' << getRA() << '\t' << d << endl << endl;
	}
}

//更新、输入信息函数
void TA::updateInfo()
{
	cout << "输入编号为" << getPeoNo() << "的助教的姓名、专业、班级、性别、ID、综合成绩、月薪、补助、出生日期：" << endl;
	string name;
	string sex;
	date birthday;
	string id;
	float score;
	float accumPay;
	int ra;
	string classNo;
	string subject;

	cin >> name;
	cin >> subject;
	cin >> classNo;
	cin >> sex;
	cin >> id;
	cin >> score;
	cin >> accumPay;
	cin >> ra;
	cin >> birthday;

	setName(name);
	setSubject(subject);
	setClassNo(classNo);
	setSex(sex);
	setId(id);
	setAccumPay(accumPay);
	setBirth(birthday);
	setScore(score);
	setRA(ra);
}

float TA::PAY()
{
	setAccumPay(getAccumPay());
	return getAccumPay();
}

istream& operator>>(std::istream& input, TA& ta)
{
	string name;
	int number;
	string sex;
	date birthday;
	string id;
	float score;
	float accumPay;
	string classNo;
	string subject;
	int advisorNo;
	int ra;

	input >> number;
	input >> name;
	input >> subject;
	input >> classNo;
	input >> sex;
	input >> id;
	input >> score;
	input >> accumPay;
	input >> ra;
	input >> advisorNo;
	input >> birthday;

	ta.setPeoNo(number);
	ta.setName(name);
	ta.setClassNo(classNo);
	ta.setSex(sex);
	ta.setId(id);
	ta.setBirth(birthday);
	ta.setScore(score);
	ta.setSubject(subject);
	ta.setAccumPay(accumPay);
	ta.setRA(ra);
	ta.setAdvisorNo(advisorNo);

	return input;
}

ostream& operator<<(std::ostream& output, TA& ta)
{
	date d;
	d = ta.getBirth();
	output << endl << ta.getPeoNo() << '\t' << ta.getName() << '\t' << ta.getSubject() << '\t' << ta.getClassNo() << '\t' << ta.getSex() << '\t' << ta.getId() << '\t' << ta.getScore() << '\t' << ta.getAccumPay() << '\t' << ta.getRA() << '\t' << ta.getAdvisorNo() << '\t' << d;
	return output;
}