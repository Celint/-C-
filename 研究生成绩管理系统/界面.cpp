#include<iostream>
#include<string>
using namespace std;

void welcome() {
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout << "**       欢迎使用研究生信息管理系统       **" << endl;
	cout << "**         作者：计科1704第一小组         **" << endl;
	cout << "**          时间：2019年1月14日           **" << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	int i = 0;
	string user;
	string password;
part:
	cout << "请输入账号" << endl;
	cin >> user;
	cout << "请输入密码" << endl;
	cin >> password;
	if (user == "0902170401"&&password == "123456")
	{
		cout << "登录成功！" << endl;
		system("pause");
		system("cls");
	}//清屏
	else
	{
		cout << "登录失败，请重新输入账号密码" << endl;
		i++;
		if (i == 5) //失败五次自动退出
		{
			cout << "超过输入次数，系统自动退出" << endl;
			system("pause");
			exit(0);
		}//非正常退出
		goto part;
	}
	

}
void menu()        //菜单页面
{
	int i = 0;
	cout << "********************************************" << endl;
	cout << "**          研究生信息管理系统            **" << endl;
	cout << "**          1.研究生信息录入              **" << endl;
	cout << "**          2.研究生信息插入              **" << endl;
	cout << "**          3.研究生信息删除              **" << endl;
	cout << "**          4.研究生信息输出              **" << endl;
	cout << "**          5.研究生信息修改              **" << endl;
	cout << "**          6.研究生信息查找              **" << endl;
	cout << "**          7.研究生信息**                **" << endl;//有需要可以再增加
	cout << "**          8.信息清除                    **" << endl;//删库跑路
	cout << "**          9.退出系统                    **" << endl;
	cout << "********************************************" << endl;
	cout << "请选择功能" << endl;
part:	cin >> i;
	switch (i)
	{

	case 1:

		//信息录入函数
		system("pause");
		system("cls");
		break;
		;
	case 2:

		//信息插入函数
		system("pause");
		system("cls");
		break;
	case 3:

		//信息删除函数
		system("pause");
		system("cls");
		break;
	case 4:
		//信息输出函数
		system("pause");
		system("cls");
		break;
	case 5:
		//信息修改函数
		system("pause");
		system("cls");
		break;
	case 6:
		//信息查找函数
		system("pause");
		system("cls");
	case 8:
		//信息清除函数
		break;
	case 9:
		//退出系统函数
		break;
	default:
		cout << "您输入的数据有误，请重新输入" << endl;
		goto part;


	}
}
int main()
{
    welcome();
    menu();
}