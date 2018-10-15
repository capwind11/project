#include <iostream>
#include <stack>
using namespace std;
void rail(int n)
{
    stack<int> s;
    int* d = new int[n];
    while(1)
    {
        for(int i=0;i<n;i++)
        {
            cin >>d[i];

            if(d[i]==0)
            {
                cout << endl;
                return;
            }
        }
        int t = 0;
        for(int i=0;i<n;i++)
        {
            s.push(i+1);
            while((!s.empty())&&(s.top()==d[t])){
                s.pop();
                t++;
            }

        }
        if(s.empty())
            cout <<"Yes";
        else cout <<"No";
        cout << endl;
    }

}

int main()
{
    int n;
    cin >>n;
    while(n!=0)
    {
        rail(n);
        cin >>n;
    }
}
