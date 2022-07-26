/*people类的定义*/
#include"people.h"
#include<iostream>
using namespace std;

//设置静态变量初始值
int people::currentNumber = 2022001;

//date类运算符重载
istream& operator>>(std::istream& input, date& d)
{
	input >> d.year;
	input >> d.month;
	input >> d.day;
	return input;
}

ostream& operator<<(std::ostream& output, date& d)
{
	output << d.year << '\t' << d.month << '\t' << d.day;
	return output;
}

date& date::operator=(const date& d)
{
	if (this == &d)
	{
		return *this;
	}
	year = d.year;
	month = d.month;
	day = d.day;
	return *this;
}

//输出人员的基本信息
void people::printInfo()
{
	cout << "编号\t姓名\t性别\tID\t\t出生日期" << endl;
	cout << number << '\t' << name << '\t' << sex << '\t' << id << "\t" << birthday << endl;
}

//更新、输入信息函数
void people::updateInfo()
{
	cout << "输入编号为" << number << "的人员的姓名、性别、ID、出生日期：" << endl;
	cin >> name;
	cin >> sex;
	cin >> id;
	cin >> birthday;
}

//无参构造函数
people::people()
{
	name = "Bob";
	number = currentNumber;
	currentNumber++;
	sex = "F";
	id = "622826200303080";
}

//含参构造函数
people::people(string inputName, int inputNumber, string inputSex, string inputId, date inputBirth)
{
	name = inputName;
	setPeoNo(inputNumber);
	sex = inputSex;
	birthday = inputBirth;
	id = inputId;
}

//拷贝构造函数
people::people(const people& p)
{
	name = p.name;
	number = p.number;
	sex = p.sex;
	birthday = p.birthday;
	id = p.id;
}

//析构函数
people::~people()
{
	//cout << "欢迎使用，再见！" << endl;
}

//重载运算符
istream& operator>>(std::istream& input, people& p)
{
	input >> p.number;
	input >> p.name;
	input >> p.sex;
	input >> p.id;
	input >> p.birthday;
	return input;
}

ostream& operator<<(std::ostream& output, people& p)
{
	cout << endl << p.number << '\t' << p.name << '\t' << p.sex << '\t' << p.id << '\t' << p.birthday;
	return output;
}

people& people::operator=(const people& p)
{
	if (this == &p)
	{
		return *this;
	}
	name = p.name;
	number = p.number;
	sex = p.sex;
	birthday = p.birthday;
	id = p.id;
	return *this;
}

//设置编号函数
void people::setPeoNo(int inputEmpNo)
{
	if (inputEmpNo <= 0)
	{
		number = currentNumber;
		currentNumber++;
	}
	else
	{
		if (inputEmpNo >= currentNumber)
			currentNumber = inputEmpNo + 1;
		if (number == currentNumber - 1 && inputEmpNo < number)
			currentNumber--;
		number = inputEmpNo;
	}
}