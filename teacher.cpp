/*teacher类的定义*/
#include"teacher.h"
#include<iostream>
using namespace std;

teacher::teacher(string inputName, int inputNumber, string inputSex, string inputId, date inputBirth, float inputAccumPay) :
	people(inputName, inputNumber, inputSex, inputId, inputBirth)
{
	accumPay = inputAccumPay;
}

teacher::~teacher()
{
	//cout << "欢迎使用，再见！" << endl;
}

void teacher::printInfo()
{
	date d;
	d = getBirth();
	cout << "编号\t姓名\t人员类型\t性别\tID\t\t月薪\t出生日期" << endl;
	cout << getPeoNo() << '\t' << getName() << '\t' << "教师" << '\t' << '\t' << getSex() << '\t' << getId() << '\t' << getAccumPay() << '\t' << d << endl << endl;
}

//更新、输入信息函数
void teacher::updateInfo()
{
	cout << "输入编号为" << getPeoNo() << "的教师的姓名、性别、ID、月薪、出生日期：" << endl;
	string name;
	float accumPay;
	string sex;
	string id;
	date birthday;

	cin >> name;
	cin >> sex;
	cin >> id;
	cin >> accumPay;
	cin >> birthday;

	setName(name);
	setAccumPay(accumPay);
	setSex(sex);
	setId(id);
	setBirth(birthday);

}

float teacher::PAY()
{
	setAccumPay(accumPay);
	return accumPay;
}

//运算符重载
istream& operator>>(std::istream& input, teacher& tea)
{
	//cout << "输入teacher类个人信息：" << endl;
	string name;
	int number;
	string sex;
	date birthday;
	string id;
	float accumPay;

	input >> number;
	input >> name;
	input >> sex;
	input >> id;
	input >> accumPay;
	input >> birthday;

	tea.setPeoNo(number);
	tea.setName(name);
	tea.setSex(sex);
	tea.setId(id);
	tea.setBirth(birthday);
	tea.setAccumPay(accumPay);

	return input;
}

ostream& operator<<(std::ostream& output, teacher& tea)
{
	date d;
	d = tea.getBirth();
	output << endl << tea.getPeoNo() << '\t' << tea.getName() << '\t' << tea.getSex() << '\t' << tea.getId() << '\t' << tea.getAccumPay() << '\t' << d;
	return output;
}