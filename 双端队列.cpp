class double_end_queue()
{
private:
    int front; //��¼��ͷǰһλ�õ��±�
    int rear; //��¼��βλ��
    int maxsize; //�û��ζ��������ɵ���󳤶ȣ���������һ��λ�������ֶ��пպ�����״̬
    ElemType *data;
public:
    double_end_queue();                               //���캯��
    ~double_end_queue();
    void initial(); //���³�ʼ��
    bool isempty() const;
    bool isfull() const;
    bool get_front(ElemType &e) const; //�õ���ͷ����
    bool get_rear(ElemType &e) const; //�õ���β����
    bool enqueue_front(const ElemType &e);//�Ӷ�ͷ��ջ
    bool dequeue_front(ElemType &e);//�Ӷ�ͷ��ջ
    bool enqueue_rear(const ElemType &e);//�Ӷ�β��ջ
    bool dequeue_rear(ElemType &e);//�Ӷ�β��ջ
    int size() const;//���������Ԫ�ظ���
};

���캯����
double_end_queue::double_end_queue()
{
    front = rear = 0;
    maxsize = 10; //Ĭ����󳤶�Ϊ10
    data = new ElemType[maxsize];
}

double_end_queue::double_end_queue(int sz)
{
    maxsize = sz; //���Զ�����󳤶ȸ�ֵ��maxsize
    front = rear = 0;
    data = new ElemType[maxsize];
}


�ж��Ƿ�Ϊ�գ�
bool double_end_queue::is_empty()
{
    return (front == rear);//����ͷ�Ͷ�β��ʶ���ʱ����Ϊ��
}

front��ӣ�
bool double_end_queue::enqueue_front(const ElemType &e)
{
    if((rear+1)%maxsize == front) //����β�ȶ�ͷ��ʶ���һ��λ��ʱ����������
        return false;
    data[front] = e; //�Ѵ������ݸ�ֵ����ͷ��ʶλ��
    front = (maxsize+front -1)%maxsize; //��ͷ��ʶ����һλ
    return true;
}

front���ӣ�
bool double_end_queue::dequeue_front(ElemType &e)
{
    if(rear == front) //����β�Ͷ�ͷ��ʶ���ʱ������Ϊ��
        return false;
    front = (front+1)%maxsize;
    e = data[front];
    return true;
}
