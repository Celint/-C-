#include<iostream>
#include<fstream>
using namespace std;
class student
{
public:
    int num;
    string name;
    char sex;
    int age;
    float score;
};
/**********学术硕士*************/
class Paper
{
public:
    int level;
    string title;
    void input();
    void output();

};
class engineer;
class academic:public student
{
public:
    string major;
    Paper paper[3];
    float grade;
    float sgrade;
public:
    float sum;          //全体总成绩
    int count;          //总人数
    float average;
    int p[6];    //总分分段人数
    friend void ifstudent(academic a[],engineer e[]);
    friend void ofstudent(academic a[],engineer e[]);
    void sumpaper();    //论文成绩
    void ssum();        //论文总成绩
    void asum();        //硕士成绩
    void aver();        //硕士平均成绩
    void section();     //分段统计
    int findnum();      //学号查询
    int findname();     //分数查询
};
void Paper::input()
{
    cout<<"enter the title of the paper:";
    cin>>title;
    cout<<"enter the level of the paper(1,2,3):";
    cin>>level;
    if(level!=1&&level!=2&&level!=3){
        cin>>level;
    }
}
void Paper::output()
{
    cout<<"title of the paper:"<<title<<"\t";
    cout<<"level of the paper:"<<level<<endl;
}
void academic::sumpaper()
{
    float grade=0;
    int i;
    for(i=0;i<3;i++)
        grade+=paper[i].level/90*100;
}
void academic::ssum()
{
    sumpaper();
    sgrade=grade*0.3+score*0.7;
}
void academic::asum()
{
    sum+=sgrade;
    count++;
}
void academic::aver()
{
    average=sum/count;
}
void academic::section()
{
    if(sgrade==100) p[0]++;
    else if(sgrade>=90&&sgrade<100) p[1]++;
    else if(sgrade>=80&&sgrade<90) p[2]++;
    else if(sgrade>=70&&sgrade<80) p[3]++;
    else if(sgrade>=60&&sgrade<70) p[4]++;
    else p[5]++;
}
int academic::findnum()
{
    int n;
    if(num==n)
        return 1;
    else
        return 0;
}
int academic::findname()
{
    string n;
    if(name==n)
        return 1;
    else
        return 0;
}
/**********工程硕士*************/
class Project
{
public:
    string title;
    char level;
    void input();
    void output();
};
class engineer:public student
{
public:
    string area;
    Project project;
    float grade;
    float sgrade;
public:
    float sum;          //全体总成绩
    int count;          //总人数
    float average;
    int p[6];    //总分分段人数
    friend void ifstudent(academic a[],engineer e[]);
    friend void ofstudent(academic a[],engineer e[]);
    void sumpaper();    //论文成绩
    void ssum();        //论文总成绩
    void asum();        //硕士成绩
    void aver();        //硕士平均成绩
    void section();     //分段统计
    int findnum();      //学号查询
    int findname();     //分数查询
};
void Project::input()
{
    cout<<"enter the title of the project:";
    cin>>title;
    cout<<"enter the level of the project(A,B,C):";
    cin>>level;
    if(level!='A'&&level!='B'&&level!='C')
        cin>>level;
}
void Project::output()
{
    cout<<"title of the project:"<<title<<"\t";
    cout<<"level of the project:"<<level<<endl;
}
void engineer::sumpaper()
{
    float grade=0;

    if(project.level=='A')
        grade=90.0;
    else if(project.level=='B')
        grade=75.0;
    else if(project.level=='C')
        grade=60.0;
    else
        grade=0.0;
}

void engineer::ssum()
{
    sumpaper();
    sgrade=grade*0.5+score*0.5;
}
void engineer::asum()
{
    sum+=sgrade;
    count++;
}
void engineer::aver()
{
    average=sum/count;
}
void engineer::section()
{
    if(sgrade==100) p[0]++;
    else if(sgrade>=90&&sgrade<100) p[1]++;
    else if(sgrade>=80&&sgrade<90) p[2]++;
    else if(sgrade>=70&&sgrade<80) p[3]++;
    else if(sgrade>=60&&sgrade<70) p[4]++;
    else p[5]++;
}
int engineer::findnum()
{
    int n;
    if(num==n)
        return 1;
    else
        return 0;
}
int engineer::findname()
{
    string n;
    if(name==n)
        return 1;
    else
        return 0;
}
/********************************/
typedef struct slist
{
    class academic;
    struct slist *next;
}*s;
typedef struct mlist
{
    class engineer;
    struct mlist *next;
}*m;
/********************************/
void ifstudent(academic a[],engineer e[])  //文件输入信息
{

}
void ofstudent(academic a[],engineer e[])  //信息保存
{

}
/********************************/
int main()
{
    cout << "Hello world." << endl;
    system("pause");
}
