
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6*2+1;
bitset<maxn> sieve;
bitset<1000001> bi;
vector<int> prime;

void inisieve(){
    sieve.set();
    sieve[1]=false;
    sieve[0]=false;
    for(int i=2;i<maxn;i++){
        if(sieve[i]) prime.push_back(i);
        for(int j=0;j<prime.size()&&i*prime[j]<maxn;j++){
            sieve[i*prime[j]]=false;
            if(i%prime[j]==0) break;
        }
    }
    return;
}

int count_in_range(int l,int r){
    if(l>r) return 0;
    bi.set();
    int ans=0;
    if(l==1) bi[0]=false;
    for(long long p:prime){
        if(p*p>r) break;
        int start=max(p*p,((l-1)/p)*p);
        for(long long i=start;i<=r;i+=p){
            if(i>=l){
                bi[i-l]=0;
            }
        }
    }
    for(int i=0;i<=r-l;i++){
        if(bi[i]) ans++;
    }
    return ans;
}

int main(){
    inisieve();
    int ans=0,l,r;
    cin>>l>>r;
    if(r<maxn){
        for(int i=l;i<=r;i++){
            if(sieve[i]) ans++;
        }
    }

    else ans= count_in_range(l,r);



    cout<<ans;
    return 0;
}
    
/*
   #include <cstdlib>
   #include <iostream>
   #include <cstdio>
   #include <math.h>
   #include <cstring>
   #include <time.h>
   
   #pragma warning(disable:4996)
   #define INF 2000000005//2 * 10^9
   #define lowbit(a) ((a)&-(a))
   inline long long max(long long a, long long b)
   {
       return a > b ? a : b;
   }
   inline long long min(long long a, long long b)
   {
       return a < b ? a : b;
   }
   
   #define FAIL -INF
   
   const long long MAXN = 6893911;//10000000;
   
   long long p[MAXN], cnt;
   bool mark[MAXN];
   int pi[MAXN];
   
   void init()
   {
       long long i, j;
       for (i = 2; i < MAXN; i++)
       {
           if (!mark[i])
               p[cnt++] = i;
           pi[i] = pi[i - 1] + !mark[i];
           for (j = 0; p[j] * i < MAXN&&j < cnt; j++)
           {
               mark[p[j] * i] = true;
               if (i%p[j] == 0)
                   break;
           }
       }
   }
   
   int f(long long n, int m)
   {
       if (n == 0)
           return 0;
       if (m == 0)
           return n - n / 2;
       return f(n, m - 1) - f(n / p[m], m - 1);
   }
   
   int Pi(long long N);
   
   int p2(long long n, int m)
   {
       int ans = 0;
       for (int i = m + 1; (long long)p[i] * p[i] <= n; i++)
           ans += Pi(n / p[i]) - Pi(p[i]) + 1;
       return ans;
   }
   
   int p3(long long n, int m)
   {
       int ans = 0;
       for (int i = m + 1; (long long)p[i] * p[i] * p[i] <= n; i++)
           ans += p2(n / p[i], i - 1);
       return ans;
   }
   
   int Pi(long long N)
   {
       if (N < MAXN)
           return pi[N];
   
       int lim = pow(N, 0.25) + 1;
       int i;
   
       for (i = 0; p[i] <= lim; i++);
   
       int ans = i + f(N, i - 1) - 1 - p2(N, i - 1) - p3(N, i - 1);
   
       return ans;
   }
   
   int main()
   {
       long long L, R;
   
       scanf("%lld %lld", &L, &R);
   
       init();
   
       printf("%d", Pi(R) - Pi(L-1));
   
   //	system("pause");
       return 0;
   }
   //1 2000000000
   //2147483647以内素数个数：105097565
*/