#include <iostream>
#include <queue>
using namespace std;
void Throw(int n)
{
    int t;
    queue<int> q;
    for(int i = 0;i<n;i++)
    {
        q.push(i+1);
    }
    while(q.size()!=1)
    {
        cout << q.front() << ' ';
        q.pop();
        t = q.front();
        q.pop();
        q.push(t);
    }
    cout << q.front()<<' '<< endl;
}

int main()
{
    int n,m;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> m;
        Throw(m);
    }
}
