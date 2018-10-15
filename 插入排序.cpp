#include <iostream>
using namespace std;
void swap(int *a,int n1,int n2)
{
    int t = a[n1];
    a[n1] = a[n2];
    a[n2] = t;
}

void insert(int *a)
{
    for (int i = 1;i<5;i++){
        int j = i;
        int key = a[j];
        while(key<a[j-1]&&j>=1){
            a[j] = a[j-1];
            j--;
        }
        a[j] = key;
    }
}

int main()
{
    int a[5]={9,3,1,8,4};
    insert(a);
    for (int i=0;i<5;i++)
        cout << a[i];
}
