#pragma once
#include<iostream>
#include<queue>
#include<math.h>
#include<map>
#include<limits>
#include<climits>
#include<limits.h>
#include<time.h>
using namespace std;
struct person
{
	int need;//所需要的时间
	int mod;//选择的业务模式
	int num;//编号
	int in;//进入时间
};
class Window {
private:
	int num;//窗口编号
	int statue;//当前状态
	int worktime;//剩下的工作时间
	person guest;//当前在服务的客人
public:
	//设置当前窗口的编号
	void setnum(int t) {
		num = t;
	}
	//获得当前的顾客
	person &getg() {
		return guest;
	}
	//构造函数，初始化工作状态以及服务顾客
	Window() {
		statue = 0;
		guest.need = 0;
	}
	//状态为0 空 状态为1 工作
	//设置工作时长
	void setw(int w) {
		worktime = w;
	}
	//设置当前服务的顾客
	void setguest(person in) {
		guest.in = in.in;
		guest.mod = in.mod;
		guest.need = in.need;
		guest.num = in.num;
	}
	//窗口工作
	int wwork() {
		//当顾客需要的时间在这个时间单元可以结束，那么可在这个时间周期退出顾客
	   if (guest.need == 1) {
		   cout << num << " window finish person " << guest.num << endl;
			worktime--;
			guest.need--;
			statue = 2;
		}
	   //空闲中
		else if (guest.need == 0) {
		    cout << num << " window no person" << endl;
			worktime--;
			statue = 0;
		}
		//正在工作
		else {
			cout << num << " window now working person num:" << guest.num << endl;
			worktime--;
			guest.need--;
			statue = 1;
		}
		return statue;
	}
	//返回当前状态，并且不改变状态值
	int getstatue() {
		return statue;
	}
};
template<typename T>
class Bank {
private:
	Window *window;//窗口数组
	int come;//来的人统计
	int waittall;//等待的总时间
	map<int, int> modm;//匹配每种模式需要的时间
	int maxtime;//剩下的工作时间总长度
	queue<T> line;//总队列
	int counter;//离开的人的计数器
	int alltime;//工作时间总长度
public:
	//清空数据
	~Bank() {
		delete[] window;
	}
	Bank( int xtime,int mods) {
		window = new Window[5];
		//编号及设置工作时间
		for (int t = 0; t < 5; t++) {
			window[t].setnum(t + 1);
			window[t].setw(xtime);
		}
		alltime = xtime;
		waittall = 0;
		come = 0;
		counter = 0;
		maxtime = xtime;
		//匹配各种的模式
		for (int t = 0; t < mods; t++) {
			int time;
			cout << "the " << t << " mods need (mins):" << endl;
			cin >> time;
			modm[t] = time / 5;
		}
	}
	//增加等待时间
	void setwait(int t) {
		waittall += t;
	}
	//返回处理人数
	int getcounter() { return counter; }
	//返回总等待时间
	int getwait() { return waittall; }
	//返回队列长度
	int size() {
		return line.size();
	}
	//返回最前面的顾客
	T front() {
		return line.front();
	}
	//顾客离开银行
	void pop(int t) {
		counter++;
		waittall = waittall +alltime-maxtime- window[t].getg().in;
		cout << "a person left" << endl;
	}
	int work() {
		int flag = 0;//判断是否所有的窗口空闲
		for (int t = 0; t < 5; t++) {
			if (window[t].wwork() != 0)flag = 1;//先进行工作，改变窗口状态
		}
		cout << endl;
		if (line.size()==0&&flag==0) {
			maxtime--;
			return -1;
		}
		else {
			if ((line.size()>0 && (line.front().need > maxtime&&flag == 0)||maxtime==0))return 3;
			else {
				for (int t = 0; t < 5; t++) {
					if (window[t].getstatue() == 2|| window[t].getstatue() == 0) {
						if(window[t].getstatue() == 2)pop(t);
						if (line.size() > 0 &&line.front().need <= maxtime) {
							person m = line.front();
							window[t].setguest(m);
							line.pop();
						}
					}
				}
			}
		}
		maxtime--;
		return 2;
	}
	//-1无人 返回1 结束一个人 返回2 继续工作 返回3 结束工作，时间结束
	//客人进入银行
	bool enter(T in) {
		come++;
		in.num = come;
		in.need = modm.at(in.mod);
			cout << "a person enter\n";
			line.push(in);
			return true;
	}
	int getcome() {
		return come;
	}
};