#include <iostream>
#include <stack>
using namespace std;
void trans(string e)
{
    stack<char> s;
    for(int i = 0;i<e.length();i++){
        if((e[i]<='z'&&e[i]>='a')||(e[i]<='Z'&&e[i]>='A')){
           cout << e[i];
           }
        else if(e[i]=='(')
            s.push(e[i]);
        else if(e[i]=='+'||e[i]=='-'){
            while((!s.empty())&&s.top()!='(')
            {
                cout << s.top();
                s.pop();
            }
                s.push(e[i]);
        }
        else if(e[i]=='*'||e[i]=='/'){
            if(s.top()=='/'||s.top()=='*'){
                    cout << s.top();
                    s.pop();
                    s.push(e[i]);
                }
                else if(s.top()=='+'||s.top()=='-'||s.top()==')')
                    s.push(e[i]);
        }
        else if(e[i]==')')
        {
            while(s.top()!='(')
            {
                cout <<s.top();
                s.pop();
            }
            s.pop();
        }


    }
    while(!s.empty()){
        cout << s.top();
        s.pop();
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;
    string a;
    for(int i =0;i<n;i++)
    {
        cin >> a;
        trans(a);
    }

}
