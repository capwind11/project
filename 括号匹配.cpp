 #include <iostream>
 #include <stack>
 #include <string>
 using namespace std;
 bool is_right(char c)
 {
     return (c=='['||c=='{'||c=='(');
 }
 bool is_left(char c)
 {
     return (c==']'||c=='}'||c==')');
 }
 bool check(char c,stack<char> s)
 {
     if(s.empty())
        return false;
     if((c==']'&&s.top()=='[')||(c=='}'&&s.top()=='{')||(c==')'&&s.top()=='('))
        return true;
     else return false;
 }
 void match(string str)
 {
     stack<char> s;
     for(int i = 0;i<str.length();i++){
        if(is_right(str[i]))
            s.push(str[i]);
        else if(is_left(str[i])){
            if(!check(str[i],s))
                {cout << "No"<< endl;
                return;}
            s.pop();
        }
     }
     if(s.empty())
        cout <<"Yes"<<endl;
     else
        cout << "No" <<endl;
 }

 int main()
 {
     int n;
     cin >> n;
     string str;
     for(int i = 0;i<n;i++){
        cin >> str;
        match(str);
     }
 }
