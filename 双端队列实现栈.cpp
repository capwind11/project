class MyStack��public double_end_queue
{
public:
    Mystack():double_end_queue()//
    {
    }
    bool push(const ElemType &e)
    {
        return enqueue_rear(e);//ֱ�ӵ��ôӶ�β��ӷ���
    }
    bool pop(ElemType &e)
    {
        return dequeue_rear(e);//ֱ�ӵ��ôӶ�β���Ӳ���
    }
    bool top(ElemType &e) const
    {
        return get_rear(e);//ֱ�ӵ��û�ȡ��βԪ��
    }
    //size(),is_empty(),is_full()�Ȳ����ɲ����壬ֱ��ʹ��˫�˶��е�ͬ������
};
