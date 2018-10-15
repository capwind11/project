#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;
int main()
{
time_t t;
srand((unsigned) time(&t));
int a = (rand()*123+rand()*59)%3;
int b = (rand()*123+rand()*59)%3;
cout<<a<<" "<<b<<endl;
}
