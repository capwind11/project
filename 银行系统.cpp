#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;
int seed;  //随机种子
enum Window_status{busy,available}; //窗口状态
double uniform() //平均分布
{
    double t;
    seed = (2045*(seed)+15)%1048576;
    t=(seed)/1048576.0;
    return(t);
}
int poisson(double lambda)  //泊松分布
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

class Customer //模拟顾客类
{
private:
    int cus_num;//顾客编号
    int arrive_time; //到达时间
    int serving_time; //该顾客所需服务时间
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
    int getnum()//得到顾客编号
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
    int serve_num; //服务顾客总数
    int cus_num; //当前服务顾客编号
    Window_status status; //窗口状态
    int serving_time,start_time; //随机的服务时间
    int Win_num;//窗口编号
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
    void show()//显示当前窗口服务顾客编号
    {
        if (cus_num==-1)
            cout << Win_num+1 << "号窗口空闲"<<endl;
        else
        cout << Win_num+1 << "号窗口正在服务"<<cus_num+1<<"号顾客"<<endl;
    }
    int get_serve_num() //得到服务总顾客数
    {
        return serve_num;
    }
    void serve(Customer cus,int current_time)//服务队头顾客，并将顾客编号和所需服务时间等信息载入
    {
        serving_time = cus.get_servetime();
        start_time = current_time;
        status = busy;
        cus_num = cus.getnum();
        serve_num++;
    }
    Window_status is_available(int current_time)//检测窗口状态
    {
        if(current_time-start_time>=serving_time)//若前一顾客已经服务完毕
        {
            status = available;//状态设置为空闲
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
    queue<Customer> q;//一条队列
    Window win[5];//五个窗口
    int total_wait_time;//顾客总共等待时间
public:
    System()
    {
        total_wait_time = 0;
        for(int i=0;i<5;i++)
        {
            win[i].set_winnum(i);
        }
    }
    void line(Customer c)//将新来的顾客排入队尾
    {
        q.push(c);
    }
    int size()//返回队列长度
    {
        return q.size();
    }
    void serve(int current_time)//更新窗口状态并分配顾客给窗口
    {
        for(int i=0;i<5;i++){
            if(win[i].is_available(current_time)==available&&!q.empty())//当出现窗口空闲时，安排顾客
            {
                cout << q.front().getnum()+1<<"号顾客"<<"等待了"<<q.front().waiting_time(current_time)<<"分钟后得到了"<<i+1<<"号窗口的服务"<<endl;
                win[i].serve(q.front(),current_time);
                total_wait_time += q.front().waiting_time(current_time);
                q.pop();//顾客离开队列
            }
        }
        cout << "此时有"<<q.size() << "位顾客在等待"<<endl;

    }
    void show()//显示每个窗口服务的顾客
    {
        for(int i =0;i<5;i++)
        {
            win[i].show();
        }
    }
    void close()//银行关闭，显示今天营业的各种信息
    {
        int cus_num=0;
        for(int i=0;i<5;i++)
        {
            cout << i+1<<"号窗口总共服务了"<<win[i].get_serve_num()<<"位顾客"<<endl;
            cus_num+=win[i].get_serve_num();
        }
        cout <<"人均等待时间为"<<((double)total_wait_time)/cus_num<<"分钟"<<endl;
    }
    bool empty() //判断队列是否为空
    {
        return q.empty();
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
    cout << endl;
}

int main()
{
    int end_time; //营业总时长
    int cus_num = 0;
    double arrive_rate,solve_time_rate; //每分钟到达顾客期望值和服务所需时间期望值
    srand((unsigned)time(NULL));
	seed = rand();//用时间常数设置随机种子
    initialize(end_time,arrive_rate,solve_time_rate);
    System bank;
    for(int current_time = 0;current_time < end_time;current_time++){
        cout <<"第"<<current_time+1<<"分钟:"<<endl;
        int number_arrivals = poisson(arrive_rate); //得到符合泊松分布的顾客数
        cout << "有"<<number_arrivals << " 位新顾客到来"<<endl;
        for(int i = 0;i < number_arrivals;i++){
            int time = poisson(solve_time_rate);
            Customer current_cus(cus_num++,current_time,time);//初始化顾客
            bank.line(current_cus);
            }
        bank.serve(current_time);
        cout << "窗口服务状态:"<<endl;
        bank.show();
        cout << endl;
    }
    int delay_time = end_time;
    cout << "正常营业时间已到"<< endl;
    cout << "---------------------------------------------" <<endl;
    bank.close();
    cout << endl;
    if(bank.empty())
    {
        cout << "已服务完所有顾客，银行关闭" <<endl;
        return 0;
    }
    cout << "此时队伍中还有"<< bank.size()<<"名顾客未得到服务"<<endl;
    cout <<"若要继续服务完队伍中顾客"<<endl;
    while(!bank.empty())//在正常营业时间外继续服务完已在队伍中的顾客
    {
        cout << "第" <<delay_time+1<<"分钟:"<<endl;
        bank.serve(delay_time);
        bank.show();
        delay_time++;
    }
    cout << endl;
    cout << "---------------------------------------------"<<endl;
    cout << "所有顾客服务完毕需要时间为" << delay_time << "分钟"<< endl;
    cout <<"比正常营业时间超出了" <<delay_time - end_time <<"分钟"<<endl;
    bank.close();
}
