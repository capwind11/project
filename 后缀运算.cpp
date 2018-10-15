#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
using namespace std;
double jisuan(char c,stack<double> &val)
{
            double n1,n2;
            switch (c){
            case '+':
                n1 = val.top();
                val.pop();
                n2 = val.top();
                val.pop();
                val.push(n1+n2);
                break;
            case '-':
                n1 = val.top();
                val.pop();
                n2 = val.top();
                val.pop();
                val.push(n2-n1);
                break;
            case '*':
                n1 = val.top();
                val.pop();
                n2 = val.top();
                val.pop();
                val.push(n1*n2);
                break;
                case '/':
                n1 = val.top();
                val.pop();
                n2 = val.top();
                val.pop();
                val.push(n2/n1);
                break;
                }


        }

double cal(string str)
{
    stack<double> val;
    for(int i = 0;i < str.length();i++){
        if(str[i]<='z'&&str[i]>='a'){
            val.push(double(str[i]-'a'+1));
        }
        else{
            jisuan(str[i],val);

    }

}return val.top();
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0;i < n;i++){
        string str;
        cin >> str;
        double d = cal(str);
        cout << fixed << setprecision(2) <<d << endl;
    }

}
