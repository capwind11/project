#include <iostream>
#include <stack>
using namespace std;
int main()
{
   stack<int> s;

s.push(3);

s.push(3);

s.pop();

s.pop();
s.pop();
cout<<s.top()<<endl;
s.push(3);
cout<<s.top()<<endl;
}



