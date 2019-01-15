#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

//类的前向声明
class graduate;
class SMaster;
class EMaster;

typedef struct SList
{ //学术硕士信息链表
	SMaster *AcademicMaster;
	struct SList *next;
} SList, *S;
typedef struct EList
{ //工程硕士信息链表
	EMaster *EngineeringMaster;
	struct EList *next;
} Elist, *E;

SList *shead; //定义学术硕士头结点
EList *ehead; //定义工程硕士头结点

struct Paper
{ //论文
	string name;
	int level;
};
struct Project
{ //项目
	string name;
	char level;
};

//***************************************类的定义********************************************************//
//研究生类的定义
class graduate
{
  protected:
	string stuNum; //学号
	string name;   //姓名
	string sex;	//性别
	int age;	   //年龄
	double kgrade; //课程成绩
};

//------------------------------------学术硕士的定义------------------------------------------------------------//
class SMaster : public graduate
{
  public:
	SMaster *pSMaster;								  //确定此对象的地址
	SMaster();										  //构造函数
	void input();									  //录入数据
	string getNum() const;							  //返回学号
	string getName() const;							  //返回姓名
	double getgrade();								  //计算论文成绩算法
	double getsum();								  //计算总成绩算法（每次论文修改后需重新调用）
	friend void saveSMasterfile();					  //保存文件
	friend void getSMasterfile();					  //打开文件
	friend ostream &operator<<(ostream &, SMaster &); //重载cout<<函数
	static void statisticalData();					  //统计函数
  protected:
	static double sumSMasterScore;	 //全体学术硕士总成绩
	static int countSMasterNumber;	 //全体学术硕士总人数
	static double averageSMasterScore; //全体学术硕士平均分
	static int a[6];				   //全体学术硕士总分分段人数
	string major;					   //主修
	struct Paper paper[3];			   //发表论文(判断是否多于三个)
	double grade1;					   //论文成绩
	double Sgrade;					   //总成绩
};

//---------------------------------工程硕士的定义------------------------------------------------------------//
class EMaster : public graduate
{
  public:
	EMaster *pEMaster;								  //确定此对象的地址
	EMaster();										  //构造函数
	void input();									  //录入数据
	string getNum() const;							  //返回学号
	string getName() const;							  //返回姓名
	double getgrade();								  //计算项目成绩
	double getsum();								  //计算总成绩算法(把项目级别ABC转化为分数)
	friend void saveEMasterfile();					  //保存文件
	friend void getEMasterfile();					  //打开文件
	friend ostream &operator<<(ostream &, EMaster &); //重载cout<<函数
	static void statisticalData();					  //统计函数
  protected:
	static double sumEMasterScore;	 //全体工程硕士总成绩
	static int countEMasterNumber;	 //全体工程硕士总人数
	static double averageEMasterScore; //全体工程硕士平均分
	static int a[6];				   //全体工程硕士总分分段人数
	string area;					   //领域
	struct Project project;			   //参与项目
	double grade1;					   //项目成绩
	double Sgrade;					   //总成绩
};
//**********************************************************************************************************//

//****************************************成员函数的定义*****************************************************//
string SMaster::getNum() const { return stuNum; }
string SMaster::getName() const { return name; }
string EMaster::getNum() const { return stuNum; }
string EMaster::getName() const { return name; }
EMaster::EMaster()
{
	stuNum = "无";
	name = "无";
	sex = "无";
	age = 0;
	kgrade = 0;
	area = "无";
	project.name = "无";
	project.level = '无';
	pEMaster = this;
}
SMaster::SMaster()
{
	stuNum = "无";
	name = "无";
	sex = "无";
	age = 0;
	kgrade = 0;
	major = "无";
	Sgrade = 0;
	for (int i = 0; i < 3; i++)
	{
		paper[i].name = "无";
		paper[i].level = 0;
	}
	pSMaster = this;
}

void SMaster::input()
{
	string _name, _sex, _stuNum, _major, papername[3];
	int papernumber, _age, paperleve[3];
	double _kgrade;
	cout << "输入姓名:";
sjudge1:
	cin >> _name;
	if (_name[0] == ' ')
	{
		cout << "请输入正确的姓名：";
		goto sjudge1;
	}
	name = _name;
	cout << "输入学号:";
sjudge2:
	cin >> _stuNum;
	if (_stuNum[0] == ' ')
	{
		cout << "请输入正确的学号：";
		goto sjudge2;
	}
	stuNum = _stuNum;
	cout << "输入性别:";
sjudge3:
	cin >> _sex;
	if (_sex != "man" && _sex != "woman")
	{
		cout << "请输入正确的性别(man / woman)：";
		goto sjudge3;
	}
	sex = _sex;
	cout << "输入课程成绩:";
sjudge4:
	cin >> _kgrade;
	if (_kgrade < 0 || _kgrade > 100)
	{
		cout << "请输入正确的课程成绩(0~100)：";
		goto sjudge4;
	}
	kgrade = _kgrade;
	cout << "输入专业:";
sjudge5:
	cin >> _major;
	if (_major[0] == ' ')
	{
		cout << "请输入正确的专业：";
		goto sjudge5;
	}
	major = _major;
	cout << "输入年龄:";
sjudge6:
	cin >> _age;
	if (_age <= 0)
	{
		cout << "请输入正确的年龄：";
		goto sjudge6;
	}
	age = _age;
	cout << "输入论文的个数:";
sjudge7:
	cin >> papernumber;
	if (papernumber > 3 || papernumber < 0)
	{
		cout << "请输入正确的论文个数(0~3)：";
		goto sjudge7;
	}
	for (int i = 0; i < papernumber; i++)
	{
		cout << "第" << i + 1 << "篇论文" << endl;
		cout << "名称:";
	sjdge8:
		cin >> papername[i];
		if (papername[i][0] == ' ')
		{
			cout << "请输入正确的论文名：";
			goto sjdge8;
		}
		paper[i].name = papername[i];
		cout << "等级:";
	sjudge9:
		cin >> paperleve[i];
		if (paperleve[i] > 3 || paperleve < 0)
		{
			cout << "请输入正确的论文等级(1~3)：";
			goto sjudge9;
		}
		paper[i].level = paperleve[i];
	}
	getgrade();
	getsum();
}
void EMaster::input()
{
	string _name, _sex, _area, projectname, _stuNum;
	int _age;
	char projectlevel;
	double _kgrade;
	cout << "输入姓名" << endl;
ejudge1:
	cin >> _name;
	if (_name[0] == ' ')
	{
		cout << "请输入正确的姓名：";
		goto ejudge1;
	}
	name = _name;
	cout << "输入学号" << endl;
ejudge2:
	cin >> _stuNum;
	if (_stuNum[0] == ' ')
	{
		cout << "请输入正确的学号：";
		goto ejudge2;
	}
	stuNum = _stuNum;
	cout << "输入性别" << endl;
ejudge3:
	cin >> _sex;
	if (_sex != "man" && _sex != "woman")
	{
		cout << "请输入正确的性别(man / woman)：";
		goto ejudge3;
	}
	sex = _sex;
	cout << "输入年龄" << endl;
ejudge4:
	cin >> _age;
	if (_age < 0)
	{
		cout << "请输入正确的年龄：";
		goto ejudge4;
	}
	age = _age;
	cout << "输入领域" << endl;
ejudge5:
	cin >> _area;
	if (_area[0] == ' ')
	{
		cout << "请输入正确的领域名：";
		goto ejudge5;
	}
	area = _area;
	cout << "输入课程成绩" << endl;
ejudge6:
	cin >> _kgrade;
	if (_kgrade > 100 || _kgrade < 0)
	{
		cout << "请输入正确的课程成绩(0~100)：";
		goto ejudge6;
	}
	kgrade = _kgrade;
	cout << "输入项目名称" << endl;
ejudge7:
	cin >> projectname;
	if (projectname[0] == ' ')
	{
		cout << "请输入正确的项目名称：";
		goto ejudge7;
	}
	project.name = projectname;
	cout << "输入项目级别" << endl;
ejudge8:
	cin >> projectlevel;
	if (projectlevel != 'A' && projectlevel != 'B' && projectlevel != 'C')
	{
		cout << "请输入正确的项目级别（A、B、C）：";
		goto ejudge8;
	}
	project.level = projectlevel;
	getgrade();
	getsum();
}
double SMaster::getgrade()
{
	int i;
	double _grade1 = 0;
	for (i = 0; i < 3; i++)
		_grade1 += (double)(10 * paper[i].level) / 90 * 100;
	grade1 = _grade1;
	return grade1;
}
double SMaster::getsum()
{
	double _Sgrade;
	getgrade();
	_Sgrade = grade1 * 0.3 + kgrade * 0.7;
	Sgrade = _Sgrade;
	return Sgrade;
}
double EMaster::getgrade()
{
	grade1 = 0;

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
ostream &operator<<(ostream &os, SMaster &s)
{
	os << setiosflags(ios::left)
	   << setw(14) << s.stuNum << setw(10) << s.name << setw(10) << s.sex << setw(10) << s.age << setw(10) << s.kgrade << setw(10) << s.major
	   << setw(5) << "名称:" << setw(2) << s.paper[0].name << setw(5) << " 等级:" << setw(6) << s.paper[0].level
	   << setw(5) << "名称:" << setw(2) << s.paper[1].name << setw(5) << " 等级:" << setw(6) << s.paper[1].level
	   << setw(5) << "名称:" << setw(2) << s.paper[2].name << setw(5) << " 等级:" << setw(6) << s.paper[2].level
	   << setw(10) << s.getgrade() << setw(10) << s.getsum() << endl;
	return os;
}
ostream &operator<<(ostream &os, EMaster &e)
{
	os << setiosflags(ios::left)
	   << setw(14) << e.stuNum << setw(10) << e.name << setw(10) << e.sex << setw(10) << e.age << setw(10) << e.kgrade << setw(10) << e.area
	   << setw(5) << "名称:" << setw(2) << e.project.name << setw(5) << " 等级:" << setw(6) << e.project.level
	   << setw(10) << e.getgrade() << setw(10) << e.getsum() << endl;
	return os;
}

//-------------------------------------统计函数---------------------------------------------------------------//

double SMaster::averageSMasterScore = 0.0;
double SMaster::sumSMasterScore = 0.0;
int SMaster::countSMasterNumber = 0;
int SMaster::a[6] = {0, 0, 0, 0, 0, 0};
void SMaster::statisticalData()
{
	averageSMasterScore = 0.0;
	sumSMasterScore = 0.0;
	countSMasterNumber = 0;
	for (int i = 0; i < 6; i++)
		a[i] = 0;
	if (shead->next == NULL)
	{
		cerr << "链表中无数据";
		system("pause");
	}
	SList *p = shead->next;
	while (p != NULL)
	{
		countSMasterNumber++;
		sumSMasterScore += p->AcademicMaster->Sgrade;
		if (p->AcademicMaster->Sgrade == 100.0)
			a[0]++;
		else if (p->AcademicMaster->Sgrade >= 90.0 && p->AcademicMaster->Sgrade < 100.0)
			a[1]++;
		else if (p->AcademicMaster->Sgrade >= 80 && p->AcademicMaster->Sgrade < 90)
			a[2]++;
		else if (p->AcademicMaster->Sgrade >= 70 && p->AcademicMaster->Sgrade < 80)
			a[3]++;
		else if (p->AcademicMaster->Sgrade >= 60 && p->AcademicMaster->Sgrade < 70)
			a[4]++;
		else
			a[5]++;
		p = p->next;
	}
	averageSMasterScore = (double)(sumSMasterScore / countSMasterNumber);
	cout << "学术硕士总人数" << countSMasterNumber << endl;
	cout << "平均分" << averageSMasterScore << endl;
	cout << "成绩分布" << endl;
	cout << "100分的人有：" << a[0] << "\t"
		 << "占百分比：" << ((double)a[0] / countSMasterNumber * 100) << "%" << endl;
	cout << "90-100分的人有：" << a[1] << "\t"
		 << "占百分比：" << ((double)a[1] / countSMasterNumber * 100) << "%" << endl;
	cout << "80-90分的人有：" << a[2] << "\t"
		 << "占百分比：" << ((double)a[2] / countSMasterNumber * 100) << "%" << endl;
	cout << "70-80分的人有：" << a[3] << "\t"
		 << "占百分比:" << ((double)a[3] / countSMasterNumber * 100) << "%" << endl;
	cout << "60-70分的人有：" << a[4] << "\t"
		 << "占百分比：" << ((double)a[4] / countSMasterNumber * 100) << "%" << endl;
	cout << "60分以下的人有：" << a[5] << "\t"
		 << "占百分比：" << ((double)a[5] / countSMasterNumber * 100) << "%" << endl;
	SList *q = shead->next;
	while (q != NULL)
	{
		for (q; q->next != NULL; q = q->next)
		{
			if (q->AcademicMaster->Sgrade > q->next->AcademicMaster->Sgrade)
			{
				SList *temp = q;
				q = q->next;
				q = temp;
			}
			cout << q->AcademicMaster->name << " " << q->AcademicMaster->stuNum << " " << q->AcademicMaster->sex << " " << q->AcademicMaster->kgrade
				 << " " << q->AcademicMaster->major << " " << q->AcademicMaster->age << " " << q->AcademicMaster->paper[0].name << " "
				 << q->AcademicMaster->paper[0].level << " " << q->AcademicMaster->paper[1].name << " " << q->AcademicMaster->paper[1].level << " "
				 << q->AcademicMaster->paper[2].name << " " << q->AcademicMaster->paper[2].level << " " << q->AcademicMaster->Sgrade << endl;
		}
		cout << q->AcademicMaster->name << " " << q->AcademicMaster->stuNum << " " << q->AcademicMaster->sex << " " << q->AcademicMaster->kgrade
			 << " " << q->AcademicMaster->major << " " << q->AcademicMaster->age << " " << q->AcademicMaster->paper[0].name << " "
			 << q->AcademicMaster->paper[0].level << " " << q->AcademicMaster->paper[1].name << " " << q->AcademicMaster->paper[1].level << " "
			 << q->AcademicMaster->paper[2].name << " " << q->AcademicMaster->paper[2].level << " " << q->AcademicMaster->Sgrade << endl;
		system("pause");
	}
}

double EMaster::averageEMasterScore = 0.0;
double EMaster::sumEMasterScore = 0.0;
int EMaster::countEMasterNumber = 0;
int EMaster::a[6] = {0, 0, 0, 0, 0, 0};
void EMaster::statisticalData()
{
	averageEMasterScore = 0.0;
	sumEMasterScore = 0.0;
	countEMasterNumber = 0;
	for (int i = 0; i < 6; i++)
		a[i] = 0;
	if (ehead->next == NULL)
	{
		cerr << "链表中无数据";
		system("pause");
	}
	EList *p = ehead->next;
	while (p != NULL)
	{
		countEMasterNumber++;
		sumEMasterScore += p->EngineeringMaster->Sgrade;
		if (p->EngineeringMaster->Sgrade == 100.0)
			a[0]++;
		else if (p->EngineeringMaster->Sgrade >= 90.0 && p->EngineeringMaster->Sgrade < 100.0)
			a[1]++;
		else if (p->EngineeringMaster->Sgrade >= 80 && p->EngineeringMaster->Sgrade < 90)
			a[2]++;
		else if (p->EngineeringMaster->Sgrade >= 70 && p->EngineeringMaster->Sgrade < 80)
			a[3]++;
		else if (p->EngineeringMaster->Sgrade >= 60 && p->EngineeringMaster->Sgrade < 70)
			a[4]++;
		else
			a[5]++;
		p = p->next;
	}
	averageEMasterScore = (double)(sumEMasterScore / countEMasterNumber);
	cout << "学术硕士总人数" << countEMasterNumber << endl;
	cout << "平均分" << averageEMasterScore << endl;
	cout << "成绩分布" << endl;
	cout << "100分的人有：" << a[0] << "/t占百分比：" << (double)(a[0] / countEMasterNumber) << endl;
	cout << "90-100分的人有：" << a[1] << "/t占百分比：" << (double)(a[1] / countEMasterNumber) << endl;
	cout << "80-90分的人有：" << a[2] << "/t占百分比：" << (double)(a[2] / countEMasterNumber) << endl;
	cout << "70-80分的人有：" << a[3] << "/t占百分比:" << (double)(a[3] / countEMasterNumber) << endl;
	cout << "60-70分的人有：" << a[4] << "/t占百分比：" << (double)(a[4] / countEMasterNumber) << endl;
	cout << "60分以下的人有：" << a[5] << "/t占百分比：" << (double)(a[5] / countEMasterNumber) << endl;
	EList *q = ehead->next;
	while (q != NULL)
	{
		for (q; q->next != NULL; q = q->next)
		{
			if (q->EngineeringMaster->Sgrade > q->next->EngineeringMaster->Sgrade)
			{
				EList *temp = q;
				q = q->next;
				q->next = temp;
			}
			cout << q->EngineeringMaster->name << " " << q->EngineeringMaster->stuNum << " " << q->EngineeringMaster->sex << " "
				 << q->EngineeringMaster->kgrade << " " << q->EngineeringMaster->area << " " << q->EngineeringMaster->age << " "
				 << q->EngineeringMaster->project.name << " " << q->EngineeringMaster->project.level << " " << q->EngineeringMaster->Sgrade << endl;
		}
		cout << q->EngineeringMaster->name << " " << q->EngineeringMaster->stuNum << " " << q->EngineeringMaster->sex << " "
			 << q->EngineeringMaster->kgrade << " " << q->EngineeringMaster->area << " " << q->EngineeringMaster->age << " "
			 << q->EngineeringMaster->project.name << " " << q->EngineeringMaster->project.level << " " << q->EngineeringMaster->Sgrade << endl;
	}
}
//************************************************************************************************************//
//*************************************链表操作***************************************************************//

void input();							 //录入
void insertSMaster(SMaster *s);			 //插入一个学术硕士
void insertEMaster(EMaster *e);			 //插入一个工程硕士
void insert();							 //插入
void seek();							 //查询
void del();								 //删除
void print();							 //输出
void modif();							 //修改
bool findDuplicationSMaster(SMaster *s); //查找是否有重复学号的学术硕士
bool findDuplicationEMaster(EMaster *e); //查找是否有重复学号的工程硕士

void input()
{

	cout << "\n*********开始录入学术硕士信息*********\n"
		 << endl;
	for (;;)
	{
		char ch;
		cout << "输入y继续录入，输入其他结束录入: ";
		cin >> ch;
		if (ch != 'y')
			break;
		SMaster *newsmaster = new SMaster;
		newsmaster->input();
		insertSMaster(newsmaster);
		cout << endl;
	}
	cout << "\n*********开始录入工程硕士信息*********\n"
		 << endl;
	for (;;)
	{
		char ch;
		cout << "输入y继续录入，输入其他结束录入: ";
		cin >> ch;
		if (ch != 'y')
			break;
		EMaster *newemaster = new EMaster;
		newemaster->input();
		insertEMaster(newemaster);
		cout << endl;
	}
}
void insertSMaster(SMaster *s)
{
	if (findDuplicationSMaster(s))
	{
		cout << "有重复，插入失败！" << endl;
		return;
	}
	SList *p = shead->next;
	SList *q = shead;
	SList *newslist = new SList;

	while (p != NULL && p->AcademicMaster->getNum() < s->getNum())
	{
		q = p;
		p = p->next;
	}
	newslist->AcademicMaster = s;
	newslist->next = p;
	q->next = newslist;
}
void insertEMaster(EMaster *e)
{
	if (findDuplicationEMaster(e))
	{
		cout << "有重复，插入失败！" << endl;
		return;
	}
	EList *p = ehead->next;
	EList *q = ehead;
	EList *newelist = new EList;

	while (p != NULL && p->EngineeringMaster->getNum() < e->getNum())
	{
		q = p;
		p = p->next;
	}
	newelist->EngineeringMaster = e;
	newelist->next = p;
	q->next = newelist;
}
void insert()
{
	int n;
	for (;;)
	{
		cout << "输入1插入学术硕士，输入2插入工程硕士，输入其他数字退出插入:";
		cin >> n;
		if (n == 1)
		{
			SMaster *newsmaster = new SMaster;
			newsmaster->input();
			insertSMaster(newsmaster);
		}
		else if (n == 2)
		{
			EMaster *newemaster = new EMaster;
			newemaster->input();
			insertEMaster(newemaster);
		}
		else
			return;
		cout << endl;
	}
}
void seek()
{
	int n;
	for (;;)
	{
		cout << "输入1查找学术硕士，输入2查找工程硕士，输入其他数字退出查找:";
		cin >> n;
		if (n == 1)
		{
			int t;
			SList *p = shead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				string stunum;
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
				cout << "输入姓名:";
				cin >> stuname;
				while (p != NULL && p->AcademicMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					cout << *(p->AcademicMaster);
			}
		}
		else if (n == 2)
		{
			int t;
			EList *p = ehead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				string stunum;
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
				cout << "输入姓名:";
				cin >> stuname;
				while (p != NULL && p->EngineeringMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					cout << *(p->EngineeringMaster);
			}
		}
		else
			return;
		cout << endl;
	}
}
void del()
{
	int n;
	for (;;)
	{
		cout << "输入1删除学术硕士，输入2删除工程硕士，输入其他数字退出删除:";
		cin >> n;
		if (n == 1)
		{
			int t;
			SList *p = shead->next;
			SList *q = shead;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				string stunum;
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
					cout << "删除成功!\n";
				}
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入姓名:";
				cin >> stuname;
				while (p != NULL && p->AcademicMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					q->next = p->next;
					free(p);
					cout << "删除成功!\n";
				}
			}
		}
		else if (n == 2)
		{
			int t;
			EList *p = ehead->next;
			EList *q = ehead;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				string stunum;
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
					cout << "删除成功!\n";
				}
			}
			else if (t == 2)
			{
				string stuname;
				cout << "输入姓名:";
				cin >> stuname;
				while (p != NULL && p->EngineeringMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
				{
					q->next = p->next;
					free(p);
					cout << "删除成功!\n";
				}
			}
		}
		else
			return;
		cout << endl;
	}
}
void print()
{
	int n;
	cout << "输入1输出学术硕士，输入2输出工程硕士:";
	cin >> n;
	if (n == 1)
	{
		SList *p = shead->next;
		if (p)
		{
			cout << "学术硕士\n";
			cout << setiosflags(ios::left);
			cout << setw(14) << "学号" << setw(10) << "姓名" << setw(10) << "性别" << setw(10) << "年龄" << setw(10) << "课程成绩" << setw(10) << "专业"
				 << setw(19) << "  第一篇论文" << setw(19) << "  第二篇论文" << setw(19) << "  第三篇论文"
				 << setw(10) << "论文成绩" << setw(10) << "总成绩" << endl;
		}
		for (; p != NULL; p = p->next)
			cout << *(p->AcademicMaster) << endl;
		cout << endl;
	}
	else if (n == 2)
	{
		EList *p = ehead->next;
		if (p)
		{
			cout << "学术硕士\n";
			cout << setiosflags(ios::left);
			cout << setw(14) << "学号" << setw(10) << "姓名" << setw(10) << "性别" << setw(10) << "年龄" << setw(10) << "课程成绩" << setw(10) << "领域"
				 << setw(19) << "    项目"
				 << setw(10) << "项目成绩" << setw(10) << "总成绩" << setw(10) << endl;
		}
		for (; p != NULL; p = p->next)
			cout << *(p->EngineeringMaster) << endl;
		cout << endl;
	}
}
void modif()
{
	int n;
	for (;;)
	{
		cout << "输入1修改学术硕士，输入2修改工程硕士，输入其他数字退出删除:";
		cin >> n;
		if (n == 1)
		{
			int t;
			SList *p = shead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				string stunum;
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
				cout << "输入姓名:";
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
			EList *p = ehead->next;
			cout << "输入1按学号查询，输入2按姓名查询:";
			cin >> t;
			if (t == 1)
			{
				string stunum;
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
				cout << "输入姓名:";
				cin >> stuname;
				while (p != NULL && p->EngineeringMaster->getName() != stuname)
					p = p->next;
				if (!p)
					cout << "无该名学术硕士!" << endl;
				else
					p->EngineeringMaster->input();
			}
		}
		else
			return;
		cout << endl;
	}
}
bool findDuplicationSMaster(SMaster *s)
{
	SList *p = shead->next;
	while (p != NULL)
	{
		if (p->AcademicMaster->getNum() == s->getNum())
			return true;
		p = p->next;
	}
	return false;
}
bool findDuplicationEMaster(EMaster *e)
{
	EList *p = ehead->next;
	while (p != NULL)
	{
		if (p->EngineeringMaster->getNum() == e->getNum())
			return true;
		p = p->next;
	}
	return false;
}
//****************************************文件操作**************************************************//
void getSMasterfile()
{
	ifstream fin("E:\\课程设计\\学术硕士信息表.txt");
	if (!fin)
	{
		cout << "文件打不开" << endl;
		return;
	}
	while (true)
	{
		SMaster *s = new SMaster;
		if (fin >> s->name >> s->stuNum >> s->sex >> s->kgrade >> s->major >> s->age >> s->paper[0].name >> s->paper[0].level >> s->paper[1].name >> s->paper[1].level >> s->paper[2].name >> s->paper[2].level)
			insertSMaster(s);
		else
		{
			fin.close();
			break;
		}
	}
}
void getEMasterfile()
{

	ifstream fin("E:\\课程设计\\工程硕士信息表.txt");
	if (!fin)
	{
		cout << "文件打不开" << endl;
		return;
	}
	while (true)
	{
		EMaster *m = new EMaster;
		if (fin >> m->name >> m->stuNum >> m->sex >> m->kgrade >> m->area >> m->age >> m->project.name >> m->project.level)
			insertEMaster(m);
		else
		{
			fin.close();
			break;
		}
	}
}
void getfile()
{
	getSMasterfile();
	getEMasterfile();
}
void saveEMasterfile()
{
	ofstream fout("E:\\课程设计\\工程硕士信息表.txt");
	if (!fout)
	{
		cout << "文件打不开" << endl;
		return;
	}
	EList *e = ehead->next;
	while (e != NULL)
	{
		fout << e->EngineeringMaster->name << " " << e->EngineeringMaster->stuNum << " " << e->EngineeringMaster->sex << " " << e->EngineeringMaster->kgrade << " " << e->EngineeringMaster->area << " " << e->EngineeringMaster->age << " " << e->EngineeringMaster->project.name << " " << e->EngineeringMaster->project.level << endl;
		e = e->next;
	}
	fout.close();
}
void saveSMasterfile()
{
	ofstream fout("E:\\课程设计\\学术硕士信息表.txt");
	if (!fout)
	{
		cout << "文件打不开" << endl;
		return;
	}
	SList *p = shead->next;
	while (p != NULL)
	{
		fout << p->AcademicMaster->name << " " << p->AcademicMaster->stuNum << " " << p->AcademicMaster->sex << " " << p->AcademicMaster->kgrade << " " << p->AcademicMaster->major << " " << p->AcademicMaster->age << " " << p->AcademicMaster->paper[0].name << " " << p->AcademicMaster->paper[0].level
			 << " " << p->AcademicMaster->paper[1].name << " " << p->AcademicMaster->paper[1].level << " " << p->AcademicMaster->paper[2].name << " " << p->AcademicMaster->paper[2].level << endl;
		p = p->next;
	}
	fout.close();
}
void savefile()
{
	saveSMasterfile();
	saveEMasterfile();
}
//**************************************************************************************************//
//****************************************界面******************************************************//
void welcome()
{
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
	if (user == "1704" && password == "666")
	{
		cout << "登录成功！" << endl;
		system("pause");
		system("cls");
	} //清屏
	else
	{
		cout << "登录失败，请重新输入账号密码" << endl;
		i++;
		if (i == 5) //失败五次自动退出
		{
			cout << "超过输入次数，系统自动退出" << endl;
			system("pause");
			exit(0);
		} //非正常退出
		goto part;
	}
}
void menu() //菜单页面
{
part:
	int i = 0;
	cout << "********************************************" << endl;
	cout << "**          研究生信息管理系统            **" << endl;
	cout << "**          1.研究生信息录入              **" << endl;
	cout << "**          2.研究生信息插入              **" << endl;
	cout << "**          3.研究生信息删除              **" << endl;
	cout << "**          4.研究生信息输出              **" << endl;
	cout << "**          5.研究生信息修改              **" << endl;
	cout << "**          6.研究生信息查找              **" << endl;
	cout << "**          7.研究生信息统计              **" << endl;
	cout << "**          8.打开文件                    **" << endl;
	cout << "**          9.保存文件                    **" << endl;
	cout << "**          0.退出系统                    **" << endl;
	cout << "********************************************" << endl;
	cout << "请选择功能" << endl;
	cin >> i;
	switch (i)
	{

	case 1:

		input();
		system("pause");
		system("cls");
		break;
		;
	case 2:

		insert();
		system("pause");
		system("cls");
		break;
	case 3:

		del();
		system("pause");
		system("cls");
		break;
	case 4:
		print();
		system("pause");
		system("cls");
		break;
	case 5:
		modif();
		system("pause");
		system("cls");
		break;
	case 6:
		seek();
		system("pause");
		system("cls");
		break;
	case 7:
		SMaster::statisticalData();
		EMaster::statisticalData();
		system("pause");
		system("cls");
		break;
	case 8:
		getfile();
		system("pause");
		system("cls");
		break;
	case 9:
		savefile();
		system("pause");
		system("cls");
		break;
	case 0:
		return;
	default:
		cout << "您输入的数据有误，请重新输入" << endl;
		goto part;
	}
	goto part;
}
//**************************************************************************************************//
//****************************************测试******************************************************//

void init()
{
	shead = new SList;
	ehead = new EList;
	shead->next = NULL;
	ehead->next = NULL;
}
int main()
{
	init();
	welcome();
	menu();
	return 0;
}