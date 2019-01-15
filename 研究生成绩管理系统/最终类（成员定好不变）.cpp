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


struct Paper { //论文
	string name;
	int level;
};
struct Project {//项目
	string name;
	string level;
};



//***************************************类的定义********************************************************//
//研究生类的定义
class graduate {    
protected:
	string stuNum;    //学号
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
	string getNum()const;          //返回学号
	string getName()const;      //返回姓名
	double getgrade();          //计算论文成绩算法
	double getsum();            //计算总成绩算法（每次论文修改后需重新调用）
	friend ostream& operator<<(ostream&, SMaster&);	//重载cout<<函数
	friend istream& operator>>(istream&, SMaster&); //重载cin>>函数
	static void statisticalData(SMaster*);	        //统计函数
	void charachter();			//属性栏
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
	EMaster*pEMaster;            //确定此对象的地址
	EMaster();                  //构造函数
	void input();             //录入数据
	string getNum()const;          //返回学号
	string getName()const;      //返回姓名
	double getgrade();        //计算项目成绩
	double getsum();          //计算总成绩算法(把项目级别ABC转化为分数)
	friend ostream& operator<<(ostream&, EMaster&);	  //重载cin<<函数
	friend istream& operator>>(istream&, EMaster&);   //重载cout>>函数
	static void statisticalData(EMaster*);	          //统计函数
	void charachter();			//属性栏
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
string SMaster::getNum()const { return stuNum; }
string SMaster::getName()const {return name;}
string EMaster::getNum()const { return stuNum; }
string EMaster::getName()const { return name; }  
EMaster::EMaster() {
	stuNum = "无";
	name = "无";
	sex = "无";
	age = 0;
	kgrade = 0;
	area = "无";
	project.name = "无";
	project.level = "无";
	pEMaster = this;
}
SMaster::SMaster() {
	stuNum = "无";
	name = "无";
	sex = "无";
	age = 0;
	kgrade = 0;
	major = "无";
	Sgrade = 0;
	for (int i = 0; i < 3; i++) {
		paper[i].name = "";		//这里不建议改成"无"
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
	judge1: if(sex != "男" || sex != "女"){
		cout << "请输入正确的性别：";
		cin >> sex;
		goto judge1;
	}
	cout << "输入课程成绩" << endl;
	cin >> kgrade;
	judge2: if(kgrade > 100 || kgrade < 0){
		cout << "请输入正确的成绩：";
		cin >> kgrade;
		goto judge2;
	}
	cout << "输入专业" << endl;
	cin >> major;
	cout << "输入年龄" << endl;
	cin >> age;
	cout << "输入论文的个数" << endl;
	int n;
	cin >> n;
	judge3: if(n > 3 || n < 0){
		cout << "请输入正确的n值：";
		cin >> n;
		goto judge3;
	}
	for (int i = 0; i < n; i++) {
		cout << "输入名称与等级" << endl;
		cin >> paper[i].name;
		cin >> paper[i].level;
		judge: if(paper[i].level > 3 || paper[i].level < 0){
			cout << "请输入正确的等级：";
			cin >> paper[i].level;
			goto judge; 
		}
	}
}
void EMaster::input() {
	cout << "输入姓名" << endl;
	cin >> name;
	cout << "输入学号" << endl;
	cin >> stuNum;
	cout << "输入性别" << endl;
	cin >> sex;
	judge4: if(sex != "男" || sex != "女"){
		cout << "请输入正确的性别：";
		cin >> sex;
		goto judge4;
	}
	cout << "输入年龄" << endl;
	cin >> age;
	cout << "输入领域" << endl;
	cin >> area;
	cout << "输入课程成绩" << endl;
	cin >> kgrade;
	judge5: if(kgrade > 100 || kgrade < 0){
		cout << "请输入正确的成绩：";
		cin >> kgrade;
		goto judge5;
	}
	string str;
	cout << "有无项目？\t";
	cin  >> str;
	if(str == "有"){
		cout << "输入项目名称" << endl;
		cin >> project.name;
		cout << "输入项目级别" << endl;
		cin >> project.level;
		judge6: if(project.level != "A" && project.level != "B" && project.level != "C"){
			cout << "请输入正确的项目级别：";
			cin >> project.level;
			goto judge6;
		}
	}
}
// double SMaster::getgrade()
// {
// 	if(paper[0].name == "")
// 		return 0.0;
// 	int i;
// 	int a[] = {0, 0, 0};
// 	for (i = 0; i < 3; i++){
// 		a[i] = (int)paper[i].level - 48;
// 		grade1 += ((double)paper[i].level / 90) * 100;
// 	}
// 	return grade1;
// }
double SMaster::getgrade()
{
	if(paper[0].name == "")
		return 0.0;
	int i;
	for (i = 0; i < 3; i++)
		grade1 += ((double)paper[i].level * 10 / 90) * 100;
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

	if (project.level == "A")
		grade1 = 90.0;
	else if (project.level == "B")
		grade1 = 75.0;
	else if (project.level == "C")
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

// ostream& operator << (ostream &os, SMaster &s){
// 	os << s.stuNum << "\t" << s.name << "\t" << s.sex << "\t" << s.age << "\t" << s.kgrade << "\t\t" << s.major << "\t" << ((s.paper[0].name == "")?"\t":s.paper[0].name) << " " << ((s.paper[0].level == 0)?' ': s.paper[0].level ) << ",\t" << ((s.paper[1].name == "")?"\t":s.paper[1].name) << " " << ((s.paper[1].level == 0)?' ':s.paper[1].level) << "\t" << ((s.paper[2].name == "")?"\t":s.paper[2].name) << " " << ((s.paper[2].level == 0)?' ':s.paper[2].level) << ",\t" << s.getgrade() << "\t   " << s.getsum() << endl;
// 	return os;
// }
ostream& operator << (ostream &os, SMaster &s){
	os << s.stuNum << "\t" << s.name << "\t" << s.sex << "\t" << s.age << "\t" << s.kgrade << "\t\t" << s.major << "\t" << ((s.paper[0].name == "")?"无\t":s.paper[0].name) << " " << ((s.paper[0].level == 0)?' ':(char)(s.paper[0].level + 48)) << "\t" << ((s.paper[1].name == "")?"\t":s.paper[1].name) << " " << ((s.paper[1].level == 0)?' ':(char)(s.paper[1].level + 48)) << "\t" <<((s.paper[2].name == "")?"\t":s.paper[2].name) << " " << ((s.paper[2].level == 0)?' ':(char)(s.paper[2].level + 48)) << "\t" << s.getgrade() << "\t  " << s.getsum() << endl;
	return os;
}
ostream& operator << (ostream &os, EMaster& e){
	os << e.stuNum << "\t" << e.name << "\t" << e.sex << "\t" << e.age << "\t" << e.kgrade << "\t\t" << e.area << "\t" << (e.project.name == "无" ? "无\t\t":e.project.name) << "\t" << (e.project.level == "无" ? " " : e.project.level) << "\t\t" << e.getgrade() << "\t  " << e.getsum() << endl;
	return os;
}

void SMaster::charachter(){
	cout << "学术硕士\n学号\t姓名\t性别  年龄\t课程成绩\t主修\t论文以及论文水平\t\t\t\t  论文成绩  总成绩" << endl;
}
void EMaster::charachter(){
	cout << "工程硕士\n学号\t学号\t性别  年龄\t课程成绩\t领域\t参与项目名称\t\t项目级别\t项目成绩  总成绩" << endl;
}
//************************************************************************************************************//





//*************************************测试**************************************//
void insert(SMaster* s) {
	SList* p = shead->next;
	SList* q = shead;
	while (p != NULL && p->AcademicMaster->getNum() < s->getNum())
	{
		p = p->next; q = q->next;
	}
	SList* newSMater = new SList;
	newSMater->AcademicMaster = s;
	newSMater->next = q->next;
	q->next = newSMater;
}
void insert(EMaster* e) {
	EList* p = ehead->next;
	EList* q = ehead;
	while (p != NULL && p->EngineeringMaster->getNum() < e->getNum())
	{
		p = p->next; q = q->next;
	}
	EList* newEMater = new EList;
	newEMater->EngineeringMaster = e;
	newEMater->next = q->next;
	q->next = newEMater;
}
void creat(SMaster s) {
	s.input();
	insert(&s);
	s.charachter();
	cout << s;
}
void create(EMaster e){
	e.input();
	insert(&e);
	e.charachter();
	cout << e;
}
void init() {
	shead = new SList;
	ehead = new EList;
	shead->next = NULL;
	ehead->next = NULL;
}
int main() {
	SMaster s;
	EMaster e;
	init();
	creat(s);
	// create(e);
	system("pause");
    return 0;
}