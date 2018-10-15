class double_end_queue()
{
private:
    int front; //记录队头前一位置的下标
    int rear; //记录队尾位置
    int maxsize; //该环形队列能容纳的最大长度，不过牺牲一个位置来区分队列空和满的状态
    ElemType *data;
public:
    double_end_queue();                               //构造函数
    ~double_end_queue();
    void initial(); //重新初始化
    bool isempty() const;
    bool isfull() const;
    bool get_front(ElemType &e) const; //得到队头的数
    bool get_rear(ElemType &e) const; //得到队尾的数
    bool enqueue_front(const ElemType &e);//从队头进栈
    bool dequeue_front(ElemType &e);//从队头出栈
    bool enqueue_rear(const ElemType &e);//从队尾进栈
    bool dequeue_rear(ElemType &e);//从队尾出栈
    int size() const;//计算队列中元素个数
};

构造函数：
double_end_queue::double_end_queue()
{
    front = rear = 0;
    maxsize = 10; //默认最大长度为10
    data = new ElemType[maxsize];
}

double_end_queue::double_end_queue(int sz)
{
    maxsize = sz; //将自定义最大长度赋值给maxsize
    front = rear = 0;
    data = new ElemType[maxsize];
}


判断是否为空：
bool double_end_queue::is_empty()
{
    return (front == rear);//当队头和队尾标识相等时队列为空
}

front入队：
bool double_end_queue::enqueue_front(const ElemType &e)
{
    if((rear+1)%maxsize == front) //当队尾比队头标识落后一个位置时，队列已满
        return false;
    data[front] = e; //把传入数据赋值给队头标识位置
    front = (maxsize+front -1)%maxsize; //队头标识后退一位
    return true;
}

front出队：
bool double_end_queue::dequeue_front(ElemType &e)
{
    if(rear == front) //当队尾和队头标识相等时，队列为空
        return false;
    front = (front+1)%maxsize;
    e = data[front];
    return true;
}
