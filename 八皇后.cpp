#include <iostream>
using namespace std;
int n = 0;
int p[8][8]={0};
void print()
{
    for(int i = 0;i<8;i++){
        for(int i1 = 0;i1<8;i1++)
            cout << p[i][i1]<<' ';
        cout <<endl;
    }

}
bool check(int i,int z)
{
    for(int t=i-1;t>=0;t--){
        if(p[t][z]==1)
            return false;
        if(z-i+t>=0&&p[t][z-i+t]==1)
            return false;
        if(z+i-t<=7&&p[t][z+i-t]==1)
            return false;
    }
    return true;

}
void queen(int i,int z)
{
    p[i][z]=1;
    if(!check(i,z)){
        p[i][z]=0;
        return;
    }
    if(i==7){
        n++;
        return;
    }
    for(int z=0;z<8;z++){
        for(int t = i+1;t<8;t++){
            for(int t1 = 0;t<8;t++)
                p[t][t1]=0;
        }

       queen(i+1,z);
    }
}

int main()
{
    for(int i =0;i<8;i++)
    {
        for(int z=0;z<8;z++)
        {
            for(int t=0;t<8;t++)
                p[z][t]=0;
        }
        queen(0,i);
    }

    cout << n;
}
