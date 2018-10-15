#include <iostream>
#include <vector>
using namespace std;
void swap(int *n,int n1,int n2)
{
    int temp = n[n1];
    n[n1] = n[n2];
    n[n2] = temp;
}
void bubblesort(int *n,int m)
{
    for(int i=0;i<m-1;i++){
        for(int z = 0;z<m-i-1;z++){
            if(n[z]>n[z+1]){
                swap(n,z,z+1);
            }
        }
    }
}

void insertsort(int *n,int m)
{
    int j,temp;;
    for(int i = 1;i < m; i++){
        j = i;
        temp = n[j];
        while(temp<n[j-1]&&j>0){
            n[j] = n[j-1];
            j--;
        }
        n[j] = temp;
    }
}

void selectsort(int *n,int m)
{
    vector<int> v;
    for(int i = 0;i < m;i++){
        v.push_back(n[i]);
    }
    vector<int>::iterator it,ta;
    int min = *v.begin(),z=0;
    while(!v.empty()){
        for(it = v.begin();it < v.end();it++){
            if(*it < min){
                ta = it;
            }
        }
        n[z]=*ta;
        v.erase(ta);
    }
}

void mergesort(int *n,int m)
{

}
int main()
{
    int m;
    cin >>m;
    int *n = new int[m];
    for(int i = 0;i<m;i++)
        cin >> n[i];
    insertsort(n,m);
    for(int i = 0;i<m;i++)
        cout << n[i];

}
