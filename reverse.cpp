#include <iostream>
#include <string>
#include <stack>
using namespace std;
void reverse(string s)
{
    stack<char> st;
    for(int i = 0;i<s.length();i++){

        if (s[i]=='_'){
            while(!st.empty()){
                cout<<st.top();
                st.pop();
            }
            cout << s[i];
        }
        else st.push(s[i]);
    }

    while(!st.empty()){
        cout<<st.top();
        st.pop();
    }
    cout<<endl;
}

int main()
{
    string a;
    int b;
    cin >>b;
    while(b){
        cin >> a;
        reverse(a);
        b--;
    }

}
