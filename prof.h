#pragma once
#include"teacher.h"
#include"linkedlist.h"

class Prof :public teacher
{
public:
	Prof();
	Prof(string inputName, int inputNumber, string inputSex, string inputId, date inputBirth, float inputAccumPay, linkedlist<int>& inputNolist);
	~Prof();

	//输出信息
	virtual void printInfo();

	//更新、输入信息函数
	virtual void updateInfo();

	//计算工资
	virtual float PAY();

	//管理所带的研究生
	bool addgraduate(int graNo);
	bool deletegraduate(int graNo);
	void cleargraduate();

	//获取研究生编号链表
	linkedlist<int>getgraNolist() { return graNolist; };
	void setgraNolist(linkedlist<int>inputgraNolist) { graNolist = inputgraNolist; };

	//运算符重载
	friend std::istream& operator>>(std::istream&, Prof&);
	friend std::ostream& operator<<(std::ostream&, Prof&);

private:
	//使用链表保存教授所带的研究生
	linkedlist<int>graNolist;
};