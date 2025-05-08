#include <limits.h>	    //声明INT_MAX和ULONG_MAX常量
#include <windows.h>	//声明GetTickCount()函数,其返回从开机到现在经过的毫秒数
//#include <stdlib.h>   //声明rand和srand函数
//#include <time.h>    //声明time函数
#include<bits/stdc++.h>
using namespace std;
class TRandom
{	
public:
	//缺省使用系统时间(开机后经过的毫秒数)为种子
	TRandom (long seed=0) { mSeed=(seed?seed: GetTickCount()); } 
	//也可以定义自己的种子
	void Seed(long seed=0)	{ mSeed=(seed?seed: GetTickCount( )); }     
	//取得一个随机的整数
	int  Integer() { return Next();}        
	//取得一个在指定范围内的随机整数
	int  Integer(int min,int max) { return min+Next()%(max-min+1);} 
   	//取得一个随机的（0到1之间的）小数
	double Real() 	{return double(Next())/double(INT_MAX);}
private:
    //使用调和算法
	void Change()	{mSeed=(314159265*mSeed+13579)%ULONG_MAX;}
   	//取得伪随机数发生器的随机数序列中的下一个随机整数
	int  Next() 
{ 
        int loops=mSeed%3;	
        for (int i=0;i<=loops;i++)  
            Change ();
		return int(mSeed/2); 
    }
	//随机数发生器的种子
unsigned long  mSeed;   
};

class dice{
public:
    dice(){
        for(int i=1;i<=6;i++){
            face[i].point=i;
        }
        
    }
    void cast(){
        int up=rand.Integer(1,6);
        int front=up;
        while(front==up||front==7-up){
            front = rand.Integer(1,6);
        }
        int left=0;
        if(up>front){
            left = diceMapping[{front,up}].second;
        }
        else{
            left = diceMapping[{up,front}].first;
        }
        cout<<"上面"<<up<<endl;
        cout<<"底面"<<7-up<<endl;
        cout<<"前面"<<front<<endl;
        cout<<"后面"<<7-front<<endl;
        cout<<"左面"<<left<<endl;
        cout<<"右面"<<7-left<<endl;
    }
private:
    TRandom rand;

    class di{
        public:
        int point;
        di* front;
        di* back;
        di* right;
        di* left;
        di* beneth;
    };
    di face[7];

        std::map<std::pair<int, int>, std::pair<int, int>> diceMapping = {
        {{1, 2}, {3, 4}}, // up=1, front=2 → left=3, right=4
        {{1, 3}, {5, 2}},
        {{1, 4}, {2, 5}},
        {{1, 5}, {4, 2}},
        // {{2, 1}, {4, 3}},
        {{2, 3}, {1, 6}},
        {{2, 4}, {6, 1}},
        {{2, 6}, {3, 1}},
        // {{3, 1}, {2, 5}},
        // {{3, 2}, {6, 1}},
        {{3, 5}, {1, 6}},
        {{3, 6}, {5, 1}},
        {{4, 5}, {2, 1}},
        {{4, 6}, {2, 5}},
        {{5, 6}, {4, 3}},
    };
};

int main(){
    dice dice;
    dice.cast();
}