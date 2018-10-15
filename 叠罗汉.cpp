#include <iostream>
#include <stack>
using namespace std;
int down(stack<int> &a,int n,int h)
{
    int t=0;
    while(a.top()!=n){
        a.pop();
        t += (h-1);
        h--;
    }
    t +=(h-1);
    return t;
}

int climb(stack<int> &a,int m)
{
    int o,h=0;
    for(int i = 0;i < m;i++)
    {
        cin >> o;
        if(o!=-1)
            {
                h++;
                a.push(o);}
        else
            {
                h--;
                a.pop();
            }
    }
    return h;
}
int main()
{
    int t,N,M,X,h;
    stack<int> a;
    cin >> t;
    for(int i = 0;i < t;i++){
        cin >> N >> M >> X;
        h = climb(a,M);
        if (X < down(a,N,h))
            cout << "NO" << endl;
        else
            cout << "YES" << endl;

        }
}
