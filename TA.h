#pragma once
#include"graduate.h"
#include"teacher.h"

class TA :public teacher, public graduate
{
public:
	TA() { RA = 2000; };
	TA(string inputName, int inputNumber, string inputSex, string inputId, float inputScore, date inputBirth, string inputClassNo, float inputAccumPay, string inputSubject, Prof* inputAdvisor, int inputRA);
	~TA();

	//接口函数
	void setRA(int inputRA) { RA = inputRA; };
	int getRA() { return RA; };

	//输出信息
	virtual void printInfo();

	//更新、输入信息函数
	virtual void updateInfo();

	//计算工资
	virtual float PAY();

	//运算符重载
	friend std::istream& operator>>(std::istream&, TA&);
	friend std::ostream& operator<<(std::ostream&, TA&);

private:
	int RA;
};