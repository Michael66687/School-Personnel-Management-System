/*prof类的定义*/
#include<iostream>
#include"prof.h"
using namespace std;

Prof::Prof()
{
	graNolist.makeEmpty();
}

Prof::Prof(string inputName, int inputNumber, string inputSex, string inputId, date inputBirth, float inputAccumPay,linkedlist<int>&inputNolist) :
	people(inputName, inputNumber, inputSex, inputId, inputBirth)
{
	graNolist.makeEmpty();
	graNolist = inputNolist;
}

Prof::~Prof()
{
	graNolist.makeEmpty();
}

//增加研究生函数
bool Prof::addgraduate(int graNo)
{
	if (graNolist.find(graNo))
	{
		return false;
	}
	node<int>* d = new node<int>;
	d->data = graNo;
	graNolist.insert_end(d);
	return true;
}

//删除研究生函数
bool Prof::deletegraduate(int graNo)
{
	node<int>* node;
	node = graNolist.getFirst();
	if (node != NULL)
	{
		do
		{
			if (node->data == graNo)
			{
				graNolist.remove(node);
				return true;
			}
			node = graNolist.getNext();
		} while (node != NULL);
	}
	return false;
}

//清空研究生函数
void Prof::cleargraduate()
{
	graNolist.makeEmpty();
}

//输出信息函数
void Prof::printInfo()
{
	date d;
	d = getBirth();
	cout << "编号\t姓名\t人员类型\t性别\tID\t\t月薪\t出生日期" << endl;
	cout << getPeoNo() << '\t' << getName() << '\t' << "教授" << '\t' << '\t' << getSex() << '\t' << getId() << '\t' << getAccumPay() << '\t' << d << endl;
	cout << "所带研究生编号：" << endl;
	node<int>* node;
	node = graNolist.getFirst();
	if (node != NULL)
	{
		int count = 0;
		do
		{
			cout << node->data << '\t';
			count++;
			node = graNolist.getNext();
			//控制每行最多显示10个研究生编号
			if (count == 10)
			{
				cout << endl;
				count = 0;
			}
		} while (node != NULL);
		cout << endl << endl;
	}
	else
	{
		cout << "无" << endl << endl;
	}
}

//更新、输入信息函数，所带研究生信息通过设置函数更新
void Prof::updateInfo()
{
	cout << "输入编号为" << getPeoNo() << "的教授的姓名、性别、ID、月薪、出生日期：" << endl;
	string name;
	string sex;
	date birthday;
	string id;
	float accumPay;

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

float Prof::PAY()
{
	setAccumPay(getAccumPay());
	return getAccumPay();
}

//运算符重载
istream& operator>>(std::istream& input, Prof& pro)
{
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

	pro.setPeoNo(number);
	pro.setName(name);
	pro.setSex(sex);
	pro.setId(id);
	pro.setBirth(birthday);
	pro.setAccumPay(accumPay);

	return input;
}

ostream& operator<<(std::ostream& output, Prof& pro)
{
	date d;
	d = pro.getBirth();
	output << endl << pro.getPeoNo() << '\t' << pro.getName() << '\t' << pro.getSex() << '\t' << pro.getId() << '\t' << pro.getAccumPay() << '\t' << d;
	return output;
}