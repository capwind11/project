#include <iostream>
using namespace std;
struct Node
{
    int n;
    Node* next;
};
class list
{

public:
    Node *head;
    list()
    {
        head = new Node;
        head->next = NULL;
    }
    void insert_front(const int &n)
    {
        Node* t = new Node;
        t->n = n;
        t->next = head;
        head = t;
    }
    void insert_back(const int&n)
    {
        Node* t = new Node;
        t->next = NULL;
        t->n = n;
        Node* p = head;
        while(p->next==NULL)
        {
            p=p->next;
        }
        p->next = t;
    }
    void insert(int m,int n)
    {
        Node* t = new Node;
        Node* p = head;
        for(int i = 0;i<m-1;i++)
        {
            p = p->next;
        }
        t->n = n;
        t->next = p->next;
        p->next = t;
    }
};

class Mystack():public list
{
    void push(const int &e)
    {
        insert_back(e);
    }
    void pop()
    {

    }
    void
};
int main()
{
    list a;
    a.insert_front(1);
    a.insert_back(2);
    a.insert(1,3);
    cout << a.head->n<<endl;
    cout << a.head->next->n<<endl;
    cout << a.head->next->next->n<<endl;
}
