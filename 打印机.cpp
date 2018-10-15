#include <iostream>
#include <queue>
#include <utility>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for(int i = 0;i<n;i++)
    {
        int t = 0;
        int l,p,y;
        pair<int,int> *e = new pair<int,int>[l];
        queue<pair<int,int> > q;
        priority_queue<int> prq;
        cin >> l >> p;
        for(int z = 0;z<l;z++){
            cin >> y;
            e[z] = make_pair(z,y);
            q.push(e[z]);
            prq.push(y);
        }
        while(!(q.front().first==p&&q.f().second==prq.top())){
            if(q.front().second==prq.top()){
                q.pop();
                prq.pop();
                t++;
                continue;
            }
            else{
                pair<int,int> temp = q.front();
                q.pop();
                q.push(temp);
            }
        }
        cout << t+1<< endl;
    }

}
