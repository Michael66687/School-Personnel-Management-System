#pragma once
#include"people.h"

class teacher :virtual public people
{
public:
	teacher() { accumPay = 3000; };
	teacher(string inputName, int inputNumber, string inputSex, string inputId, date inputBirth, float inputAccumPay);
	~teacher();

	//接口函数
	void setAccumPay(float inputAccumPay) { accumPay = inputAccumPay; };
	float getAccumPay() { return accumPay; };

	virtual void printInfo();//输出信息

	virtual float PAY();//计算工资

	//更新、输入信息函数
	virtual void updateInfo();

	friend std::istream& operator>>(std::istream&, teacher&);
	friend std::ostream& operator<<(std::ostream&, teacher&);
private:
	float accumPay;
};