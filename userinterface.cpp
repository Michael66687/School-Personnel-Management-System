/*用户界面类的定义*/
#pragma warning(disable:4996 6031)
#include<iostream>
#include<string.h>
#include<windows.h>
#include<fstream>
#include<conio.h>
#include"userinterface.h"
using namespace std;

//构造函数
userinterface::userinterface()
{
	people_database = NULL;
}

//析构函数
userinterface::~userinterface()
{
	delete people_database;
}

//欢迎界面
void userinterface::welcome()
{
	system("cls");
	cin.clear();
	cin.sync();

	cout << " ++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
		<< "                 学校人事管理系统" << endl
		<< " ++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl
		<< "######################################################" << endl
		<< "                      主菜单" << endl
		<< "\t\t1.录入人员信息" << endl
		<< "\t\t2.删除人员信息" << endl
		<< "\t\t3.查找人员信息" << endl
		<< "\t\t4.更新人员信息" << endl
		<< "\t\t5.保存信息到默认文件" << endl
		<< "\t\t6.新建文件保存信息" << endl
		<< "\t\t7.从指定文件中读取信息" << endl
		<< "\t\t8.清空当前数据库" << endl
		<< "\t\t9.显示某一类全部人员" << endl
		<< "\t\t10.排序人员信息" << endl
		<< "\t\t11.设置导师与研究生(助教)关系" << endl
		<< "\t\t12.修改密码" << endl
		<< "\t\t13.退出" << endl
		<< "                请选择序号（1-13）" << endl
		<< "######################################################" << endl;

	cout << "输入编号进行操作：";
}

//从指定文件中读取数据
bool userinterface::loadnew()
{
	system("cls");
	cin.clear();
	cin.sync();

	cout << "是否要从指定文件中读取数据？(y/n)" << endl;
	char input;
	cin>>input;
	if (input == 'Y' || input == 'y')
	{
		delete people_database;
		people_database = NULL;
		if (people_database == NULL)
		{
			people_database = new database();
			try
			{
				people_database->load_new();
			}
			catch (FileException e)
			{
				if (e.mode == "open")
				{
					cout << "以" << e.type << "方式打开文件" << e.filename << "时出错。" << endl;
				}
				else //if (e.mode == "operator")
				{
					if (e.type == "read")
					{
						cout << "从文件" << e.filename << "读取时出错。" << endl;
					}
					else //if (e.type == "write")
					{
						cout << "向文件" << e.filename << "写入时出错。" << endl;
					}
				}
				return false;
			}
			cout << "读取数据成功！" << endl;
			return false;
	}
		else
		{
			cout << "返回上级菜单" << endl;
			pause();
			return false;
		}
	}
}

//输入密码界面
bool userinterface::start()
{
	system("cls");
	cin.clear();
	cin.sync();

	if (people_database == NULL)
	{
		people_database = new database();
		try
		{
			people_database->load();
		}
		catch (FileException e)
		{
			if (e.mode == "open")
			{
				cout << "以" << e.type << "方式打开文件" << e.filename << "时出错。" << endl;
				pause();
			}
			else //if (e.mode == "operator")
			{
				if (e.type == "read")
				{
					cout << "从文件" << e.filename << "读取时出错。" << endl;
					pause();
				}
				else //if (e.type == "write")
				{
					cout << "向文件" << e.filename << "写入时出错。" << endl;
					pause();
				}
			}
			return false;
		}
	}

	cout << " ++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
		<< "                 学校人事管理系统" << endl
		<< " ++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl
		<< "######################################################" << endl;

	string inputPassword, password;
	char inputPassWords[20];
	char input;
	password = people_database->getPassword();
	cout << "请输入密码：" << endl;
	int i = 0;
	// 对密码进行*保护
	while ((input = _getch()) != '\r' && i < 20)
	{
		if (input == '\b')
		{
			if (i > 0)
			{
				i--;
				cout << "\b \b"; //密码支持退格的实现
			}
			else
			{
				putchar(7);
			}
		}
		else
		{
			inputPassWords[i] = input;
			i++;
			cout << "*";
		}
	}
	inputPassWords[i] = '\0';
	inputPassword = inputPassWords;
	cout << endl;
	if (inputPassword != password)
	{
		cout << "密码错误！请重试。" << endl;
		pause();
		return true;
	}
	cout << "密码正确！欢迎您使用本学校人事管理系统！" << endl;
	pause();
	return false;
}


//主要的交互界面
bool userinterface::running()
{
	welcome();

	int input;
	cin >> input;

	if (!cin)
	{
		cout << "输入错误，请重新输入。" << endl;
		pause();
		return true;
	}

	switch (input)
	{
	case 1:
		while (insertPeople());
		break;
	case 2:
		while (deletePeople());
		break;
	case 3:
		while (searchPeople());
		break;
	case 4:
		while (updatePeople());
		break;
	case 5:
		while (saveInfo());
		break;
	case 6:
		while (saveInfo_new());
		break;
	case 7:
		while (loadnew());
		break;
	case 8:
		while (deleteDatabase());
		break;
	case 9:
		while (showAll());
		break;
	case 10:
		while (sortPeople());
		break;
	case 11:
		while (setRelationship());
		break;
	case 12:
		while (setPassword());
		break;
	case 13:
		quit();
		return false;
	default:
		cout << "输入错误，请重新输入。" << endl;
	}
	pause();
	return true;
}

//暂停函数
void userinterface::pause()
{
	cin.clear();
	cin.sync();
	cout << "按任意键继续：";
	getch();
}

//查询界面
bool userinterface::searchPeople()
{
	system("cls");

	cout << "      查找人员信息" << endl
		<< "\t1.按编号查找" << endl
		<< "\t2.按id查找" << endl
		<< "\t3.按姓名查找" << endl
		<< "\t4.返回上级" << endl;

	cout << "输入编号进行操作：";

	int input;
	int num;
	int peopleNo;
	string peopleId;
	string peopleName;
	cin >> input;

	if (!cin)
	{
		cout << "输入错误，请重新输入。" << endl;
		pause();
		return true;
	}

	switch (input)
	{
	case 1:
		cout << "     按编号查找雇员" << endl;
		cout << "输入待查雇员编号：";
		cin >> peopleNo;
		if (!cin)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}
		num = people_database->search_No(peopleNo);
		if (num == 0)
		{
			cout << "没有找到结果。" << endl;
		}
		else
		{
			cout << "找到" << num << "个结果。" << endl;
		}
		break;
	case 2:

		cout << "     按id查找雇员" << endl;
		cout << "输入待查雇员id：";
		cin >> peopleId;
		if (!cin)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}
		num = people_database->search_id(peopleId);
		if (num == 0)
		{
			cout << "没有找到结果。" << endl;
		}
		else
		{
			cout << "找到" << num << "个结果。" << endl;
		}
		break;
	case 3:

		cout << "     按姓名查找雇员" << endl;
		cout << "输入待查雇员姓名：";
		cin >> peopleName;
		if (!cin)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}
		num = people_database->search_name(peopleName);
		if (num == 0)
		{
			cout << "没有找到结果。" << endl;
		}
		else
		{
			cout << "找到" << num << "个结果。" << endl;
		}
		break;
	case 4:
		cout << "返回上级菜单。" << endl;
		return false;
	default:
		cout << "输入错误，请重新输入。" << endl;
		pause();
		return true;
	}

	pause();
	return true;
}

//插入界面
bool userinterface::insertPeople()
{
	system("cls");

	cout << "      录入人员信息" << endl;
	int input;
	cout << "1.录入人员信息" << endl
		<< "2.返回上级" << endl;
	cin >> input;
	switch (input)
	{
	case 1:
		system("cls");
		cout << "输入人员类别：" << endl;
		cout << "1.学生" << endl
			<< "2.教师" << endl
			<< "3.研究生" << endl
			<< "4.助教" << endl
			<< "5.教授" << endl;

		int peopleType;
		cin >> peopleType;
		if (!cin)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		if (peopleType < 1 || peopleType>5)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		people_database->addPeople((PeopleType)peopleType);

		cout << "是否继续？（y/n）";
		char input;
		cin >> input;
		if (input == 'y' || input == 'Y')
			return true;
		else
			return false;
	case 2:
		cout << "返回上级菜单" << endl;
		return false;
	default:
		cout << "输入错误，请重试！" << endl;
		pause();
		return true;
	}
	
}

//删除界面
bool userinterface::deletePeople()
{
	system("cls");
	string peopleId;
	int input;
	cout << "        删除人员信息" << endl;
	cout << "1.删除人员信息" << endl
		<< "2.返回上级" << endl;
	cin >> input;
	switch (input)
	{
	case 1:
		cout << "输入人员id：" << endl;


		cin >> peopleId;
		if (!cin)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		if (people_database->deletePeople(peopleId))
		{
			cout << "删除结束。" << endl;
		}
		else
		{
			cout << "未找到目标雇员。" << endl;
		}

		cout << "是否继续？（y/n）";
		char input;
		cin >> input;
		if (input == 'y' || input == 'Y')
		{
			return true;
		}
		else
			return false;
	case 2:
		cout << "返回上级菜单" << endl;
		return false;
	default:
		cout << "输入错误，请重试！" << endl;
		pause();
		return true;
	}
}

//更新界面
bool userinterface::updatePeople()
{
	system("cls");
	string peopleId;
	int input;
	cout << "       更新人员信息" << endl
		<< "1.更新人员信息" << endl
		<< "2.返回上级" << endl;
	cin >> input;
	switch (input)
	{
	case 1:
		cout << "输入人员id：" << endl;


		cin >> peopleId;
		if (!cin)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		if (people_database->updatePeople(peopleId))
		{
			cout << "更新结束。" << endl;
		}
		else
		{
			cout << "查无此人！" << endl;
		}

		cout << "是否继续？（y/n）";
		char input;
		cin >> input;
		if (input == 'y' || input == 'Y')
			return true;
		else
			return false;
	case 2:
		cout << "返回上级菜单" << endl;
		return false;
	default:
		cout << "输入错误，请重试！" << endl;
		pause();
		return true;
	}
}

//保存人员信息
bool userinterface::saveInfo()
{
	system("cls");

	cout << "是否保存数据？（y/n）:";
	char input;
	cin >> input;
	if (input == 'y' || input == 'Y')
	{
		try
		{
			people_database->save();
		}
		catch (FileException e)
		{
			cout << "保存失败！" << endl;
			if (e.mode == "open")
			{
				cout << "以" << e.type << "方式打开文件夹" << e.filename << "时出错。" << endl;
			}
			else
			{
				if (e.type == "read")
				{
					cout << "从文件" << e.filename << "读取时出错。" << endl;
				}
				else
				{
					cout << "向文件" << e.filename << "写入时出错。" << endl;
				}
			}
			return false;
		}
	}
	else
	{
		cout << "取消保存，返回上级菜单" << endl;
		return false;
	}
	cout << "保存成功！" << endl;
	return false;
}

//新建文件保存数据
bool userinterface::saveInfo_new()
{
	system("cls");

	cout << "是否新建文件保存数据？（y/n）:";
	char input;
	cin >> input;
	if (input == 'y' || input == 'Y')
	{
		try
		{
			people_database->save_new();
		}
		catch (FileException e)
		{
			cout << "保存失败！" << endl;
			if (e.mode == "open")
			{
				cout << "以" << e.type << "方式打开文件夹" << e.filename << "时出错。" << endl;
			}
			else
			{
				if (e.type == "read")
				{
					cout << "从文件" << e.filename << "读取时出错。" << endl;
				}
				else
				{
					cout << "向文件" << e.filename << "写入时出错。" << endl;
				}
			}
			return false;
		}
	}
	else
	{
		cout << "返回上级菜单" << endl;
		return false;
	}
	cout << "保存成功！" << endl;
	return false;
}

//退出界面
void userinterface::quit()
{
	cout << "是否保存数据（保存至现有文件中）？（y/n）:";
	char input;
	cin >> input;
	if (input == 'y' || input == 'Y')
	{
		try
		{
			people_database->save();
		}
		catch (FileException e)
		{
			if (e.mode == "open")
			{
				cout << "以" << e.type << "方式打开文件夹" << e.filename << "时出错。" << endl;
			}
			else
			{
				if (e.type == "read")
				{
					cout << "从文件" << e.filename << "读取时出错。" << endl;
				}
				else
				{
					cout << "向文件" << e.filename << "写入时出错。" << endl;
				}
			}
		}
	}

	cout << "谢谢使用，再见！" << endl;
}

//显示某一类人员
bool userinterface::showAll()
{
	system("cls");

	int peopleType, num, input;
	cout << "       按类别显示全部人员" << endl
		<< "1.按类别显示全部人员" << endl
		<< "2.返回上级" << endl;
	cin >> input;
	switch (input)
	{
	case 1:
		cout << "输入人员类别：" << endl;
		cout << "1.学生" << endl
			<< "2.教师" << endl
			<< "3.研究生" << endl
			<< "4.助教" << endl
			<< "5.男教授" << endl
			<< "0.全部" << endl;
		cin >> peopleType;
		if (!cin || peopleType < 0 || peopleType>6)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}
		num = people_database->showAll((PeopleType)peopleType);
		if (num == 0)
			cout << "没有找到结果。" << endl;
		else
			cout << "找到" << num << "个结果。" << endl;

		cout << "是否继续？（y/n）";
		char input;
		cin >> input;
		if (input == 'y' || input == 'Y')
			return true;
		else
			return false;
	case 2:
		cout << "返回上级菜单" << endl;
		return false;
	default:
		cout << "输入错误，请重试！" << endl;
		pause();
		return true;
	}
	
}

//清空当前数据库
bool userinterface::deleteDatabase()
{
	system("cls");

	string inputPassword, password;
	password = people_database->getPassword();
	cout << "        清空当前数据库" << endl;
	cout << "请输入密码：" << endl;
	cin >> inputPassword;
	if (inputPassword == password)
	{
		if (people_database->deleteAll())
		{
			cout << "当前数据库已清除。" << endl;
			return false;
		}
		cout << "清空数据库失败！" << endl;
		return false;
	}
	cout << "密码错误！操作未进行！" << endl;
	return false;
}

//设置密码
bool userinterface::setPassword()
{
	system("cls");
	int input;
	int i = 0;
	string inputPassword1, inputPassword2, password;
	char inputPassWords[20];
	char inputs;
	password = people_database->getPassword();
	cout << "\t设置数据库密码" << endl;
	cout << "1.设置密码" << endl
		<< "2.返回上级" << endl;
	cin >> input;
	switch (input)
	{
	case 1:
		i = 0;
		cout << "请输入当前密码：" << endl;
		// 对输入进行*保护
		while ((inputs = _getch()) != '\r' && i < 20)
		{
			if (inputs == '\b')
			{
				if (i > 0)
				{
					i--;
					cout << "\b \b";//密码支持退格的实现
				}
				else
				{
					putchar(7);
				}
			}
			else
			{
				inputPassWords[i] = inputs;
				i++;
				cout << "*";
			}
		}
		inputPassWords[i] = '\0';
		cout << endl;
		inputPassword1 = inputPassWords;
		if (inputPassword1 == password)
		{
			cout << "密码正确。请输入重新设置后的密码：" << endl;
			i = 0;
			while ((inputs = _getch()) != '\r' && i < 20)
			{
				if (inputs == '\b')
				{
					if (i > 0)
					{
						i--;
						cout << "\b \b";//密码支持退格的实现
					}
					else
					{
						putchar(7);
					}
				}
				else
				{
					inputPassWords[i] = inputs;
					i++;
					cout << "*";
				}
			}
			inputPassWords[i] = '\0';
			inputPassword1 = inputPassWords;
			cout << endl;
			cout << "请再次输入新密码：" << endl;
			i = 0;
			while ((inputs = _getch()) != '\r' && i < 20)
			{
				if (inputs == '\b')
				{
					if (i > 0)
					{
						i--;
						cout << "\b \b";//密码支持退格的实现
					}
					else
					{
						putchar(7);
					}
				}
				else
				{
					inputPassWords[i] = inputs;
					i++;
					cout << "*";
				}
			}
			inputPassWords[i] = '\0';
			cout << endl;
			inputPassword2 = inputPassWords;
			if (inputPassword1 == inputPassword2)
			{
				if (people_database->setPassword(inputPassword1))
				{
					cout << "密码设置成功！" << endl;
					return false;
				}
				cout << "密码设置失败！" << endl;
				return false;
			}
			else
			{
				cout << "两次输入密码不同，设置密码失败！" << endl;
				return false;
			}
		}
		else
		{
			cout << "密码错误，返回主菜单！" << endl;
			return false;
		}
	case 2:
		cout << "返回上级菜单" << endl;
		return false;
	default:
		cout << "输入错误，请重试！" << endl;
		return true;
	}
	
}

//设置关系界面
bool userinterface::setRelationship()
{
	system("cls");
	int gradNo;
	int profNo;
	int input;
	bool result;
	cout << "        设置导师与研究生(助教)关系" << endl
		<< "1.设置关系" << endl
		<< "2.返回上级" << endl;
	cin >> input;
	switch (input)
	{
	case 1:
		cout << "输入研究生编号：";
		cin >> gradNo;

		if (!cin)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		cout << "输入教授编号：";
		cin >> profNo;

		if (!cin)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		result = people_database->setRelationship(gradNo, profNo);

		if (result)
		{
			cout << "设置成功。" << endl;
		}
		else
		{
			cout << "设置失败，编号不存在。" << endl;
		}

		cout << "是否继续？（y/n）";
		cin >> input;
		if (input == 'y' || input == 'Y')
		{
			return true;
		}
		else
			return false;
	case 2:
		cout << "返回上级菜单" << endl;
		return false;
	default:
		cout << "输入错误，请重试！" << endl;
		pause();
		return true;
	}
	
}

//排序界面
bool userinterface::sortPeople()
{
	system("cls");

	cout << "        人员信息排序" << endl
		<< "\t1.按编号排序" << endl
		<< "\t2.按工资排序" << endl
		<< "\t3.按综合成绩对学生(包括研究生和助教)排序" << endl
		<< "\t4.返回上级" << endl;

	cout << "输入编号进行操作：";

	int key;
	int direction;
	int peoType;
	cin >> key;
	if (!cin)
	{
		cout << "输入错误，请重新输入。" << endl;
		pause();
		return true;
	}

	switch (key)
	{
	case 1:
		cout << "输入人员类型：" << endl;
		cout << "1.学生" << endl
			<< "2.教师" << endl
			<< "3.研究生" << endl
			<< "4.助教" << endl
			<< "5.教授" << endl
			<< "0.全部人员" << endl;

		cin >> peoType;
		if (!cin || peoType < 0 || peoType>5)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		cout << "请选择排序方向：" << endl;
		cout << "1.升序" << endl
			<< "2.降序" << endl;

		cin >> direction;
		if (!cin || direction < 1 || direction>2)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		people_database->sortByNo((PeopleType)peoType, (direction == 1) ? -1 : 1);

		break;
	case 2:
		cout << "输入人员类型：" << endl;
		cout << "1.教师" << endl
			<< "2.助教" << endl
			<< "3.教授" << endl;

		cin >> peoType;
		if (!cin || peoType < 1 || peoType>3)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		cout << "请选择排序方向：" << endl;
		cout << "1.升序" << endl
			<< "2.降序" << endl;

		cin >> direction;
		if (!cin || direction < 1 || direction>2)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		people_database->sortByPay((PeopleType)(peoType + 1), (direction == 1) ? -1 : 1);

		break;
	case 3:
		cout << "输入人员类型：" << endl;
		cout << "1.学生" << endl
			<< "2.研究生" << endl
			<< "3.助教" << endl;

		cin >> peoType;
		if (!cin || peoType < 1 || peoType>3)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		cout << "请选择排序方向：" << endl;
		cout << "1.升序" << endl
			<< "2.降序" << endl;

		cin >> direction;
		if (!cin || direction < 1 || direction>2)
		{
			cout << "输入错误，请重新输入。" << endl;
			pause();
			return true;
		}

		people_database->sortByScore((PeopleType)peoType, (direction == 1) ? -1 : 1);

		break;
	case 4:
		cout << "返回上级菜单。" << endl;
		return false;
	default:
		cout << "输入错误，请重新输入。" << endl;
		pause();
		return true;
	}
	
	pause();
	return true;
}