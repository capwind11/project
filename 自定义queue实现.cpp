
template <typename T> class Queue {
public:
     Queue()
     {
         fr = roar = 0;
         sz = 0;
     }   // construct an empty queue
      ~Queue()
      {

      }  // destructor
      Queue(const Queue &rhs)
      {
          sz = rhs.sz;
          fr = rhs.fr;
          roar = rhs.roar;
          for(int i = 0;i<100;i++)
          {
              a[i] = rhs.a[i];
          }
      }
      const Queue & operator = (const Queue &rhs)
      {
          sz = rhs.sz;
          fr = rhs.fr;
          roar = rhs.roar;
          for(int i = 0;i<100;i++)
          {

              a[i] = rhs.a[i];
          }
      }
      bool empty()const
      {
          return (sz==0);
      }
      bool full()const
      {
          return (sz==100);
      }
      int size()const
      {
          return sz;
      }
      bool push(const T &x)
      {
          if(full())
            return false;
          roar = (roar+1)%100;
          a[roar]=x;
          sz++;
          return true;
      }
      //enqueue
      bool pop()
      {
          if(empty())
            return false;
          fr = fr + 1;
          sz = sz - 1;
          return true;
      }//dequeue
      const T & front()const
      {
          return a[fr+1];
      }

private:
    T a[100];
    int fr;
    int roar;
    int sz;
};

#include <iostream>
using namespace std;
int main()
{
    Queue<int> q,p;
    q.push(2);
    q.push(3);
    p = q;
    cout << q.front();
    cout << p.size();
}
