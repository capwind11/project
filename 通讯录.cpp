#include"iostream"
#include"utility"
#include"string.h"
using namespace std;
string find(pair<string,string> *cardlist,string name,int size);
int main()
{
    int size;
    string name;
    string phonenum;
    pair<string,string> *cardlist;
    cin >> size;
    cardlist = new pair<string,string>[size];
    for(int i=0;i<size;i++){
        cin >> name;
        cin >> phonenum;
        cardlist[i] = make_pair(name,phonenum);
    }
    string search_name;
    string targetnum;
    cin >> search_name;
    targetnum = find(cardlist,search_name,size);
    cout << targetnum;
    delete []cardlist;
    return 0;
}

string find(pair<string,string> *cardlist,string name,int size)
{
    for(int i=0;i<size;i++){
        if(name==cardlist[i].first)
            return cardlist[i].second;
    }

}

