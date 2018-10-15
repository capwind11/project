#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <iomanip>
#include<stdio.h>
using namespace std;
bool eval(char c,stack<double>& s)
{
    double t;
    if(c=='-'){
                t = s.top();
                s.pop();
                t = s.top()-t;
                s.pop();
                s.push(t);
            }
            if(c=='+'){
                t = s.top();
                s.pop();
                t = t+s.top();
                s.pop();
                s.push(t);
            }
            if(c=='/'){
                t = s.top();
                if(t==0){
                    cout <<"Error"<<endl;
                    return false;
                }
                s.pop();
                t = s.top()/t;
                s.pop();
                s.push(t);
            }
            if(c=='*'){
                t = s.top();
                s.pop();
                t = t*s.top();
                s.pop();
                s.push(t);
            }
            return true;
}
double str2num(int &n,string e)
{
    double d1=0,d2=0,t;
    bool flag = 0;
    int cou = 0;
    while(e[n]=='.'||(e[n]<='9'&&e[n]>='0')){
        if(e[n]=='.')
        {
            flag = 1;
            n++;
        }
        else{
            if(flag == 0){
               d1 = d1*10+(e[n]-'0');
               n++;
            }
            else{
                t = e[n]-'0';
                for(int z = 0;z<=cou;z++)
                    t = t/10;
                d2+=t;
                cou++;
                n++;
            }
        }
    }
    n--;
    return d1+d2;
}
void cal(string e,int n)
{
    map<char,double> f;
    double temp;
    bool flag = 1;
    stack<double> s;
    char c,t;
    for(int i = 0;i<n;i++)
    {
        cin >> c >>t >>temp;
        f[c] = temp;
    }
    for(int i = 0;i<e.length();i++){
        if((e[i]<='z'&&e[i]>='a')||(e[i]<='Z'&&e[i]>='A')){
            s.push(f[e[i]]);
        }
        else if(e[i]>='0'&&e[i]<='9'){
            s.push(str2num(i,e));
        }
        else if(e[i]=='+'||e[i]=='-'||e[i]=='/'||e[i]=='*'){
            flag = eval(e[i],s);
        }
    }
    if (flag)
    cout <<fixed <<setprecision(3)<<s.top() <<endl;
}

int main()
{
    int m;
    cin >> m;
    string e;
    for(int i = 0;i<m;i++){
    		getchar();
            getline(cin,e);
            int n;
            cin >> n;
            cal(e,n);
    }

}
