#include <iostream>
#include <stack>
using namespace std;
bool cou(int n)
{
    stack<int> s;
    int *t = new int[2*n];
    int p1,p2;
    for(int i = 0;i<n;i++){
        cin >> p1;
        cin >> p2;
        t[p1-1]=i;
        t[p2-1]=i;
    }
    s.push(t[0]);
    for(int i = 1;i<2*n;i++){
        if((!s.empty())&&s.top()==t[i])
           s.pop();
        else s.push(t[i]);
    }
    if(s.empty())
        return true;
    else return false;

}

int main()
{
    int n,m;
    cin >> n;
    for(int i = 0;i<n;i++){
        cin >> m;
        if(cou(m))
            cout << "Yes"<<endl;
        else
        cout << "No"<<endl;
    }
}
