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
	int need;//����Ҫ��ʱ��
	int mod;//ѡ���ҵ��ģʽ
	int num;//���
	int in;//����ʱ��
};
class Window {
private:
	int num;//���ڱ��
	int statue;//��ǰ״̬
	int worktime;//ʣ�µĹ���ʱ��
	person guest;//��ǰ�ڷ���Ŀ���
public:
	//���õ�ǰ���ڵı��
	void setnum(int t) {
		num = t;
	}
	//��õ�ǰ�Ĺ˿�
	person &getg() {
		return guest;
	}
	//���캯������ʼ������״̬�Լ�����˿�
	Window() {
		statue = 0;
		guest.need = 0;
	}
	//״̬Ϊ0 �� ״̬Ϊ1 ����
	//���ù���ʱ��
	void setw(int w) {
		worktime = w;
	}
	//���õ�ǰ����Ĺ˿�
	void setguest(person in) {
		guest.in = in.in;
		guest.mod = in.mod;
		guest.need = in.need;
		guest.num = in.num;
	}
	//���ڹ���
	int wwork() {
		//���˿���Ҫ��ʱ�������ʱ�䵥Ԫ���Խ�������ô�������ʱ�������˳��˿�
	   if (guest.need == 1) {
		   cout << num << " window finish person " << guest.num << endl;
			worktime--;
			guest.need--;
			statue = 2;
		}
	   //������
		else if (guest.need == 0) {
		    cout << num << " window no person" << endl;
			worktime--;
			statue = 0;
		}
		//���ڹ���
		else {
			cout << num << " window now working person num:" << guest.num << endl;
			worktime--;
			guest.need--;
			statue = 1;
		}
		return statue;
	}
	//���ص�ǰ״̬�����Ҳ��ı�״ֵ̬
	int getstatue() {
		return statue;
	}
};
template<typename T>
class Bank {
private:
	Window *window;//��������
	int come;//������ͳ��
	int waittall;//�ȴ�����ʱ��
	map<int, int> modm;//ƥ��ÿ��ģʽ��Ҫ��ʱ��
	int maxtime;//ʣ�µĹ���ʱ���ܳ���
	queue<T> line;//�ܶ���
	int counter;//�뿪���˵ļ�����
	int alltime;//����ʱ���ܳ���
public:
	//�������
	~Bank() {
		delete[] window;
	}
	Bank( int xtime,int mods) {
		window = new Window[5];
		//��ż����ù���ʱ��
		for (int t = 0; t < 5; t++) {
			window[t].setnum(t + 1);
			window[t].setw(xtime);
		}
		alltime = xtime;
		waittall = 0;
		come = 0;
		counter = 0;
		maxtime = xtime;
		//ƥ����ֵ�ģʽ
		for (int t = 0; t < mods; t++) {
			int time;
			cout << "the " << t << " mods need (mins):" << endl;
			cin >> time;
			modm[t] = time / 5;
		}
	}
	//���ӵȴ�ʱ��
	void setwait(int t) {
		waittall += t;
	}
	//���ش�������
	int getcounter() { return counter; }
	//�����ܵȴ�ʱ��
	int getwait() { return waittall; }
	//���ض��г���
	int size() {
		return line.size();
	}
	//������ǰ��Ĺ˿�
	T front() {
		return line.front();
	}
	//�˿��뿪����
	void pop(int t) {
		counter++;
		waittall = waittall +alltime-maxtime- window[t].getg().in;
		cout << "a person left" << endl;
	}
	int work() {
		int flag = 0;//�ж��Ƿ����еĴ��ڿ���
		for (int t = 0; t < 5; t++) {
			if (window[t].wwork() != 0)flag = 1;//�Ƚ��й������ı䴰��״̬
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
	//-1���� ����1 ����һ���� ����2 �������� ����3 ����������ʱ�����
	//���˽�������
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