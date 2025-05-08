#include<bits/stdc++.h>
using namespace std;
const int n=8;
int checkerboard[100][100];
int top=1;
int str[100][10],checkstr[100][10];

bool check(int x,int y){
    for(int i=0;i<x;i++){
        if(checkerboard[i][y]) return false;
    }

    for(int i=1;x-i>=0&&y-i>=0;i++){
        if(checkerboard[x-i][y-i]) return false;
    }
    for(int i=1;x-i>=0&&y+i>=0;i++){
        if(checkerboard[x-i][y+i]) return false;
    }
    return true;
}


void dfs(int x){
    if(x==n){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(checkerboard[i][j]){
                    str[top][i+1]=j+1;
                    break;
                }
            }
        }
        top++;
        return;
    }
    for(int i=0;i<n;i++){
        if(check(x,i)){
            checkerboard[x][i]=1;
            dfs(x+1);
            checkerboard[x][i]=0;
        }
    }
    return;
}


bool checkre(int* strchar,int cnt){
    for(int i=0;i<cnt;i++){
        for(int j=1;j<=8;j++){
            if(checkstr[i][j]!=strchar[9-j]) return false;//updown
        }
        for(int j=1;j<=8;j++)
            if(checkstr[i][j]+strchar[j]!=9) return false;//leftright
        for(int j=1;j<=8;j++)
            if(0) return false;
        for(int j=1;j<=8;j++)
            if(0) return false;
    } 
    return true;
}

int main(){
    int cnnt=0;
    dfs(0);
    for(int i=1;i<=92;i++){
        if(!checkre(str[i],cnnt)){
            for(int j=1;j<=8;j++) cout<<str[i][j];
            cout<<'\n';
            for(int j=1;j<=8;j++) checkstr[cnnt][j]=str[i][j];
            cnnt++;
        }
        
    }
    return 0;
}