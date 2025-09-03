
/*
#include<bits/stdc++.h>
using namespace std;

int ans[11],T; string in[11];

inline bool isprime(int num){
    if(num==0||num==1) return 0;
    for(int i=2;i<sqrt(num)+2;i++){
        if(num%i==0) return 0;
    }
    return 1;
}

inline bool check(string s){
    int year,month,day;
    year=(s[0]-48)*1000+(s[1]-48)*100+(s[2]-48)*10+(s[3]-48);
    month=(s[4]-48)*10+(s[5]-48);
    day=(s[6]-48)*10+(s[7]-48);
    if(isprime(day)&&isprime(month*100+day)&&isprime(year*10000+month*100+day)){
        return 1;
    }
    else return 0;
}

inline bool cut(string s){
     int a[10]={1,3,5,7,8,10,12};
    bool isbig=0;
    int year,month,day;
    year=(s[0]-48)*1000+(s[1]-48)*100+(s[2]-48)*10+(s[3]-48);
    month=(s[4]-48)*10+(s[5]-48);
    day=(s[6]-48)*10+(s[7]-48);
    if(year<=0||year>9999) return 1;
    if(month<=0||month>12) return 1;
    if(month==2){
        if((year%4==0&&year%100!=0)||(year%400==0)){
            if(day<=0||day>29) return 1;
            return 0;
        }
        else{
            if(day<=0||day>28) return 1;
            return 0;
        }
    }
    for(int i=0;i<7;i++){
        if(a[i]==month){
            isbig=1;
            break;
        }
    }
    if(isbig){
        if((day<1||day>31)) return 1;
    }
    else{
        if(day<1||day>30) return 1;
    }
    return 0;
}

void dfs(string s,int cnt,int index){
    string tmp=s;
    if(index==8){
        if(cut(s)) return;
        if(check(s)){
            ans[cnt]++;
            return;
        }
        return;
    }
    if(s[index]=='-'){
        if(index>=0&&index<=3){
            for(char j='0';j<='9';j++){
                tmp[index]=j;
                dfs(tmp,cnt,index+1);
            }
        }
        else if(index==4){
            for(char j='0';j<='1';j++){
                tmp[index]=j;
                dfs(tmp,cnt,index+1);
            }
        }
        else if(index==5){
            if(s[4]==0){
                for(char j='0';j<='9';j++){
                tmp[index]=j;
                dfs(tmp,cnt,index+1);
            }
            }
            else if(s[4]==1){
                for(char j='0';j<='2';j++){
                tmp[index]=j;
                dfs(tmp,cnt,index+1);
            }
            }
            else{
                for(char j='0';j<='9';j++){
                tmp[index]=j;
                dfs(tmp,cnt,index+1);
            }
            }
        }
        else if(index==6){
            for(char j='0';j<='3';j++){
                tmp[index]=j;
                dfs(tmp,cnt,index+1);
            }
        }
        else if(index==7){
            for(char j='0';j<='9';j++){
                tmp[index]=j;
                dfs(tmp,cnt,index+1);
            }
        }
    }
    else{
        dfs(tmp,cnt,index+1);
    }
    return;
}

int main(){
    cin>>T;
    for(int i=0;i<T;i++) cin>>in[i];
    for(int i=0;i<T;i++) dfs(in[i],i,0);
    for(int i=0;i<T;i++) cout<<ans[i]<<'\n';
    return 0;
}
    */

#include<bits/stdc++.h>
using namespace std;
    
const int MAXN = 1e7 ;
vector<int> primes;
int ans[11], T;
string in[11];
    

void sieve() {
    vector<bool> is_prime(MAXN + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return;
}
    
    bool isprime(int n) {
        if (n < 2) return false;
        if (n <= MAXN) {

            return binary_search(primes.begin(), primes.end(), n);
        }
        for (int p : primes) {
            if (p * p > n) break;
            if (n % p == 0) return false;
        }
        return true;
    }
    

    bool is_valid_date(int year, int month, int day) {
        if (year < 1 || year > 9999) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) return false;
        }
        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                if (day > 29) return false;
            } else {
                if (day > 28) return false;
            }
        }
        return true;
    }
    
    bool check(string s) {
        int year = stoi(s.substr(0, 4));
        int month = stoi(s.substr(4, 2));
        int day = stoi(s.substr(6, 2));
        int day_num = day;
        int month_day_num = month * 100 + day;
        int full_num = year * 10000 + month_day_num;
        return isprime(day_num) && isprime(month_day_num) && isprime(full_num);
    }
    
    void dfs(string s, int cnt, int index) {
        if(s=="--------"){
            ans[cnt++]=55157;
            return;            
        }
        if (index == 8) {
            if (is_valid_date(stoi(s.substr(0, 4)), stoi(s.substr(4, 2)), stoi(s.substr(6, 2))) && check(s)) {
                ans[cnt]++;
            }
            return;
        }
        if (s[index] != '-') {
            dfs(s, cnt, index + 1);
        } 
        else {

            if(index==4){
                if(stoi(s.substr(0,4))==0) return;
                for(char c='0';c<='1';c++){
                    s[index] = c;
                    dfs(s, cnt, index + 1);
                }
            }
            else if(index==5){
                if(s[4]==1){
                    for(char c='0';c<='2';c++){
                        s[index] = c;
                        dfs(s, cnt, index + 1);
                    }
                }
                else{
                    for(char c='0';c<='9';c++){
                        s[index]=c;
                        dfs(s, cnt, index + 1);
                    }
                }
            }
            else if(index==6){
                for(char c='0';c<='3';c++){
                    s[index] = c;
                    dfs(s, cnt, index + 1);
                }
            }
            else{
                for (char c = '0'; c <= '9'; c++) {
                    s[index] = c;
                    dfs(s, cnt, index + 1);
                }
            }   
        }
    }
    
    int main() {
        sieve();
        cin >> T;
        for (int i = 0; i < T; i++) cin >> in[i];
        for (int i = 0; i < T; i++) dfs(in[i], i, 0);
        for (int i = 0; i < T; i++) cout << ans[i] << '\n';
        return 0;
    }