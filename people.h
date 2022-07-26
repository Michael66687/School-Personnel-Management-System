#pragma once
#include<string>
using std::string;

class date
{
public:
	date()
	{
		year = 2003;
		month = 3;
		day = 8;
	}
	date(int inputyear, int inputmonth, int inputday)
	{
		year = inputyear;
		month = inputmonth;
		day = inputday;
	}
	int year;
	int month;
	int day;
	friend std::istream& operator>>(std::istream& input, date& d);
	friend std::ostream& operator<<(std::ostream& output, date& d);
	date& operator=(const date& d);
};

class people
{
public:
	people();
	people(string inputName, int inputNumber, string inputSex, string inputId, date inputBirth);
	people(const people& p);
	~people();

	//访问数据成员的接口函数
	void setPeoNo(int inputNumber);
	void setName(string inputName) { name = inputName; };
	void setSex(string inputSex) { sex = inputSex; };
	void setBirth(date birth) { birthday = birth; };
	void setId(string inputId) { id = inputId; };
	int getPeoNo() { return number; };
	string getName() { return name; };
	string getSex() { return sex; };
	date getBirth() { return birthday; };
	string getId() { return id; };

	//输出人员信息
	virtual void printInfo();

	//更新、输入信息函数
	virtual void updateInfo();

	//运算符重载
	people& operator=(const people& p);
	friend std::istream& operator>>(std::istream&, people&);
	friend std::ostream& operator<<(std::ostream&, people&);
private:
	string name;
	int number;
	string sex;
	date birthday;
	string id;
	static int currentNumber;
};