#include <vector>
#include <utility>
#include <iostream>
using namespace std;
void give_out(pair<int,int>* st,int num);
void whistle_blow(pair<int,int>* st,int num);
bool check(pair<int,int>* st,int num);
void given(pair<int,int>* st,int num);

int main()
{
    int num,rounds,candys;
    pair<int,int> *st;
    cin >> num;
    while(num)
    {
        rounds = 0;
        st = new pair<int,int>[num];
        give_out(st,num);
        while(check(st,num)){
            rounds++;
            whistle_blow(st,num);
            given(st,num);
        }
        cout << rounds << ' ' << st[0].second <<endl;
        cin >> num;
        }

    return 0;

}

void give_out(pair<int,int>* st,int num)
{
    int even;
    for(int i = 0;i<num;i++){
        cin >> even;
        st[i] = make_pair(i,even);
    }
}

void whistle_blow(pair<int,int>* st,int num)
{
    int temp[num];
    for(int i = 0;i < num;i++){
        st[i].second = st[i].second/2;
        temp[i]=st[i].second;
    }
    for(int i = 1;i < num;i++){
        st[i].second +=temp[i-1];
    }
    st[0].second += temp[num-1];
}

bool check(pair<int,int>* st,int num)
{
    for(int i =0;i < num-1;i++){
        if(st[i].second != st[i+1].second)
            return 1;
    }
    return 0;
}

void given(pair<int,int>* st,int num)
{
    for(int i = 0;i < num;i++){
        if((st[i].second%2)!=0){
            st[i].second +=1;
        }
    }
}
