#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

vector<int> bubblesort(vector<int>);
bool test(vector<int> result,vector<int> origin);
void swap(int l[],int a,int b);
int main()
{
    vector<int> origin;
    int size,num;
    cin >> size;
    for(int i = 0; i < size; i++){
        cin >> num;
        origin.push_back(num);
    }
    clock_t start,end;
    start = clock();
    vector<int> result = bubblesort(origin);
    end = clock();
    double cpu_time_used;
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << cpu_time_used<< endl;
    vector<int>::iterator pos;
    for (pos = result.begin();pos<result.end();pos++)
        cout << *pos <<'\t';
    cout << endl;
    bool flag = test(result,origin);
    cout << flag;
    return 0;
}

vector<int> bubblesort(vector<int> origin)
{
    int *temp = new int[origin.size()];
    vector<int>::iterator pos;
    int i;
    for (i = 0,pos = origin.begin(); pos < origin.end(); ++pos,++i)
		temp[i]= *pos;
    for(i = origin.size();i > 0;i--){
            for(int z = 0;z<i-1;z++){
                if(temp[z]>temp[z+1]){
                    swap(temp,z,z+1);
                }
            }
    }
    vector<int> result;
    for(i = 0;i<origin.size();i++)
        result.push_back(temp[i]);
    return result;



}

void swap(int l[],int a,int b)
{
    int temp = l[a];
    l[a] = l[b];
    l[b] = temp;
}
bool test(vector<int> result,vector<int> origin){
    bool flag = 0,mark = 0;
    if (result.size()!=origin.size())
        return flag;
    vector<int>::iterator pos1,pos2;
    for(pos1 = result.begin();pos1<result.end()-1;pos1++)
    {
        if(*pos1>*(pos1+1))
           {
               return flag;
           }
    }
    for(pos1 = result.begin();pos1<result.end();pos1++){
        mark = 0;
        for(pos2 = origin.begin();pos2<origin.end();pos2++){
            if(*pos1 == *pos2)
            {
                mark = 1;
                result.erase(pos1);
                origin.erase(pos2);
            }
        }
        if (mark ==0)
            return flag;
    }


    return 1;
    }
