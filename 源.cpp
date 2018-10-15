#include<iostream>
#include<queue>
#include<math.h>
#include<map>
#include<limits>
#include<climits>
#include<limits.h>
#include<time.h>
#include <stdlib.h>
#include"class.h"
//559 ��¼ 84 �ο�����
//����0��1�ľ��ȷֲ�
double random_real() {
	double f;
	srand((unsigned)time(NULL));//�������
	f = (float)(rand() % 100);//���������
	return f / 100;
}
int poisson(double mean) {
	double l = exp(-mean);
	double p = random_real();
	int count = 0;
	while (p >= l) {
		count++;
		p *= random_real();
	}
	return count-1;
}
//����ʱ��ת����ʱ�䵥Ԫ��
int changetime(int a1, int a2, int b1, int b2) {
	int c1 = b1 - a1,c2;
	if (b2 - a2 < 0) {
		c1--;
		c2 = 60 - (b2 - a2);
	}
	else c2 = b2 - a2;
	return (c1 * 60 + c2) / 5;
}
int main() {
	int st1,st2,mods;
	int end1, end2, now = 0;
	char a;
	cout << "please input the start time (24 hours����ȷ������):" << endl;
	cin >> st1>>a>>st2;
	cout << "please input the end time (24 hours����ȷ������):" << endl;
	cin >> end1 >> a >> end2;
	cout << "enter the number of mods:" << endl;
	cin >> mods;
	int worktime = changetime(st1, st2, end1, end2);
	Bank<person> bank( worktime ,mods);
	for (int t = 1; t <= worktime; t++) {
		int numarrive = poisson(0.3);//ÿ��ʱ�䵥Ԫ�����ƽ���˿���
		//������ʱ�˿Ͷ���
		for (int g = 0; g < numarrive; g++) {
			person test;
			test.in = t;
			test.mod = rand() % mods;
			bank.enter(test);
		}
		int statue = bank.work();
		if (statue == 3)break;
	}
	if (bank.getcounter() == 0) {
		cout << "nobody come" << endl;
		return 0;
	}
	double waitav = bank.getwait() / double(bank.getcounter())*5;
	cout << "people come:" << bank.getcome() << endl;
	cout << "average waiting time:" << waitav <<" mins"<< endl;
	cout << "people left in the line:" << bank.size() << endl;
	cout << "the number of people deal with:" << bank.getcounter() << endl;
	return 0;
}
