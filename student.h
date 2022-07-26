#pragma once
#include"people.h"

class student :virtual public people
{
public:
	student()
	{
		classNo = "12";
		score = 100.00;
	}
	student(string inputName, int inputNumber, string inputSex, string inputId, float inputScore, date inputBirth, string inputClassNo);
	~student();

	//接口函数
	void setClassNo(string inputClassNo) { classNo = inputClassNo; };
	string getClassNo() { return classNo; };

	void setScore(float inputScore) { score = inputScore; };
	float getScore() { return score; };

	virtual void printInfo();//输出信息

	//更新、输入信息函数
	virtual void updateInfo();

	friend std::istream& operator>>(std::istream&, student&);
	friend std::ostream& operator<<(std::ostream&, student&);
private:
	string classNo;
	float score;
};