
typedef int Stack_entry;

class Stack {
  public:
    Stack_entry data[250];
    int sz;
   // Standard Stack methods
    Stack()
    {
        sz = 0;
    }
    bool empty() const
    {
        return (sz==0);
    }
     /* Returns true if the stack is empty, otherwise, returns false.
    */
    int size() const
    {
        return sz;
    }
    /* Returns the number of elements in the stack.
    */
    void push(const Stack_entry &item)
    {
        data[sz]=item;
        sz++;
    }
    /*item is pushed into the stack and it becomes the new top element.
     */
     void pop()
     {
         if(sz==0)
            return;
         sz--;
     }
     /*The top item is removed if the stack is not empty.
     Otherwise, nothing happens.
     */

    const Stack_entry & top() const
    {
        if(sz==0)
            return -1;
        return data[sz-1];
    }
    /* The top element is returned by item if the stack is not empty,
    and the stack remains unchanged.
    Nothing happens if the stack is empty.
   */
     // Safety features
    ~Stack()
    {
    }
    Stack(const Stack &original)
    {
        *this = original;
    }
    void operator =(const Stack &original)
    {
        sz = original.sz;
        for(int i=0;i<sz;i++){
                data[i] = original.data[i];
        }
    }
};


typedef Stack MyStack;

#include <iostream>
using namespace std;
int main()
{
    Stack s1,s2;
    s1.push(3);
    s1.push(4);
    s1.push(4);
    s1.push(4);
    s1.push(4);
    s1.push(3);
    s2 = s1;
    cout << s1.size() << s1.top();
    cout << s2.size() << s2.top();
}

//or if your are using templates

//typedef Stack<int> MyStack;
