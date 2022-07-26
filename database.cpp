/*database类的定义*/
#include<iostream>
#include<fstream>
#include <cstdio>
#include"database.h"
using namespace std;

//构造函数
database::database()
{
	stuList.makeEmpty();
	teaList.makeEmpty();
	gradList.makeEmpty();
	TAList.makeEmpty();
	profList.makeEmpty();
}

//析构函数
database::~database()
{
	stuList.makeEmpty();
	teaList.makeEmpty();
	gradList.makeEmpty();
	TAList.makeEmpty();
	profList.makeEmpty();
}

//从文件中读取
void database::load()
{
	//从文件中读取一个字符，以判断文件是否为空
	ifstream stuf("info_student.txt", ios::in);
	ifstream teaf("info_teacher.txt", ios::in);
	ifstream gradf("info_graduate.txt", ios::in);
	ifstream taf("info_TA.txt", ios::in);
	ifstream proff("info_prof.txt", ios::in);
	ifstream passf("password.txt", ios::in);
	char check;
	stuf >> check;
	teaf >> check;
	gradf >> check;
	taf >> check;
	proff >> check;
	passf >> check;
	try
	{
		if (!stuf.eof())
		{
			stuf.close();
			loadStudent("info_student.txt");
		}
		else
		{
			stuf.close();
		}

		if (!teaf.eof())
		{
			teaf.close();
			loadTeacher("info_teacher.txt");
		}
		else
		{
			teaf.close();
		}

		if (!gradf.eof())
		{
			gradf.close();
			loadGraduate("info_graduate.txt");
		}
		else
		{
			gradf.close();
		}

		if (!taf.eof())
		{
			taf.close();
			loadTA("info_TA.txt");
		}
		else
		{
			taf.close();
		}

		if (!proff.eof())
		{
			proff.close();
			loadProf("info_prof.txt");
		}
		else
		{
			proff.close();
		}

		if (!passf.eof())
		{
			passf.close();
			loadPassWord("password.txt");
		}
		else
		{
			// 文件为空，需要设置初始密码
			passf.close();
			ofstream passSet("password.txt", ios::out);
			passSet << endl << "000000";
			passSet.close();
			loadPassWord("password.txt");
		}

	}
	catch (FileException e)
	{
		throw e;
	}

	//通过编号设置导师与研究生、助教关系
	node<Prof>* prof;
	node<graduate>* grad;
	node<TA>* ta;
	Prof* p;
	grad = gradList.getFirst();
	if (grad != NULL)
	{
		do
		{
			prof = profList.getFirst();
			if (prof != NULL)
			{
				do
				{
					if (prof->data.getPeoNo() == grad->data.getAdvisorNo())
					{
						p = &prof->data;
						grad->data.setAdvisor(p);
					}
					prof = profList.getNext();
				} while (prof != NULL);
			}
			grad = gradList.getNext();
		} while (grad != NULL);
	}
	ta = TAList.getFirst();
	if (ta != NULL)
	{
		do
		{
			prof = profList.getFirst();
			if (prof != NULL)
			{
				do
				{
					if (prof->data.getPeoNo() == ta->data.getAdvisorNo())
					{
						p = &prof->data;
						ta->data.setAdvisor(p);
					}
					prof = profList.getNext();
				} while (prof != NULL);
			}
			ta = TAList.getNext();
		} while (ta != NULL);
	}
}

//向文件中保存
void database::save()
{
	try
	{
		saveStudent("info_student.txt");
		saveTeacher("info_teacher.txt");
		saveGraduate("info_graduate.txt");
		saveTA("info_TA.txt");
		saveProf("info_prof.txt");
		savePassWord("password.txt");
	}
	catch (FileException e)
	{
		throw e;
	}
}

//向新建文件中保存
void database::save_new()
{
	string stuFilename, teaFilename, gradFilename, taFilename, profFilename;
	cout << "请输入用于储存学生数据的新建文件名（格式为.txt）" << endl;
	cin >> stuFilename;
	cout << "请输入用于储存教师数据的新建文件名（格式为.txt）" << endl;
	cin >> teaFilename;
	cout << "请输入用于储存研究生数据的新建文件名（格式为.txt）" << endl;
	cin >> gradFilename;
	cout << "请输入用于储存助教数据的新建文件名（格式为.txt）" << endl;
	cin >> taFilename;
	cout << "请输入用于储存教授数据的新建文件名（格式为.txt）" << endl;
	cin >> profFilename;
	try
	{
		saveStudent(stuFilename);
		saveTeacher(teaFilename);
		saveGraduate(gradFilename);
		saveTA(taFilename);
		saveProf(profFilename);
		savePassWord("password.txt");
	}
	catch (FileException e)
	{
		throw e;
	}
}

//从指定文件中读取数据
void database::load_new()
{
	string stuFilename, teaFilename, gradFilename, taFilename, profFilename;
	cout << "请输入读取学生数据的文件名（格式为.txt）" << endl;
	cin >> stuFilename;
	cout << "请输入读取教师数据的新建文件名（格式为.txt）" << endl;
	cin >> teaFilename;
	cout << "请输入读取研究生数据的新建文件名（格式为.txt）" << endl;
	cin >> gradFilename;
	cout << "请输入读取助教数据的新建文件名（格式为.txt）" << endl;
	cin >> taFilename;
	cout << "请输入读取教授数据的新建文件名（格式为.txt）" << endl;
	cin >> profFilename;

	//从文件中读取一个字符，以判断文件是否为空
	ifstream stuf(stuFilename, ios::in);
	ifstream teaf(teaFilename, ios::in);
	ifstream gradf(gradFilename, ios::in);
	ifstream taf(taFilename, ios::in);
	ifstream proff(profFilename, ios::in);
	ifstream passf("password.txt", ios::in);
	char check;
	stuf >> check;
	teaf >> check;
	gradf >> check;
	taf >> check;
	proff >> check;
	passf >> check;
	try
	{
		if (!stuf.eof())
		{
			stuf.close();
			loadStudent(stuFilename);
		}
		else
		{
			stuf.close();
		}

		if (!teaf.eof())
		{
			teaf.close();
			loadTeacher(teaFilename);
		}
		else
		{
			teaf.close();
		}

		if (!gradf.eof())
		{
			gradf.close();
			loadGraduate(gradFilename);
		}
		else
		{
			gradf.close();
		}

		if (!taf.eof())
		{
			taf.close();
			loadTA(taFilename);
		}
		else
		{
			taf.close();
		}

		if (!proff.eof())
		{
			proff.close();
			loadProf(profFilename);
		}
		else
		{
			proff.close();
		}

		if (!passf.eof())
		{
			passf.close();
			loadPassWord("password.txt");
		}
		else
		{
			// 能够调用load_new函数时说明程序已经不是第一次运行，理论上不需要再设置初始密码
			// 但为了防止文件被恶意或意外修改，此处仍保留了密码文件为空时的解决方法
			passf.close();
			ofstream passSet("password.txt", ios::out);
			passSet << endl << "000000";
			passSet.close();
			loadPassWord("password.txt");
		}

	}
	catch (FileException e)
	{
		throw e;
	}

	//通过编号设置导师与研究生、助教关系
	node<Prof>* prof;
	node<graduate>* grad;
	node<TA>* ta;
	Prof* p;
	grad = gradList.getFirst();
	if (grad != NULL)
	{
		do
		{
			prof = profList.getFirst();
			if (prof != NULL)
			{
				do
				{
					if (prof->data.getPeoNo() == grad->data.getAdvisorNo())
					{
						p = &prof->data;
						grad->data.setAdvisor(p);
					}
					prof = profList.getNext();
				} while (prof != NULL);
			}
			grad = gradList.getNext();
		} while (grad != NULL);
	}
	ta = TAList.getFirst();
	if (ta != NULL)
	{
		do
		{
			prof = profList.getFirst();
			if (prof != NULL)
			{
				do
				{
					if (prof->data.getPeoNo() == ta->data.getAdvisorNo())
					{
						p = &prof->data;
						ta->data.setAdvisor(p);
					}
					prof = profList.getNext();
				} while (prof != NULL);
			}
			ta = TAList.getNext();
		} while (ta != NULL);
	}
}

//从文件中读取学生信息
void database::loadStudent(const string& fileName)
{
	ifstream in(fileName.c_str(), ios::in);

	node<student>* stu;
	if (in)
	{
		while (!in.eof())
		{
			stu = new node<student>;
			if (in >> stu->data)
			{
				stuList.insert_end(stu);
			}
			else
			{
				FileException e(fileName, "operator", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(fileName, "open", "read");
		throw e;
	}
	in.close();
}

//从文件中读取教师信息
void database::loadTeacher(const string& fileName)
{
	ifstream in(fileName.c_str(), ios::in);

	node<teacher>* tea;
	if (in)
	{
		while (!in.eof())
		{
			tea = new node<teacher>;
			if (in >> tea->data)
			{
				teaList.insert_end(tea);
			}
			else
			{
				FileException e(fileName, "operator", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(fileName, "open", "read");
		throw e;
	}
	in.close();
}

//从文件中读取研究生信息
void database::loadGraduate(const string& fileName)
{
	ifstream in(fileName.c_str(), ios::in);

	node<graduate>* grad;
	if (in)
	{
		while (!in.eof())
		{
			grad = new node<graduate>;
			if (in >> grad->data)
			{
				gradList.insert_end(grad);
			}
			else
			{
				FileException e(fileName, "operator", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(fileName, "open", "read");
		throw e;
	}
	in.close();
}

//从文件中读取助教信息
void database::loadTA(const string& fileName)
{
	ifstream in(fileName.c_str(), ios::in);

	node<TA>* ta;
	if (in)
	{
		while (!in.eof())
		{
			ta = new node<TA>;
			if (in >> ta->data)
			{
				TAList.insert_end(ta);
			}
			else
			{
				FileException e(fileName, "operator", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(fileName, "open", "read");
		throw e;
	}
	in.close();
}

//从文件中读取教授信息
void database::loadProf(const string& fileName)
{
	ifstream in(fileName.c_str(), ios::in);

	node<Prof>* prof;
	if (in)
	{
		while (!in.eof())
		{
			prof = new node<Prof>;
			if (in >> prof->data)
			{
				profList.insert_end(prof);
			}
			else
			{
				FileException e(fileName, "operator", "read");
				throw e;
			}
		}
	}
	else
	{
		FileException e(fileName, "open", "read");
		throw e;
	}
	in.close();
}

//从文件中读取密码
void database::loadPassWord(const string& fileName)
{
	ifstream in(fileName.c_str(), ios::in);
	if (in)
	{
		if (!(in >> password))
		{
			FileException e(fileName, "operator", "read");
			throw e;
		}
	}
	else
	{
		FileException e(fileName, "operator", "read");
		throw e;
	}
	in.close();
}

//向文件中保存学生信息
void database::saveStudent(const string& fileName)
{
	ofstream out(fileName.c_str(), ios::out | ios::trunc);
	node<student>* stu;
	if (out)
	{
		stu = stuList.getFirst();
		while (stu != NULL)
		{
			if (!(out << stu->data))
			{
				FileException e(fileName, "operator", "write");
				throw e;
			}
			stu = stuList.getNext();
		}
	}
	else
	{
		FileException e(fileName, "open", "write");
		throw e;
	}
	out.close();
}

//向文件中保存教师信息
void database::saveTeacher(const string& fileName)
{
	ofstream out(fileName.c_str(), ios::out | ios::trunc);
	node<teacher>* tea;
	if (out)
	{
		tea = teaList.getFirst();
		while (tea != NULL)
		{
			if (!(out << tea->data))
			{
				FileException e(fileName, "operator", "write");
				throw e;
			}
			tea = teaList.getNext();
		}
	}
	else
	{
		FileException e(fileName, "open", "write");
		throw e;
	}
	out.close();
}

//向文件中保存研究生信息
void database::saveGraduate(const string& fileName)
{
	ofstream out(fileName.c_str(), ios::out | ios::trunc);
	node<graduate>* grad;
	if (out)
	{
		grad = gradList.getFirst();
		while (grad != NULL)
		{
			if (!(out << grad->data))
			{
				FileException e(fileName, "operator", "write");
				throw e;
			}
			grad = gradList.getNext();
		}
	}
	else
	{
		FileException e(fileName, "open", "write");
		throw e;
	}
	out.close();
}

//向文件中保存助教信息
void database::saveTA(const string& fileName)
{
	ofstream out(fileName.c_str(), ios::out | ios::trunc);
	node<TA>* ta;
	if (out)
	{
		ta = TAList.getFirst();
		while (ta != NULL)
		{
			if (!(out << ta->data))
			{
				FileException e(fileName, "operator", "write");
				throw e;
			}
			ta = TAList.getNext();
		}
	}
	else
	{
		FileException e(fileName, "open", "write");
		throw e;
	}
	out.close();
}

//向文件中保存教授信息
void database::saveProf(const string& fileName)
{
	ofstream out(fileName.c_str(), ios::out | ios::trunc);
	node<Prof>* prof;
	if (out)
	{
		prof = profList.getFirst();
		while (prof != NULL)
		{
			if (!(out << prof->data))
			{
				FileException e(fileName, "operator", "write");
				throw e;
			}
			prof = profList.getNext();
		}
	}
	else
	{
		FileException e(fileName, "open", "write");
		throw e;
	}
	out.close();
}

//向文件中保存密码
void database::savePassWord(const string& fileName)
{
	ofstream out(fileName.c_str(), ios::out | ios::trunc);
	if (out)
	{
		out << endl;
		if (!(out << password))
		{
			FileException e(fileName, "operator", "write");
			throw e;
		}
	}
	else
	{
		FileException e(fileName, "open", "write");
		throw e;
	}
	out.close();
}

//以id为准删除雇员
bool database::deletePeople(const string& id)
{
	node<student>* stu;
	node<teacher>* tea;
	node<graduate>* grad;
	node<TA>* ta;
	node<Prof>* prof;
	bool flag = false;

	stu = stuList.getFirst();
	if (stu != NULL)
	{
		do
		{
			if (stu->data.getId() == id)
			{
				stu->data.printInfo();
				cout << "按Y/y确认删除：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					stuList.remove(stu);
					flag = true;
					cout << "删除成功。" << endl;
				}
				else
				{
					cout << "放弃删除。" << endl;
				}
			}
			stu = stuList.getNext();
		} while (stu != NULL);
	}

	tea = teaList.getFirst();
	if (tea != NULL)
	{
		do
		{
			if (tea->data.getId() == id)
			{
				tea->data.printInfo();
				cout << "按Y/y确认删除：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					teaList.remove(tea);
					flag = true;
					cout << "删除成功。" << endl;
				}
				else
				{
					cout << "放弃删除。" << endl;
				}
			}
			tea = teaList.getNext();
		} while (tea != NULL);
	}

	grad = gradList.getFirst();
	if (grad != NULL)
	{
		do
		{
			if (grad->data.getId() == id)
			{
				grad->data.printInfo();
				cout << "按Y/y确认删除：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					gradList.remove(grad);
					flag = true;
					cout << "删除成功。" << endl;
				}
				else
				{
					cout << "放弃删除。" << endl;
				}
			}
			grad = gradList.getNext();
		} while (grad != NULL);
	}

	ta = TAList.getFirst();
	if (ta != NULL)
	{
		do
		{
			if (ta->data.getId() == id)
			{
				ta->data.printInfo();
				cout << "按Y/y确认删除：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					TAList.remove(ta);
					flag = true;
					cout << "删除成功。" << endl;
				}
				else
				{
					cout << "放弃删除。" << endl;
				}
			}
			ta = TAList.getNext();
		} while (ta != NULL);
	}

	prof = profList.getFirst();
	if (prof != NULL)
	{
		do
		{
			if (prof->data.getId() == id)
			{
				prof->data.printInfo();
				cout << "按Y/y确认删除：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					grad = gradList.getFirst();
					if (grad != NULL)
					{
						do
						{
							if (grad->data.getAdvisorNo() == prof->data.getPeoNo())
							{
								grad->data.setAdvisor(NULL);
								grad->data.setAdvisorNo(-1);
							}
							grad = gradList.getNext();
						} while (grad != NULL);
					}
					profList.remove(prof);
					flag = true;
					cout << "删除成功。" << endl;
				}
				else
				{
					cout << "放弃删除。" << endl;
				}
			}
			prof = profList.getNext();
		} while (prof != NULL);
	}

	return flag;
}

//新增学生
void database::addStudent()
{
	node<student>* stu = new node<student>;
	stu->data.updateInfo();
	stuList.insert_end(stu);
}

//新增教师
void database::addTeacher()
{
	node<teacher>* tea = new node<teacher>;
	tea->data.updateInfo();
	teaList.insert_end(tea);
}

//新增研究生
void database::addGraduate()
{
	node<graduate>* grad = new node<graduate>;
	grad->data.updateInfo();
	gradList.insert_end(grad);
}

//新增助教
void database::addTA()
{
	node<TA>* ta = new node<TA>;
	ta->data.updateInfo();
	TAList.insert_end(ta);
}

//新增教授
void database::addProf()
{
	node<Prof>* prof = new node<Prof>;
	prof->data.updateInfo();
	profList.insert_end(prof);
}

//用于用户操作的添加人员函数
void database::addPeople(PeopleType p)
{
	switch (p)
	{
	case STUDENT_TYPE:
		addStudent();
		break;
	case TEACHER_TYPE:
		addTeacher();
		break;
	case GRADUATE_TYPE:
		addGraduate();
		break;
	case TA_TYPE:
		addTA();
		break;
	case PROF_TYPE:
		addProf();
		break;
	default:
		cout << "输入类型错误。" << endl;
		break;
	}
}

//基础编号排序函数
void database::sortNo(people** head, int length, int direction)
{
	people* tmp;
	bool flag;
	do
	{
		flag = false;
		for (int i = 0; i < length - 1; i++)
		{
			if (compareNo(head[i], head[i + 1], direction) < 0)
			{
				tmp = head[i];
				head[i] = head[i + 1];
				head[i + 1] = tmp;
				flag = true;
			}
		}
	} while (flag);
}

//基础工资排序函数
void database::sortPay(teacher** head, int length, int direction)
{
	teacher* tmp;
	bool flag;
	do
	{
		flag = false;
		for (int i = 0; i < length - 1; i++)
		{
			if (comparePay(head[i], head[i + 1], direction) < 0)
			{
				tmp = head[i];
				head[i] = head[i + 1];
				head[i + 1] = tmp;
				flag = true;
			}
		}
	} while (flag);
}

//基础成绩排序函数
void database::sortScore(student** head, int length, int direction)
{
	student* tmp;
	bool flag;
	do
	{
		flag = false;
		for (int i = 0; i < length - 1; i++)
		{
			if (compareScore(head[i], head[i + 1], direction) < 0)
			{
				tmp = head[i];
				head[i] = head[i + 1];
				head[i + 1] = tmp;
				flag = true;
			}
		}
	} while (flag);
}

//编号比较函数
int database::compareNo(people* p1, people* p2, int direction)
{
	int compareNo = p1->getPeoNo() - p2->getPeoNo();
	return compareNo * direction;
}

//工资比较函数
int database::comparePay(teacher* t1, teacher* t2, int direction)
{
	int comparePay = t1->getAccumPay() - t2->getAccumPay();
	return comparePay * direction;
}

//成绩比较函数
int database::compareScore(student* s1, student* s2, int direction)
{
	int compareScore = s1->getScore() - s2->getScore();
	return compareScore * direction;
}

//按成绩排序函数
void database::sortByScore(PeopleType p, int direction)
{
	student** head;
	int length = 0;
	switch (p)
	{
	case STUDENT_TYPE:
		length = stuList.size();
		if (length > 0)
		{
			head = new student * [length];
			node<student>* tmp = stuList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = stuList.getNext();
				count++;
			} while (tmp != NULL);
			sortScore(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "学生数量为零。" << endl;
		}
		break;
		//由于教师没有成绩数据成员，故跳过
	case TEACHER_TYPE:
		length = gradList.size();
		if (length > 0)
		{
			head = new student * [length];
			node<graduate>* tmp = gradList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = gradList.getNext();
				count++;
			} while (tmp != NULL);
			sortScore(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "研究生数量为零。" << endl;
		}
		break;
	case GRADUATE_TYPE:
		length = TAList.size();
		if (length > 0)
		{
			head = new student * [length];
			node<TA>* tmp = TAList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = TAList.getNext();
				count++;
			} while (tmp != NULL);
			sortScore(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "助教数量为零。" << endl;
		}
		break;
	}
}

//按工资排序函数
void database::sortByPay(PeopleType p, int direction)
{
	teacher** head;
	int length = 0;
	switch (p)
	{
	case TEACHER_TYPE:
		length = teaList.size();
		if (length > 0)
		{
			head = new teacher * [length];
			node<teacher>* tmp = teaList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = teaList.getNext();
				count++;
			} while (tmp != NULL);
			sortPay(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "教师数量为零。" << endl;
		}
		break;
		//由于助教没有工资数据成员，故跳过
	case GRADUATE_TYPE:
		length = TAList.size();
		if (length > 0)
		{
			head = new teacher * [length];
			node<TA>* tmp = TAList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = TAList.getNext();
				count++;
			} while (tmp != NULL);
			sortPay(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "助教数量为零。" << endl;
		}
		break;
	case TA_TYPE:
		length = profList.size();
		if (length > 0)
		{
			head = new teacher * [length];
			node<Prof>* tmp = profList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = profList.getNext();
				count++;
			} while (tmp != NULL);
			sortPay(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "教授数量为零。" << endl;
		}
		break;
	default:
		cout << "输入错误！" << endl;
		break;
	}
}

//按编号排序函数
void database::sortByNo(PeopleType p, int direction)
{
	people** head;
	int length = 0;
	switch (p)
	{
	case PEOPLE_TYPE:
		length = stuList.size() + teaList.size() + gradList.size() + TAList.size() + profList.size();
		if (length > 0)
		{
			head = new people * [length];
			int count = 0;
			node<student>* stu = stuList.getFirst();
			if (stu != NULL)
			{
				do
				{
					head[count] = &stu->data;
					stu = stuList.getNext();
					count++;
				} while (stu != NULL);
			}
			node<teacher>* tea = teaList.getFirst();
			if (tea != NULL)
			{
				do
				{
					head[count] = &tea->data;
					tea = teaList.getNext();
					count++;
				} while (tea != NULL);
			}
			node<graduate>* grad = gradList.getFirst();
			if (grad != NULL)
			{
				do
				{
					head[count] = &grad->data;
					grad = gradList.getNext();
					count++;
				} while (grad != NULL);
			}
			node<TA>* ta = TAList.getFirst();
			if (ta != NULL)
			{
				do
				{
					head[count] = &ta->data;
					ta = TAList.getNext();
					count++;
				} while (ta != NULL);
			}
			node<Prof>* prof = profList.getFirst();
			if (prof != NULL)
			{
				do
				{
					head[count] = &prof->data;
					prof = profList.getNext();
					count++;
				} while (prof != NULL);
			}
			sortNo(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "系统内人员数量为零！" << endl;
		}
		break;
	case STUDENT_TYPE:
		length = stuList.size();
		if (length > 0)
		{
			head = new people * [length];
			node<student>* tmp = stuList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = stuList.getNext();
				count++;
			} while (tmp != NULL);
			sortNo(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "学生数量为零。" << endl;
		}
		break;
	case TEACHER_TYPE:
		length = teaList.size();
		if (length > 0)
		{
			head = new people * [length];
			node<teacher>* tmp = teaList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = teaList.getNext();
				count++;
			} while (tmp != NULL);
			sortNo(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "教师数量为零。" << endl;
		}
		break;
	case GRADUATE_TYPE:
		length = gradList.size();
		if (length > 0)
		{
			head = new people * [length];
			node<graduate>* tmp = gradList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = gradList.getNext();
				count++;
			} while (tmp != NULL);
			sortNo(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "研究生数量为零。" << endl;
		}
		break;
	case TA_TYPE:
		length = TAList.size();
		if (length > 0)
		{
			head = new people * [length];
			node<TA>* tmp = TAList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = TAList.getNext();
				count++;
			} while (tmp != NULL);
			sortNo(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "助教数量为零。" << endl;
		}
		break;
	case PROF_TYPE:
		length = profList.size();
		if (length > 0)
		{
			head = new people * [length];
			node<Prof>* tmp = profList.getFirst();
			int count = 0;
			do
			{
				head[count] = &tmp->data;
				tmp = profList.getNext();
				count++;
			} while (tmp != NULL);
			sortNo(head, length, direction);
			for (int i = 0; i < length; i++)
			{
				head[i]->printInfo();
			}
			delete[]head;
		}
		else
		{
			cout << "教授数量为零。" << endl;
		}
		break;
	default:
		cout << "输入错误！" << endl;
		break;
	}
}

//按编号查找人员
int database::search_No(const int& No)
{
	node<student>* stu;
	node<teacher>* tea;
	node<graduate>* grad;
	node<TA>* ta;
	node<Prof>* prof;
	int count = 0;

	stu = stuList.getFirst();
	if (stu != NULL)
	{
		do
		{
			if (stu->data.getPeoNo() == No)
			{
				stu->data.printInfo();
				count++;
			}
			stu = stuList.getNext();
		} while (stu != NULL);
	}

	tea = teaList.getFirst();
	if (tea != NULL)
	{
		do
		{
			if (tea->data.getPeoNo() == No)
			{
				tea->data.printInfo();
				count++;
			}
			tea = teaList.getNext();
		} while (tea != NULL);
	}

	grad = gradList.getFirst();
	if (grad != NULL)
	{
		do
		{
			if (grad->data.getPeoNo() == No)
			{
				grad->data.printInfo();
				count++;
			}
			grad = gradList.getNext();
		} while (grad != NULL);
	}

	ta = TAList.getFirst();
	if (ta != NULL)
	{
		do
		{
			if (ta->data.getPeoNo() == No)
			{
				ta->data.printInfo();
				count++;
			}
			ta = TAList.getNext();
		} while (ta != NULL);
	}

	prof = profList.getFirst();
	if (prof != NULL)
	{
		do
		{
			if (prof->data.getPeoNo() == No)
			{
				prof->data.printInfo();
				count++;
			}
			prof = profList.getNext();
		} while (prof != NULL);
	}
	return count;
}

//按id查找人员
int database::search_id(const string& id)
{
	node<student>* stu;
	node<teacher>* tea;
	node<graduate>* grad;
	node<TA>* ta;
	node<Prof>* prof;
	int count = 0;

	stu = stuList.getFirst();
	if (stu != NULL)
	{
		do
		{
			if (stu->data.getId() == id)
			{
				stu->data.printInfo();
				count++;
			}
			stu = stuList.getNext();
		} while (stu != NULL);
	}

	tea = teaList.getFirst();
	if (tea != NULL)
	{
		do
		{
			if (tea->data.getId() == id)
			{
				tea->data.printInfo();
				count++;
			}
			tea = teaList.getNext();
		} while (tea != NULL);
	}

	grad = gradList.getFirst();
	if (grad != NULL)
	{
		do
		{
			if (grad->data.getId() == id)
			{
				grad->data.printInfo();
				count++;
			}
			grad = gradList.getNext();
		} while (grad != NULL);
	}

	ta = TAList.getFirst();
	if (ta != NULL)
	{
		do
		{
			if (ta->data.getId() == id)
			{
				ta->data.printInfo();
				count++;
			}
			ta = TAList.getNext();
		} while (ta != NULL);
	}

	prof = profList.getFirst();
	if (prof != NULL)
	{
		do
		{
			if (prof->data.getId() == id)
			{
				prof->data.printInfo();
				count++;
			}
			prof = profList.getNext();
		} while (prof != NULL);
	}
	return count;
}

//按姓名查找雇员
int database::search_name(const string& name)
{
	node<student>* stu;
	node<teacher>* tea;
	node<graduate>* grad;
	node<TA>* ta;
	node<Prof>* prof;
	int count = 0;

	stu = stuList.getFirst();
	if (stu != NULL)
	{
		do
		{
			if (stu->data.getName() == name)
			{
				stu->data.printInfo();
				count++;
			}
			stu = stuList.getNext();
		} while (stu != NULL);
	}

	tea = teaList.getFirst();
	if (tea != NULL)
	{
		do
		{
			if (tea->data.getName() == name)
			{
				tea->data.printInfo();
				count++;
			}
			tea = teaList.getNext();
		} while (tea != NULL);
	}

	grad = gradList.getFirst();
	if (grad != NULL)
	{
		do
		{
			if (grad->data.getName() == name)
			{
				grad->data.printInfo();
				count++;
			}
			grad = gradList.getNext();
		} while (grad != NULL);
	}

	ta = TAList.getFirst();
	if (ta != NULL)
	{
		do
		{
			if (ta->data.getName() == name)
			{
				ta->data.printInfo();
				count++;
			}
			ta = TAList.getNext();
		} while (ta != NULL);
	}

	prof = profList.getFirst();
	if (prof != NULL)
	{
		do
		{
			if (prof->data.getName() == name)
			{
				prof->data.printInfo();
				count++;
			}
			prof = profList.getNext();
		} while (prof != NULL);
	}
	return count;
}

//按id更新雇员信息
bool database::updatePeople(const string& id)
{
	node<student>* stu;
	node<teacher>* tea;
	node<graduate>* grad;
	node<TA>* ta;
	node<Prof>* prof;
	bool flag = false;

	stu = stuList.getFirst();
	if (stu != NULL)
	{
		do
		{
			if (stu->data.getId() == id)
			{
				stu->data.printInfo();
				cout << "按Y/y确认更新：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					stu->data.updateInfo();
					flag = true;
					cout << "更新成功。" << endl;
				}
				else
				{
					cout << "放弃更新。" << endl;
				}
			}
			stu = stuList.getNext();
		} while (stu != NULL);
	}

	tea = teaList.getFirst();
	if (tea != NULL)
	{
		do
		{
			if (tea->data.getId() == id)
			{
				tea->data.printInfo();
				cout << "按Y/y确认更新：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					tea->data.updateInfo();
					flag = true;
					cout << "更新成功。" << endl;
				}
				else
				{
					cout << "放弃更新。" << endl;
				}
			}
			tea = teaList.getNext();
		} while (tea != NULL);
	}

	grad = gradList.getFirst();
	if (grad != NULL)
	{
		do
		{
			if (grad->data.getId() == id)
			{
				grad->data.printInfo();
				cout << "按Y/y确认更新：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					grad->data.updateInfo();
					flag = true;
					cout << "更新成功。" << endl;
				}
				else
				{
					cout << "放弃更新。" << endl;
				}
			}
			grad = gradList.getNext();
		} while (grad != NULL);
	}

	ta = TAList.getFirst();
	if (ta != NULL)
	{
		do
		{
			if (ta->data.getId() == id)
			{
				ta->data.printInfo();
				cout << "按Y/y确认更新：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					ta->data.updateInfo();
					flag = true;
					cout << "更新成功。" << endl;
				}
				else
				{
					cout << "放弃更新。" << endl;
				}
			}
			ta = TAList.getNext();
		} while (ta != NULL);
	}

	prof = profList.getFirst();
	if (prof != NULL)
	{
		do
		{
			if (prof->data.getId() == id)
			{
				prof->data.printInfo();
				cout << "按Y/y确认更新：";
				char input;
				cin >> input;
				if ((input == 'y') || (input == 'Y'))
				{
					prof->data.updateInfo();
					flag = true;
					cout << "更新成功。" << endl;
				}
				else
				{
					cout << "放弃更新。" << endl;
				}
			}
			prof = profList.getNext();
		} while (prof != NULL);
	}

	return flag;
}

//显示某一类的所有雇员
int database::showAll(PeopleType p)
{
	node<student>* stu;
	node<teacher>* tea;
	node<graduate>* grad;
	node<TA>* ta;
	node<Prof>* prof;
	int count = 0;

	switch (p)
	{
	case PEOPLE_TYPE:
		stu = stuList.getFirst();
		if (stu != NULL)
		{
			do
			{
				stu->data.printInfo();
				count++;
				stu = stuList.getNext();
			} while (stu != NULL);
		}
		tea = teaList.getFirst();
		if (tea != NULL)
		{
			do
			{
				tea->data.printInfo();
				count++;
				tea = teaList.getNext();
			} while (tea != NULL);
		}
		grad = gradList.getFirst();
		if (grad != NULL)
		{
			do
			{
				grad->data.printInfo();
				count++;
				grad = gradList.getNext();
			} while (grad != NULL);
		}
		ta = TAList.getFirst();
		if (ta != NULL)
		{
			do
			{
				ta->data.printInfo();
				count++;
				ta = TAList.getNext();
			} while (ta != NULL);
		}
		prof = profList.getFirst();
		if (prof != NULL)
		{
			do
			{
				prof->data.printInfo();
				count++;
				prof = profList.getNext();
			} while (prof != NULL);
		}
		break;
	case STUDENT_TYPE:
		stu = stuList.getFirst();
		if (stu != NULL)
		{
			do
			{
				stu->data.printInfo();
				count++;
				stu = stuList.getNext();
			} while (stu != NULL);
		}
		break;
	case TEACHER_TYPE:
		tea = teaList.getFirst();
		if (tea != NULL)
		{
			do
			{
				tea->data.printInfo();
				count++;
				tea = teaList.getNext();
			} while (tea != NULL);
		}
		break;
	case GRADUATE_TYPE:
		grad = gradList.getFirst();
		if (grad != NULL)
		{
			do
			{
				grad->data.printInfo();
				count++;
				grad = gradList.getNext();
			} while (grad != NULL);
		}
		break;
	case TA_TYPE:
		ta = TAList.getFirst();
		if (ta != NULL)
		{
			do
			{
				ta->data.printInfo();
				count++;
				ta = TAList.getNext();
			} while (ta != NULL);
		}
		break;
	case PROF_TYPE:
		prof = profList.getFirst();
		if (prof != NULL)
		{
			do
			{
				prof->data.printInfo();
				count++;
				prof = profList.getNext();
			} while (prof != NULL);
		}
		break;
	default:
		break;
	}
	return count;
}

//清空当前数据库
bool database::deleteAll()
{
	stuList.makeEmpty();
	teaList.makeEmpty();
	gradList.makeEmpty();
	TAList.makeEmpty();
	profList.makeEmpty();
	return true;
}

//设置数据库密码
bool database::setPassword(const string& inputPassword)
{
	password = inputPassword;
	try
	{
		savePassWord("password.txt");
	}
	catch (FileException e)
	{
		throw e;
	}
	return true;
}

//设置销售经理与销售员的关系
bool database::setRelationship(int gradNo, int profNo)
{
	graduate* g = NULL;
	TA* t = NULL;
	Prof* p = NULL;

	node<graduate>* tmpG = gradList.getFirst();
	if (tmpG != NULL)
	{
		do
		{
			if (tmpG->data.getPeoNo() == gradNo)
			{
				g = &tmpG->data;
				break;
			}
			tmpG = gradList.getNext();
		} while (tmpG != NULL);
	}

	node<TA>* tmpT = TAList.getFirst();
	if (tmpT != NULL)
	{
		do
		{
			if (tmpT->data.getPeoNo() == gradNo)
			{
				t = &tmpT->data;
				break;
			}
			tmpT = TAList.getNext();
		} while (tmpT != NULL);
	}

	node<Prof>* tmpP = profList.getFirst();
	if (tmpP != NULL)
	{
		do
		{
			if (tmpP->data.getPeoNo() == profNo)
			{
				p = &tmpP->data;
				break;
			}
			tmpP = profList.getNext();
		} while (tmpP != NULL);
	}

	if (g != NULL && p != NULL)
	{
		g->setAdvisor(p);
		return true;
	}

	if (t != NULL && p != NULL)
	{
		t->setAdvisor(p);
		return true;
	}

	return false;
}