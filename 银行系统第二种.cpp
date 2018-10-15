#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int seed;//随机种子
enum Window_status{busy,available};//窗口状态
double uniform()//均匀随机分布
{
    double t;
    seed = (2045*(seed)+15)%1048576;
    t=(seed)/1048576.0;
    return(t);
}
int poisson(double lambda)//泊松分布
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

class Customer //模拟顾客的抽象类
{
private:
    int cus_num;//编号
    int arrive_time;//到达时间
    int serving_time;//所需服务时间
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
    int getnum()//得到顾客编号
    {
        return cus_num;
    }
    int waiting_time(int current_time) //计算得到服务前等待的时间
    {
        return current_time-arrive_time;
    }
};
class Window
{
private:
    int cus_num; //当前服务的顾客编号
    int wait_time; //该窗口队列总共等待时间
    int serve_num; //总共服务的顾客数
    queue<Customer> q; //该窗口前的队
    Window_status status; //窗口状态
    int serving_time,start_time; //随机的服务时间
    int Win_num;//窗口编号
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
    int getwaittime()//得到总的等待时间
    {
        return wait_time;
    }
    void setwinnum(int n)
    {
        Win_num = n;
    }
    int getwinnum()//得到窗口编号
    {
        return Win_num;
    }
    Window_status sit()//返回窗口状态
    {
        return status;
    }
    int get_serve_num()//得到该窗口总服务顾客数
    {
        return serve_num;
    }
    void serve(Customer cus,int current_time)//服务当前顾客
    {
        cus_num = cus.getnum();
        serving_time = cus.get_serving_time();
        start_time = current_time;
        status = busy;
        serve_num++;
    }
    void show()//显示正在受到服务的顾客
    {
        if (cus_num==-1)
            cout << Win_num+1 << "号窗口空闲"<<endl;
        else
        cout << Win_num+1 << "号窗口正在服务"<<cus_num+1<<"号顾客"<<endl;
    }
        void update(int current_time)//更新窗口状态并给窗口分配工作
    {
            if(is_available(current_time)==available&&!q.empty())
            {
                cout << q.front().getnum()+1<<"号顾客"<<"等待了"<<q.front().waiting_time(current_time)<<"分钟后得到了"<<Win_num+1<<"号窗口的服务"<<endl;
                serve(q.front(),current_time);
                wait_time += q.front().waiting_time(current_time);
                q.pop();
            }
        cout << "此时"<<Win_num+1<<"号窗口有"<<q.size() << "位顾客在等待"<<endl;

    }
    void push(Customer c)//将顾客排入队伍中
    {
        q.push(c);
    }
    int size()//返回窗口前队伍长度
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
    bool empty()//返回窗口前队伍是否还有等待顾客
    {
        return q.empty();
    }
};

class System//模拟系统
{
private:
    Window win[5];//五个窗口
    int total_wait_time;//总共等待时长
public:
    System()
    {
        total_wait_time = 0;
        for(int i=0;i<5;i++)
        {
            win[i].setwinnum(i);
        }
    }
    void show() //显示每个窗口服务的顾客编号
    {
        for(int i =0;i<5;i++)
        {
            win[i].show();
        }
    }

    int pick() //对队列长度进行排序并返回最短队列的编号
    {
        int target = 0;
        for(int i=0;i<4;i++)
        {
            if(win[i].size()>win[i+1].size()||(win[i].sit()==busy&&win[i+1].sit()==available))
                    target = i+1;
            }
        return target;
    }

    void line(Customer c)//将一个顾客安排进五条队伍之一
    {
        int t = pick();
        win[t].push(c);
    }
    void serve(int current_time)//安排每个窗口的工作
    {
        int size=0;
        for(int i=0;i<5;i++){
            win[i].update(current_time);
            size+=win[i].size();
        }
        cout <<"此时一共有"<<size<< "位顾客在等待"<<endl;

    }
    void close()//银行关闭并得到营业状况
    {
        int cus_num=0;
        for(int i=0;i<5;i++)
        {
            cout << i+1<<"号窗口总共服务了"<<win[i].get_serve_num()<<endl;
            cus_num+=win[i].get_serve_num();
            total_wait_time+=win[i].getwaittime();
        }
        cout <<"人均等待时间"<<total_wait_time*1.0/cus_num<<endl;
    }
    bool empty()//银行是否还有顾客
    {
        for(int i=0;i<5;i++)
            if(!win[i].empty())
            return false;
        return true;
    }
};

void initialize(int &end_time,double &arrive_rate,double &solve_time_rate)
{
    cout << "请输入银行工作时间长度(分钟)"<<endl;
    cin >> end_time;
    cout <<"请输入每分钟可能光临顾客的数目"<<endl;
    cin >> arrive_rate;
    cout << "请输入每位顾客办理业务可能所需时间(分钟)"<<endl;
    cin >> solve_time_rate;
}

int main()
{
    int end_time;
    int cus_num = 0;
    double arrive_rate,solve_time_rate;
    srand((unsigned)time(NULL));
	seed = rand();//利用时间常数作随机种子得出时间常数
    initialize(end_time,arrive_rate,solve_time_rate);
    System bank;
    for(int current_time = 0;current_time < end_time;current_time++){
        cout <<"第"<<current_time+1<<"分钟:"<<endl;
        int number_arrivals = poisson(arrive_rate);//泊松分布得到顾客数
        cout << "有"<<number_arrivals << " 位新顾客到来"<<endl;
        for(int i = 0;i < number_arrivals;i++){
            int time = poisson(solve_time_rate);
            Customer current_cus(cus_num++,current_time,time);//初始化顾客信息
            bank.line(current_cus);
            }
        bank.serve(current_time);
        cout << endl;
    }
    int delay_time = end_time;
    cout << endl;
    cout << "正常营业时间已到"<< endl;
    bank.close();
    cout << "---------------------------------------------" <<endl;
    if(bank.empty())
    {
        cout << "已服务完所有顾客，银行关闭" <<endl;
        return 0;
    }
    cout <<"若要继续服务完队伍中顾客"<<endl;
    while(!bank.empty())
    {
        cout << "第" <<delay_time+1<<"分钟:"<<endl;
        bank.serve(delay_time);
        delay_time++;
    }
    cout << endl;
    cout << "---------------------------------------------"<<endl;
    cout << "所有顾客服务完毕需要时间为" << delay_time << "分钟"<< endl;
    cout <<"比正常营业时间超出了" <<delay_time - end_time <<"分钟"<<endl;
    bank.close();
}
