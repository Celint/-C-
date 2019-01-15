#include<string>
#include<iostream>
using namespace std;

//类的前向声明
class graduate;
class SMaster;
class EMaster;

typedef struct SList {//学术硕士信息链表
	SMaster* AcademicMaster;
	struct SList *next;
}SList, *S;
typedef struct EList {//工程硕士信息链表
	EMaster* EngineeringMaster;
	struct EList *next;
}Elist, *E;

SList* shead;        //定义学术硕士头结点
EList* ehead;        //定义工程硕士头结点


struct Paper { //论文6
	string name;
	int level;
};
struct Project {//项目
	string name;
	char level;
};



//***************************************类的定义********************************************************//
//研究生类的定义
class graduate {    
protected:
	int stuNum;    //学号
	string name;   //姓名
	string sex;    //性别
	int age;       //年龄
	double kgrade; //课程成绩
};

//------------------------------------学术硕士的定义------------------------------------------------------------//
class SMaster : public graduate { 
public:
	SMaster*pSMaster;            //确定此对象的地址
	SMaster();                  //构造函数
    void input();               //录入数据
	int getNum()const;          //返回学号
	string getName()const;      //返回姓名
	double getgrade();          //计算论文成绩算法
	double getsum();            //计算总成绩算法（每次论文修改后需重新调用）
	friend ostream& operator<<(ostream&, SMaster&);	//重载cin<<函数
	friend istream& operator>>(istream&, SMaster&); //重载cou>>函数
	static void statisticalData(SMaster*);	        //统计函数
protected:
	static double sumSMasterScore;          //全体学术硕士总成绩
	static int countSMasterNumber;          //全体学术硕士总人数
	static double averageSMasterScore;      //全体学术硕士平均分
	static int a[6];                        //全体学术硕士总分分段人数
	string major;               //主修
	struct Paper paper[3];      //发表论文(判断是否多于三个)
	double grade1;              //论文成绩
	double Sgrade;              //总成绩
};

//---------------------------------工程硕士的定义------------------------------------------------------------//
class EMaster : public graduate {
public:
	EMaster*pEMaster;           //确定此对象的地址
	EMaster();                  //构造函数
	void input();               //录入数据
	int getNum()const;          //返回学号
	string getName()const;      //返回姓名
	double getgrade();        //计算项目成绩
	double getsum();          //计算总成绩算法(把项目级别ABC转化为分数)
	friend ostream& operator<<(ostream&, EMaster&);	  //重载cin<<函数
	friend istream& operator>>(istream&, EMaster&);   //重载cout>>函数
	static void statisticalData(EMaster*);	          //统计函数
protected:
	static double sumEMasterScore;          //全体工程硕士总成绩
	static int countEMasterNumber;          //全体工程硕士总人数
	static double averageEMasterScore;      //全体工程硕士平均分
	static int a[6];                        //全体工程硕士总分分段人数
	string area;              //领域
	struct Project project;   //参与项目
	double grade1;            //项目成绩
	double Sgrade;            //总成绩
};
//**********************************************************************************************************//

//****************************************成员函数的定义*****************************************************//
int SMaster::getNum()const { return stuNum; }
string SMaster::getName()const {return name;}
int EMaster::getNum()const { return stuNum; }
string EMaster::getName()const { return name; }
EMaster::EMaster() {
	stuNum = 0;
	name = "";
	sex = "";
	age = 0;
	kgrade = 0;
	area = "";
	project.name = "";
	project.level = ' ';
	pEMaster = this;
}
SMaster::SMaster() {
	stuNum = 0;
	name = "无";
	sex = "未知";
	age = 0;
	kgrade = 0;
	major = "";
	Sgrade = 0;
	for (int i = 0; i < 3; i++) {
		paper[i].name = "";
		paper[i].level = 0;
	}
	pSMaster = this;
}
void SMaster::input() {
	cout << "输入姓名" << endl;
	cin >> name;
	cout << "输入学号" << endl;
	cin >> stuNum;
	cout << "输入性别" << endl;
	cin >> sex;
	cout << "输入课程成绩" << endl;
	cin >> kgrade;
	cout << "输入专业" << endl;
	cin >> major;
	cout << "输入年龄" << endl;
	cin >> age;
	cout << "输入论文的个数" << endl;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "输入名称与等级" << endl;
		cin >> paper[i].name >> paper[i].level;
	}
}
void EMaster::input() {
	cout << "输入姓名" << endl;
	cin >> name;
	cout << "输入学号" << endl;
	cin >> stuNum;
	cout << "输入性别" << endl;
	cin >> sex;
	cout << "输入年龄" << endl;
	cin >> age;
	cout << "输入领域" << endl;
	cin >> area;
	cout << "输入课程成绩" << endl;
	cin >> kgrade;
	cout << "输入项目名称" << endl;
	cin >> project.name;
	cout << "输入项目级别" << endl;
	cin >> project.level;
}
double SMaster::getgrade()
{
	int i;
	for (i = 0; i < 3; i++)
		grade1 += paper[i].level / 90 * 100;
	return grade1;
}
double SMaster::getsum()
{
	getgrade();
	Sgrade = grade1 * 0.3 + kgrade * 0.7;
	return Sgrade;
}
double  EMaster::getgrade()
{
	float grade1 = 0;

	if (project.level == 'A')
		grade1 = 90.0;
	else if (project.level == 'B')
		grade1 = 75.0;
	else if (project.level == 'C')
		grade1 = 60.0;
	else
		grade1 = 0.0;
	return grade1;
}
double EMaster::getsum()
{
	getgrade();
	Sgrade = grade1 * 0.5 + kgrade * 0.5;
	return Sgrade;
}
//************************************************************************************************************//





//*************************************链表操作**************************************//

void input();           //录入
void insert();          //插入
void seek();            //查询
void del();             //删除
void print();           //输出
void modif();           //修改
void input() {

	cout << "\n*********开始录入学术硕士信息*********\n" << endl;
	for (;;)
	{
		char ch;
		SList* p = shead;
		SList* newslist = new SList;
		SMaster newsmaster;
		newsmaster.input();
		newslist->AcademicMaster = newsmaster.pSMaster;
		newslist->next = p->next;
		p->next = newslist;
		p = newslist;

		cout << "输入y继续录入，输入其他结束录入: ";
		cin >> ch;
		if (ch != 'y')
			break;
	}
	cout << "\n*********开始录入工程硕士信息*********\n" << endl;
	for (;;)
	{
		char ch;
		EList* p = ehead;
		EList* newelist = new EList;
		EMaster newemaster;
		newemaster.input();
		newelist->EngineeringMaster = newemaster.pEMaster;
		newelist->next = p->next;
		p->next = newelist;
		p = newelist;

		cout << "输入y继续录入，输入其他结束录入: ";
		cin >> ch;
		if (ch != 'y')
			break;
	}
}

void insert() {
	int n;
	cout << "在指定研究生后插入" << endl;
	for (;;)
	{
		cout << "输入1查入学术硕士，输入2查入工程硕士，输入其他数字退出插入:";
		cin >> n;
		if (n == 1)
		{
			int t;
			SList* p = shead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				int stunum;
				cout << "输入学号:";
				cin >> stunum;
				while (p != NULL && p->AcademicMaster->getNum() != stunum)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					SList* newslist = new SList;
					SMaster newsmaster;
					newsmaster.input();
					newslist->AcademicMaster = newsmaster.pSMaster;
					newslist->next = p->next;
					p->next = newslist;
				}
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入学号:";
				cin >> stuname;
				while (p != NULL && p->AcademicMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					SList* newslist = new SList;
					SMaster newsmaster;
					newsmaster.input();
					newslist->AcademicMaster = newsmaster.pSMaster;
					newslist->next = p->next;
					p->next = newslist;
				}
			}
		}
		else if (n == 2)
		{
			int t;
			EList* p = ehead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				int stunum;
				cout << "输入学号:";
				cin >> stunum;
				while (p != NULL && p->EngineeringMaster->getNum() != stunum)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					EList* newelist = new EList;
					EMaster newemaster;
					newemaster.input();
					newelist->EngineeringMaster = newemaster.pEMaster;
					newelist->next = p->next;
					p->next = newelist;
				}
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入学号:";
				cin >> stuname;
				while (p != NULL && p->EngineeringMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					EList* newelist = new EList;
					EMaster newemaster;
					newemaster.input();
					newelist->EngineeringMaster = newemaster.pEMaster;
					newelist->next = p->next;
					p->next = newelist;
				}
			}
		}
	}
}


void seek() {
	int n;
	for (;;)
	{
		cout << "输入1查找学术硕士，输入2查找工程硕士，输入其他数字退出查找:";
		cin >> n;
		if(n==1)
		{
			int t;
			SList* p = shead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				int stunum;
				cout << "输入学号:";
				cin >> stunum;
				while (p != NULL && p->AcademicMaster->getNum() != stunum)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					cout << *(p->AcademicMaster);
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入学号:";
				cin >> stuname;
				while (p != NULL && p->AcademicMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					cout << *(p->AcademicMaster);
			}
		}
		else if(n==2)
		{
			int t;
			EList* p = ehead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				int stunum;
				cout << "输入学号:";
				cin >> stunum;
				while (p != NULL && p->EngineeringMaster->getNum() != stunum)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					cout << *(p->EngineeringMaster);
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入学号:";
				cin >> stuname;
				while (p != NULL && p->EngineeringMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					cout << *(p->EngineeringMaster);
			}
		}
	}
}
void del() {
	int n;
	for (;;)
	{
		cout << "输入1删除学术硕士，输入2删除工程硕士，输入其他数字退出删除:";
		cin >> n;
		if (n == 1)
		{
			int t;
			SList* p = shead->next;
			SList* q = shead;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				int stunum;
				cout << "输入学号:";
				cin >> stunum;
				while (p != NULL && p->AcademicMaster->getNum() != stunum)
				{
					q = p;
					p = p->next;
				}
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					q->next = p->next;
					free(p);
					cout << "删除成功!";
				}
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入学号:";
				cin >> stuname;
				while (p != NULL && p->AcademicMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					q->next = p->next;
					free(p);
					cout << "删除成功!";
				}
			}
		}
		else if (n == 2)
		{
			int t;
			EList* p = ehead->next;
			EList* q = ehead;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				int stunum;
				cout << "输入学号:";
				cin >> stunum;
				while (p != NULL && p->EngineeringMaster->getNum() != stunum)
				{
					q = p;
					p = p->next;
				}
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					q->next = p->next;
					free(p);
					cout << "删除成功!";
				}
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入学号:";
				cin >> stuname;
				while (p != NULL && p->EngineeringMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					q->next = p->next;
					free(p);
					cout << "删除成功!";
				}
			}
		}
	}
}

void print() {
	int n;
	cout << "输入1输出学术硕士，输入2输出工程硕士:";
	cin >> n;
	if (n == 1)
	{
		SList*p = shead->next;
		for (; p != NULL; p = p->next)
			cout << *(p->AcademicMaster) << endl;
	}
	else if (n == 2)
	{
		EList*p = ehead->next;
		for (; p != NULL; p = p->next)
			cout << *(p->EngineeringMaster) << endl;
	}
}
void modif() {
	int n;
	for (;;)
	{
		cout << "输入1修改学术硕士，输入2修改工程硕士，输入其他数字退出删除:";
		cin >> n;
		if (n == 1)
		{
			int t;
			SList* p = shead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				int stunum;
				cout << "输入学号:";
				cin >> stunum;
				while (p != NULL && p->AcademicMaster->getNum() != stunum)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					p->AcademicMaster->input();
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入学号:";
				cin >> stuname;
				while (p != NULL && p->AcademicMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					p->AcademicMaster->input();
			}
		}
		else if (n == 2)
		{
			int t;
			EList* p = ehead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				int stunum;
				cout << "输入学号:";
				cin >> stunum;
				while (p != NULL && p->EngineeringMaster->getNum() != stunum)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					p->EngineeringMaster->input();
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入学号:";
				cin >> stuname;
				while (p != NULL && p->EngineeringMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					p->EngineeringMaster->input();
			}
		}
	}
}
//****************************************测试******************************************************//

void init() {
	shead = new SList;
	ehead = new EList;
	shead->next = NULL;
	ehead->next = NULL;
}
int main() {
	init();
	input();
	
}