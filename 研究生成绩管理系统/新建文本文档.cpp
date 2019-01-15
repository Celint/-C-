#include<iostream>
using namespace std;

struct Paper { //论文
	string name;
	int level;
};
struct Project {//项目
	string name;
	char level;
};


class graduate {    //研究生类
protected:
	int stuNum;  //学号
	string name;  //姓名
	string sex;  //性别
	int age;   //年龄
	double grade; //课程成绩
};

class SMaster : public graduate { //学术硕士
protected:
	string major; //主修
	struct Paper paper[3]; //发表论文(判断是否多于三个)
	double grade1;                    //论文成绩
	double Sgrade; //总成绩
	double getgrade(); //计算论文成绩算法
	double getsum();  //计算总成绩算法（每次论文修改后需重新调用）
public:
    void input();
    void insert();
	SMaster() {
		stuNum = 0;
		name = "无";
		sex = "未知";
		age = 0;
		grade = 0;
		major = "";
		Sgrade = 0;
		for (int i = 0; i < 3; i++) {
			paper[i].name = "";
			paper[i].level = 0;
		}
	}
};
class EMaster : public graduate {//工程硕士
protected:
	string area; //领域
	struct Project project; //参与项目
	double grade1;                    //项目成绩
	double getgrade();
	double Sgrade;//总成绩
	double getsum();//计算总成绩算法(把项目级别ABC转化为分数)
public:
	void input();
	void insert();
	EMaster() {
		stuNum = 0;
		name = "";
		sex = "";
		age = 0;
		grade = 0;
		area = "";
		project.name = "";
		project.level = ' ';
	}

};
void SMaster::input() {
	cout << "输入姓名" << endl;
	cin >> name;
	cout << "输入学号" << endl;
	cin >> stuNum;
	cout << "输入性别" << endl;
	cin >> sex;
	cout << "输入课程成绩" << endl;
	cin >> grade;
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
	cin >> grade;
	cout << "输入项目名称" << endl;
	cin >> project.name;
	cout << "输入项目级别" << endl;
	cin >> project.level;
}
typedef struct SList { //学术硕士信息链表
	SMaster AMaster;
	struct SList *next;
}SList,*S;
typedef struct EList {//工程硕士信息链表
	EMaster EnMaster;
	struct EList *next;
}EList,*M;
SList* shead;        //定义学术硕士头结点
EList* ehead;        //定义工程硕士头结点
void SMaster::insert() {
	SList* p = shead->next;
	SList* q = shead;
	while (p != NULL && p->AMaster.stuNum < this->stuNum)
	{
		p = p->next; q = q->next;
	}
	SList* newSMater = new SList;
	newSMater->AMaster = *this;
	newSMater->next = q->next;
	q->next = newSMater;
}
void EMaster::insert() {
EList* p = ehead->next;
	EList* q = ehead;
	while (p != NULL && p->EnMaster.stuNum < this->stuNum)
	{
		p = p->next; q = q->next;
	}
	EList* newEMater = new EList;
	newEMater->EnMaster = *this;
	newEMater->next = q->next;
	q->next = newEMater;
}
void creat() {
	for (;;)
	{
		char ch;
		cout << "输入1创建学术硕士，输入2创建工程硕士,输入其他停止创建" << endl;
		cin >> ch;
		if (ch == '1')
		{
			SMaster newSMaster;
			newSMaster.input();
			newSMaster.insert();
		}
		else if (ch == '2')
		{
			EMaster newEMaster;
			newEMaster.input();
			newEMaster.insert();
		}
		else
			return;
	}
}
void init() {
	shead = new SList;
	ehead = new EList;
	shead->next = NULL;
	ehead->next = NULL;
}
double SMaster::getgrade()
{
	int i;
	for (i = 0; i<3; i++)
		grade1 += paper[i].level*10 / 90 * 100;
	return grade1;
}
double SMaster::getsum()
{
	getgrade();
	Sgrade = grade1 * 0.3 + grade * 0.7;
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
	Sgrade = grade1 * 0.5 + grade * 0.5;
	return Sgrade;
}
struct Section1
{
    int p[6];
    double percent[6];
};
class all1:public SMaster
{
public:
    int count;   //总人数
    double aver; //平均分
    void average();   //平均成绩
    struct Section1 section;//分数查询
    int numcount();
    void getnum();
    void getpercent();
};

void all1::average()        //学术研究生平均分
{
    int sum=0;
    for(int i=0;i<count;i++)
        sum+=grade;
    aver=sum/count;
}
void all1::getnum()          //学术研究生各分数段人数
{
    if(grade==100) section.p[0]++;
    else if(grade>=90&&grade<100) section.p[1]++;
    else if(grade>=80&&grade<90) section.p[2]++;
    else if(grade>=70&&grade<80) section.p[3]++;
    else if(grade>=60&&grade<70) section.p[4]++;
    else section.p[5]++;
}
int all1::numcount()          //学术研究生人数
{
    count=section.p[0]+section.p[1]+section.p[2]+section.p[3]+section.p[4]+section.p[5];
    return count;
}
void all1::getpercent()       //学术研究生分数段所占百分比
{
    if(grade==100) section.percent[0]=section.p[0]/count;
    else if(grade>=90&&grade<100) section.percent[1]=section.p[1]/count;
    else if(grade>=80&&grade<90) section.percent[2]=section.p[2]/count;
    else if(grade>=70&&grade<80) section.percent[3]=section.p[3]/count;
    else if(grade>=60&&grade<70) section.percent[4]=section.p[4]/count;
    else section.percent[5]=section.p[5]/count;
}
struct Section2
{
    int p[6];
    double percent[6];
};
class all2:public EMaster
{
public:
    int count;
    double aver;
    void average();
    struct Section2 section;
    int numcount();
    void getnum();
    void getpercent();
};

void all2::average()      //全体工程研究生平均分
{
    int sum=0;
    for(int i=0;i<count;i++)
        sum+=grade;
    aver=sum/count;
}
void all2::getnum()        //分数段人数
{
    if(grade==100) section.p[0]++;
    else if(grade>=90&&grade<100) section.p[1]++;
    else if(grade>=80&&grade<90) section.p[2]++;
    else if(grade>=70&&grade<80) section.p[3]++;
    else if(grade>=60&&grade<70) section.p[4]++;
    else section.p[5]++;
}
int all2::numcount()       //工程研究生人数
{
    count=section.p[0]+section.p[1]+section.p[2]+section.p[3]+section.p[4]+section.p[5];
    return count;
}
void all2::getpercent()    //分数段所占百分比
{
    if(grade==100) section.percent[0]=section.p[0]/count;
    else if(grade>=90&&grade<100) section.percent[1]=section.p[1]/count;
    else if(grade>=80&&grade<90) section.percent[2]=section.p[2]/count;
    else if(grade>=70&&grade<80) section.percent[3]=section.p[3]/count;
    else if(grade>=60&&grade<70) section.percent[4]=section.p[4]/count;
    else section.percent[5]=section.p[5]/count;
}
void srank()       //排序
{
}
int main(void) {
	init();
	creat();
}
