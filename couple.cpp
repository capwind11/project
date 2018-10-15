#include <iostream>
#include <queue>
using namespace std;
bool cou(int n)
{
    queue<int> v;
    int *t = new int[2*n];
    int p1,p2;
    for(int i = 0;i<n;i++){
        cin >> p1;
        cin >> p2;
        t[p1-1]=i;
        t[p2-1]=i;
    }
    for(int i = 0;i<2*n;i++){
        v.push(t[i]);
    }
    delete t;
    bool y;
    int t1,t2;
    while(!v.empty()){
            y = false;
        for(int i = 0;i < v.size();i++){

            t1 = v.front();
            v.pop();
            if(t1==v.front()){
                v.pop();
                i++;
                y=true;
            }
            else v.push(t1);
        }
        if(y==false){
            return false;
        }
    }
    return true;
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
