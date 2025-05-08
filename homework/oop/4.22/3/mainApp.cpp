#include<iostream>
#include"a.h"
#include"b.h"
using namespace std;
int main(int argc,char * argv[])
{
    A aA;
    B aB(aA);
if (argc>1) 
{
        aA.Display(argv[1]);
}
else 
{
        aA.Display();
        aB.Func();
    }
    cout<<sizeof(A)<<endl;
    return 0;
}
