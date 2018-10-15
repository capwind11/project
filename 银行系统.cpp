#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;
int seed;  //�������
enum Window_status{busy,available}; //����״̬
double uniform() //ƽ���ֲ�
{
    double t;
    seed = (2045*(seed)+15)%1048576;
    t=(seed)/1048576.0;
    return(t);
}
int poisson(double lambda)  //���ɷֲ�
{
    int i,x;
    double a,b,u;
    a = exp(-lambda);
    i = 0;
    b = 1.0;
    do{
        u=uniform();
        b*=u;
        i++;
    }while(b>=a);
    x = i-1;
    return x;
}

class Customer //ģ��˿���
{
private:
    int cus_num;//�˿ͱ��
    int arrive_time; //����ʱ��
    int serving_time; //�ù˿��������ʱ��
public:
    Customer()
    {
    }
    Customer(int n,int current_time,int time)
    {
        cus_num = n;
        arrive_time = current_time;
        serving_time = time;
    }
    int getnum()//�õ��˿ͱ��
    {
        return cus_num;
    }
    int get_servetime()
    {
        return serving_time;
    }
    int waiting_time(int current_time)
    {
        return current_time-arrive_time;
    }
};
class Window
{
private:
    int serve_num; //����˿�����
    int cus_num; //��ǰ����˿ͱ��
    Window_status status; //����״̬
    int serving_time,start_time; //����ķ���ʱ��
    int Win_num;//���ڱ��
public:
    Window()
    {
        serve_num = 0;
        cus_num = -1;
        serving_time = start_time = 0;
        status = available;
    }
    Window(int n)
    {
        serve_num = 0;
        serving_time = start_time = 0;
        Win_num = n;
        status = available;
    }
    int get_winnum()
    {
        return Win_num;
    }
    void set_winnum(int n)
    {
        Win_num = n;
    }
    void show()//��ʾ��ǰ���ڷ���˿ͱ��
    {
        if (cus_num==-1)
            cout << Win_num+1 << "�Ŵ��ڿ���"<<endl;
        else
        cout << Win_num+1 << "�Ŵ������ڷ���"<<cus_num+1<<"�Ź˿�"<<endl;
    }
    int get_serve_num() //�õ������ܹ˿���
    {
        return serve_num;
    }
    void serve(Customer cus,int current_time)//�����ͷ�˿ͣ������˿ͱ�ź��������ʱ�����Ϣ����
    {
        serving_time = cus.get_servetime();
        start_time = current_time;
        status = busy;
        cus_num = cus.getnum();
        serve_num++;
    }
    Window_status is_available(int current_time)//��ⴰ��״̬
    {
        if(current_time-start_time>=serving_time)//��ǰһ�˿��Ѿ��������
        {
            status = available;//״̬����Ϊ����
            cus_num=-1;
        }
        else
            status = busy;
        return status;
    }
};

class System
{
private:
    queue<Customer> q;//һ������
    Window win[5];//�������
    int total_wait_time;//�˿��ܹ��ȴ�ʱ��
public:
    System()
    {
        total_wait_time = 0;
        for(int i=0;i<5;i++)
        {
            win[i].set_winnum(i);
        }
    }
    void line(Customer c)//�������Ĺ˿������β
    {
        q.push(c);
    }
    int size()//���ض��г���
    {
        return q.size();
    }
    void serve(int current_time)//���´���״̬������˿͸�����
    {
        for(int i=0;i<5;i++){
            if(win[i].is_available(current_time)==available&&!q.empty())//�����ִ��ڿ���ʱ�����Ź˿�
            {
                cout << q.front().getnum()+1<<"�Ź˿�"<<"�ȴ���"<<q.front().waiting_time(current_time)<<"���Ӻ�õ���"<<i+1<<"�Ŵ��ڵķ���"<<endl;
                win[i].serve(q.front(),current_time);
                total_wait_time += q.front().waiting_time(current_time);
                q.pop();//�˿��뿪����
            }
        }
        cout << "��ʱ��"<<q.size() << "λ�˿��ڵȴ�"<<endl;

    }
    void show()//��ʾÿ�����ڷ���Ĺ˿�
    {
        for(int i =0;i<5;i++)
        {
            win[i].show();
        }
    }
    void close()//���йرգ���ʾ����Ӫҵ�ĸ�����Ϣ
    {
        int cus_num=0;
        for(int i=0;i<5;i++)
        {
            cout << i+1<<"�Ŵ����ܹ�������"<<win[i].get_serve_num()<<"λ�˿�"<<endl;
            cus_num+=win[i].get_serve_num();
        }
        cout <<"�˾��ȴ�ʱ��Ϊ"<<((double)total_wait_time)/cus_num<<"����"<<endl;
    }
    bool empty() //�ж϶����Ƿ�Ϊ��
    {
        return q.empty();
    }
};

void initialize(int &end_time,double &arrive_rate,double &solve_time_rate)
{
    cout << "���������й���ʱ�䳤��(����)"<<endl;
    cin >> end_time;
    cout <<"������ÿ���ӿ��ܹ��ٹ˿͵���Ŀ"<<endl;
    cin >> arrive_rate;
    cout << "������ÿλ�˿Ͱ���ҵ���������ʱ��(����)"<<endl;
    cin >> solve_time_rate;
    cout << endl;
}

int main()
{
    int end_time; //Ӫҵ��ʱ��
    int cus_num = 0;
    double arrive_rate,solve_time_rate; //ÿ���ӵ���˿�����ֵ�ͷ�������ʱ������ֵ
    srand((unsigned)time(NULL));
	seed = rand();//��ʱ�䳣�������������
    initialize(end_time,arrive_rate,solve_time_rate);
    System bank;
    for(int current_time = 0;current_time < end_time;current_time++){
        cout <<"��"<<current_time+1<<"����:"<<endl;
        int number_arrivals = poisson(arrive_rate); //�õ����ϲ��ɷֲ��Ĺ˿���
        cout << "��"<<number_arrivals << " λ�¹˿͵���"<<endl;
        for(int i = 0;i < number_arrivals;i++){
            int time = poisson(solve_time_rate);
            Customer current_cus(cus_num++,current_time,time);//��ʼ���˿�
            bank.line(current_cus);
            }
        bank.serve(current_time);
        cout << "���ڷ���״̬:"<<endl;
        bank.show();
        cout << endl;
    }
    int delay_time = end_time;
    cout << "����Ӫҵʱ���ѵ�"<< endl;
    cout << "---------------------------------------------" <<endl;
    bank.close();
    cout << endl;
    if(bank.empty())
    {
        cout << "�ѷ��������й˿ͣ����йر�" <<endl;
        return 0;
    }
    cout << "��ʱ�����л���"<< bank.size()<<"���˿�δ�õ�����"<<endl;
    cout <<"��Ҫ��������������й˿�"<<endl;
    while(!bank.empty())//������Ӫҵʱ����������������ڶ����еĹ˿�
    {
        cout << "��" <<delay_time+1<<"����:"<<endl;
        bank.serve(delay_time);
        bank.show();
        delay_time++;
    }
    cout << endl;
    cout << "---------------------------------------------"<<endl;
    cout << "���й˿ͷ��������Ҫʱ��Ϊ" << delay_time << "����"<< endl;
    cout <<"������Ӫҵʱ�䳬����" <<delay_time - end_time <<"����"<<endl;
    bank.close();
}
