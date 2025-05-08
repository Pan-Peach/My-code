#include<bits/stdc++.h>
using namespace std;
const int maxn=10000000;
class DSU{
  public:
    vector<int> pa;

    DSU(int n){
      pa.resize(n+1);
      for(int i=1;i<=n;i++){
        pa[i]=i;
      }
    }

    int find(int x){
      int ori=x;
      vector<bool> visited(pa.size(),0);
      while(x!=pa[x]&&!visited[x]){
        visited[x]=1;
        x=pa[x];
        if(x==ori){
          return -1;
        }
      }
      return x;
    }

    int findlen(int x){
      int len=0;
      while(pa[x]!=x){
        x=pa[x];
        len++;
      }
      return len;
    }

    int unite(int x,int y){
      if(find(x)==find(y)){
        int len=abs(findlen(x)-findlen(y))+1;
        pa[x]=y;
        return len;
      }
      pa[x]=y;
      return maxn;
    }

/*    int findcyc(int min){
      vector<bool> visited(pa.size(),0);
      int len=0;
      for(int i=1;i<pa.size();i++){
        len=0;
        bool iscyc=true;
        if(!visited[i]&&i!=pa[i]){
          int x=i,ori=i;
          while(pa[x]!=ori){
            visited[x]=true;
            x=pa[x];
            len++;
            if(x==pa[x]){
              iscyc=false;
              break;
            }
          }
          if(iscyc) min=(min<len)?min:len;
        }
      }
      return min;
    }
*/

};

int main(){
  int n,t;
  cin>>n;
  DSU dsu(n);
  int len,min=maxn;
  for(int i=1;i<=n;i++){
    cin>>t;
    len=dsu.unite(i,t);
    min=(min<len)?min:len;
  }
  cout<<min;
  return 0;
}