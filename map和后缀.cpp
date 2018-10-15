#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <iomanip>
#include<stdio.h>
using namespace std;
double eval(string e, map<char,double> f)
{
    stack<double> s;
    double t;
    for(int i = 0; i < e.length();i++){
        if(e[i]<='z'&&e[i]>='a')
            s.push(f[e[i]]);
        else if(e[i]=='-'||e[i]=='+'||e[i]=='/'||e[i]=='*'){
            if(e[i]=='-'){
                t = s.top();
                s.pop();
                t = s.top()-t;
                s.pop();
                s.push(t);
            }
            if(e[i]=='+'){
                t = s.top();
                s.pop();
                t = t+s.top();
                s.pop();
                s.push(t);
            }
            if(e[i]=='/'){
                t = s.top();
                s.pop();
                t = s.top()/t;
                s.pop();
                s.push(t);
            }
            if(e[i]=='*'){
                t = s.top();
                s.pop();
                t = t*s.top();
                s.pop();
                s.push(t);
            }
        }
    }
    return s.top();
}


    int main()
{
    int m;
    cin >> m;
    string e;
    map<char,double> f;
    f['a'] = 1.0;
    f['b'] = 3;
    f['c'] = 2;
    f['x'] = 1;
    for(int i = 0;i<m;i++){
    		getchar();
            getline(cin,e);
            cout << fixed<< setprecision(1)<< eval(e,f);
    }

}


