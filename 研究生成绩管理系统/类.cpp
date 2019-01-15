// ConsoleApplication5.cpp: 定义控制台应用程序的入口点。

#include<string>
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
	double kgrade; //课程成绩
};

class SMaster : public graduate { //学术硕士
protected:
	string major; //主修
	struct Paper paper[3]; //发表论文(判断是否多于三个)
	double grade1;                    //论文成绩
	double Sgrade; //总成绩
	double getgrade(); //计算论文成绩算法
	double getsum();   //计算总成绩算法（每次论文修改后需重新调用）
public:
	static struct SList *Shead;
	void getName() {
		cout << "输入姓名" << endl;
		cin >> name;
	}
	void getStuNum() {
		cout << "输入学号" << endl;
		cin >> stuNum;
	}
	void getSex() {
		cout << "输入性别" << endl;
		cin >> sex;
	}
	void getKgrade() {
		cout << "输入课程成绩" << endl;
		cin >> kgrade;
	}
	void getMajor() {
		cout << "输入专业" << endl;
		cin >> major;
	}
	void getAge() {
		cout << "输入年龄" << endl;
		cin >> age;
	}
	void getPaper() {
		cout << "输入论文的个数" << endl;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cout << "输入名称与等级" << endl;
			cin >> paper[i].name >> paper[i].level;
		}
	}
	SMaster() {
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
		getName();
		getStuNum();
		getSex();
		getAge();
		getKgrade();
		getMajor();
		getPaper();
		getsum();
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
	static M Mhead;
	EMaster() {
		stuNum = 0;
		name = "";
		sex = "";
		age = 0;
		kgrade = 0;
		area = "";
		project.name = "";
		project.level = ' ';
		getName();
		getNum();
		getSex();
		getAge();
		getArea();
		getKgrade();
		getProject();
	}
	void getName() {
		cout << "输入姓名" << endl;
		cin >> name;
	}
	void getNum() {
		cout << "输入学号" << endl;
		cin >> stuNum;
	}
	void getSex() {
		cout << "输入性别" << endl;
		cin >> sex;
	}
	void getAge() {
		cout << "输入年龄" << endl;
		cin >> age;
	}
	void getArea() {
		cout << "输入领域" << endl;
		cin >> area;
	}
	void getKgrade() {
		cout << "输入课程成绩" << endl;
		cin >> kgrade;
	}
	void getProject() {
		cout << "输入项目名称" << endl;
		cin >> project.name;
		cout << "输入项目级别" << endl;
		cin >> project.level;
	}
};

typedef struct SList { //学术硕士信息链表
	SMaster SM;
	struct SList *next;
}*S;
typedef struct MList {//工程硕士信息链表
	EMaster EM;
	struct MList *next;
}*M;

int main()
{

	return 0;
}
void inSert() {
	cout << "学术硕士插入（A）工程硕士（B）" << endl;
	if (getchar() == 'A') {
		SMaster s();
		struct SList *sl = SMaster::Shead;
		while (sl->next!=NULL)
		{
			if()
		}
	}
	
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