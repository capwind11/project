#include <iostream>
#include <stack>
#include <string>
using namespace std;
void resort(string a,stack<char> &s)
{
    int i = 0;
    while (i<a.length()){
        if((a[i]<='Z'&&a[i]>='A')||(a[i]<='z'&&a[i]>='a')){
            cout << a[i];
            i++;
        }
        else if(a[i]=='+'||a[i]=='-'){
            if(!s.empty())
                if(s.top()=='+'||s.top()=='-')
                {
                    cout << s.top();
                    s.pop();
                }
               s.push(a[i]);
               i++;
        }
        else{
            s.push(a[i]);
            i++;
            cout << a[i];
            cout << s.top();
            s.pop();
            i++;

        }
    }
    while(!s.empty())
        {cout << s.top();
        s.pop();}
}
int main()
{
    string a;
    cin >> a;
    stack<char> s;
    resort(a,s);
}
