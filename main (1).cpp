#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<ctime>
using namespace std;

class timer{
int limit;
time_t start;
public:
timer(int s){
limit=s;
start=0;
}
void startTimer(){
start=time(0);
}
int timeLeft(){
return limit-(time(0) - start);
}
int expired(){
if(timeLeft()<= 0)
return 1;
else
return 0;
}
};

class user{
public:
int adminlogin(){
string u,p;
cout<<"Admin name:";
cin>>u;
cout<<"Admin password:";
cin>>p;
if(u=="admin" && p=="admin123")
return 1;
cout<<"invalid login"<<endl;
return 0;
}

int stulogin(){
string u,p;
cout<<"student name:";
cin>>u;
cout<<"student password:";
cin>>p;
if(u=="student" && p=="stu123")
return 1;
cout<<"invalid login"<<endl;
return 0;
}
};

class que{
public:
string q,o1,o2,o3,o4,corr;

void displayque(){
cout<<q<<endl;
cout<<"1:"<<o1<<endl;
cout<<"2:"<<o2<<endl;
cout<<"3:"<<o3<<endl;
cout<<"4:"<<o4<<endl;
}
};

class exam{
vector<que>questions;
int timeque;

public:
void addquestion(){
int n,t;
cout<<"Enter no of questions";
cin>>n;
cout<<"Enter time per que";
cin>>t;
cin.ignore();
ofstream f("questions.txt");
f<<t<<endl;
for(int i=0;i<n;i++){
que qo;
cout<<"Question"<<i+1<<" "<<endl;
getline(cin,qo.q);
cout<<"op 1 ";
getline(cin,qo.o1);
cout<<"op 2 ";
getline(cin,qo.o2);
cout<<"op 3 ";
getline(cin,qo.o3);
cout<<"op 4 ";
getline(cin,qo.o4);
cout<<"correct(1,2,3,4) ";
cin>>qo.corr;
cin.ignore();

f<<qo.q<<endl<<qo.o1<<endl<<qo.o2<<endl<<qo.o3<<endl<<qo.o4<<endl<<qo.corr<<endl;
}

f.close();
cout<<"question saved"<<endl;
}
void loadquestions() {
ifstream f("questions.txt");
if (!f) {
cout << "No question file found"<<endl;
return;
}
f >> timeque;
f.ignore();
que qo;
while (getline(f, qo.q)) {
getline(f, qo.o1);
getline(f, qo.o2);
getline(f, qo.o3);
getline(f, qo.o4);
getline(f, qo.corr);
questions.push_back(qo);
}
f.close();
}
void startexam() {
int score = 0;
string ans;
cout << "Time per question: " << endl<<timeque<< "seconds"<<endl;
for (int i = 0; i < (int)questions.size(); i++) {
timer to(timeque);
to.startTimer();
cout << "\nQ" << i + 1 << ": ";
questions[i].displayque();
cout << "Enter answer: ";
cin >> ans;
if (to.expired() == 1) {
cout << "Time's up! Answer not counted."<<endl;
} else {
cout << "Time left: " << to.timeLeft() << " seconds"<<endl;
if (ans == questions[i].corr) {
cout << "Correct"<<endl;
score++;
} else {
cout<<"Wrong! Correct answer:"<<questions[i].corr<<endl;
}
}
} cout<<"FinalScore:"<<score<<"/"<<questions.size()<<endl;
}
};

int main(){
user u;
exam e;
int ch;
cout<<"1.admin"<<endl<<"2.student"<<endl;
cin>>ch;
if(ch==1){
if(u.adminlogin()==1){
e.addquestion();
}
}
else if(ch==2){
if(u.stulogin()==1){
e.loadquestions();
e.startexam();
}
}
else{
cout<<"invalid"<<endl;
}
return 0;
}