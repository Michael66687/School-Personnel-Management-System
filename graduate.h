#pragma once
#include"student.h"
#include"teacher.h"
#include"prof.h"

class graduate :virtual public student
{
public:
	graduate()
	{
		subject = "physics";
		advisor = NULL;
		advisorNo = -1;
	}
	graduate(string inputName, int inputNumber, string inputSex, string inputId, float inputScore, date inputBirth, string inputClassNo, string inputSubject, Prof* inputAdvisor);
	~graduate();

	//获取和设置专业
	void setSubject(string inputSubject) { subject = inputSubject; };
	string getSubject() { return subject; };

	//设置导师
	void setAdvisor(Prof* inputTeacher);
	void setAdvisorNo(int inputAdvisorNo) { advisorNo = inputAdvisorNo; };

	//获取导师
	teacher* getAdvisor() { return advisor; };
	int getAdvisorNo() { return advisorNo; };

	//输出信息
	virtual void printInfo();

	//更新、输入信息函数
	virtual void updateInfo();

	friend std::istream& operator>>(std::istream&, graduate&);
	friend std::ostream& operator<<(std::ostream&, graduate&);

private:
	string subject;

	//该研究生的导师
	Prof* advisor;
	//导师编号，用于之后设置人员关系
	int advisorNo;
};