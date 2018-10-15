class MyStack：public double_end_queue
{
public:
    Mystack():double_end_queue()//
    {
    }
    bool push(const ElemType &e)
    {
        return enqueue_rear(e);//直接调用从队尾入队方法
    }
    bool pop(ElemType &e)
    {
        return dequeue_rear(e);//直接调用从队尾出队操作
    }
    bool top(ElemType &e) const
    {
        return get_rear(e);//直接调用获取队尾元素
    }
    //size(),is_empty(),is_full()等操作可不定义，直接使用双端队列的同名方法
};
