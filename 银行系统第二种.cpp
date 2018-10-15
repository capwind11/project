#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int seed;//�������
enum Window_status{busy,available};//����״̬
double uniform()//��������ֲ�
{
    double t;
    seed = (2045*(seed)+15)%1048576;
    t=(seed)/1048576.0;
    return(t);
}
int poisson(double lambda)//���ɷֲ�
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

class Customer //ģ��˿͵ĳ�����
{
private:
    int cus_num;//���
    int arrive_time;//����ʱ��
    int serving_time;//�������ʱ��
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
    int get_serving_time()
    {
        return serving_time;
    }
    int getnum()//�õ��˿ͱ��
    {
        return cus_num;
    }
    int waiting_time(int current_time) //����õ�����ǰ�ȴ���ʱ��
    {
        return current_time-arrive_time;
    }
};
class Window
{
private:
    int cus_num; //��ǰ����Ĺ˿ͱ��
    int wait_time; //�ô��ڶ����ܹ��ȴ�ʱ��
    int serve_num; //�ܹ�����Ĺ˿���
    queue<Customer> q; //�ô���ǰ�Ķ�
    Window_status status; //����״̬
    int serving_time,start_time; //����ķ���ʱ��
    int Win_num;//���ڱ��
public:

    Window()
    {
        cus_num = -1;
        wait_time = 0;
        serve_num = 0;
        serving_time = start_time = 0;
        status = available;
    }
    Window(int n)
    {
        cus_num = -1;
        wait_time = 0;
        serve_num = 0;
        serving_time = start_time = 0;
        Win_num = n;
        status = available;
    }
    int getwaittime()//�õ��ܵĵȴ�ʱ��
    {
        return wait_time;
    }
    void setwinnum(int n)
    {
        Win_num = n;
    }
    int getwinnum()//�õ����ڱ��
    {
        return Win_num;
    }
    Window_status sit()//���ش���״̬
    {
        return status;
    }
    int get_serve_num()//�õ��ô����ܷ���˿���
    {
        return serve_num;
    }
    void serve(Customer cus,int current_time)//����ǰ�˿�
    {
        cus_num = cus.getnum();
        serving_time = cus.get_serving_time();
        start_time = current_time;
        status = busy;
        serve_num++;
    }
    void show()//��ʾ�����ܵ�����Ĺ˿�
    {
        if (cus_num==-1)
            cout << Win_num+1 << "�Ŵ��ڿ���"<<endl;
        else
        cout << Win_num+1 << "�Ŵ������ڷ���"<<cus_num+1<<"�Ź˿�"<<endl;
    }
        void update(int current_time)//���´���״̬�������ڷ��乤��
    {
            if(is_available(current_time)==available&&!q.empty())
            {
                cout << q.front().getnum()+1<<"�Ź˿�"<<"�ȴ���"<<q.front().waiting_time(current_time)<<"���Ӻ�õ���"<<Win_num+1<<"�Ŵ��ڵķ���"<<endl;
                serve(q.front(),current_time);
                wait_time += q.front().waiting_time(current_time);
                q.pop();
            }
        cout << "��ʱ"<<Win_num+1<<"�Ŵ�����"<<q.size() << "λ�˿��ڵȴ�"<<endl;

    }
    void push(Customer c)//���˿����������
    {
        q.push(c);
    }
    int size()//���ش���ǰ���鳤��
    {
        return q.size();
    }
    Window_status is_available(int current_time)
    {
        if(current_time-start_time>=serving_time)
        {
            status = available;
            cus_num = -1;
        }
        else
            status = busy;
        return status;
    }
    bool empty()//���ش���ǰ�����Ƿ��еȴ��˿�
    {
        return q.empty();
    }
};

class System//ģ��ϵͳ
{
private:
    Window win[5];//�������
    int total_wait_time;//�ܹ��ȴ�ʱ��
public:
    System()
    {
        total_wait_time = 0;
        for(int i=0;i<5;i++)
        {
            win[i].setwinnum(i);
        }
    }
    void show() //��ʾÿ�����ڷ���Ĺ˿ͱ��
    {
        for(int i =0;i<5;i++)
        {
            win[i].show();
        }
    }

    int pick() //�Զ��г��Ƚ������򲢷�����̶��еı��
    {
        int target = 0;
        for(int i=0;i<4;i++)
        {
            if(win[i].size()>win[i+1].size()||(win[i].sit()==busy&&win[i+1].sit()==available))
                    target = i+1;
            }
        return target;
    }

    void line(Customer c)//��һ���˿Ͱ��Ž���������֮һ
    {
        int t = pick();
        win[t].push(c);
    }
    void serve(int current_time)//����ÿ�����ڵĹ���
    {
        int size=0;
        for(int i=0;i<5;i++){
            win[i].update(current_time);
            size+=win[i].size();
        }
        cout <<"��ʱһ����"<<size<< "λ�˿��ڵȴ�"<<endl;

    }
    void close()//���йرղ��õ�Ӫҵ״��
    {
        int cus_num=0;
        for(int i=0;i<5;i++)
        {
            cout << i+1<<"�Ŵ����ܹ�������"<<win[i].get_serve_num()<<endl;
            cus_num+=win[i].get_serve_num();
            total_wait_time+=win[i].getwaittime();
        }
        cout <<"�˾��ȴ�ʱ��"<<total_wait_time*1.0/cus_num<<endl;
    }
    bool empty()//�����Ƿ��й˿�
    {
        for(int i=0;i<5;i++)
            if(!win[i].empty())
            return false;
        return true;
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
}

int main()
{
    int end_time;
    int cus_num = 0;
    double arrive_rate,solve_time_rate;
    srand((unsigned)time(NULL));
	seed = rand();//����ʱ�䳣����������ӵó�ʱ�䳣��
    initialize(end_time,arrive_rate,solve_time_rate);
    System bank;
    for(int current_time = 0;current_time < end_time;current_time++){
        cout <<"��"<<current_time+1<<"����:"<<endl;
        int number_arrivals = poisson(arrive_rate);//���ɷֲ��õ��˿���
        cout << "��"<<number_arrivals << " λ�¹˿͵���"<<endl;
        for(int i = 0;i < number_arrivals;i++){
            int time = poisson(solve_time_rate);
            Customer current_cus(cus_num++,current_time,time);//��ʼ���˿���Ϣ
            bank.line(current_cus);
            }
        bank.serve(current_time);
        cout << endl;
    }
    int delay_time = end_time;
    cout << endl;
    cout << "����Ӫҵʱ���ѵ�"<< endl;
    bank.close();
    cout << "---------------------------------------------" <<endl;
    if(bank.empty())
    {
        cout << "�ѷ��������й˿ͣ����йر�" <<endl;
        return 0;
    }
    cout <<"��Ҫ��������������й˿�"<<endl;
    while(!bank.empty())
    {
        cout << "��" <<delay_time+1<<"����:"<<endl;
        bank.serve(delay_time);
        delay_time++;
    }
    cout << endl;
    cout << "---------------------------------------------"<<endl;
    cout << "���й˿ͷ��������Ҫʱ��Ϊ" << delay_time << "����"<< endl;
    cout <<"������Ӫҵʱ�䳬����" <<delay_time - end_time <<"����"<<endl;
    bank.close();
}
