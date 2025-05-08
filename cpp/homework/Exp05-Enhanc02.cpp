#include<bits/stdc++.h>
using namespace std;

bool is_valid(char*a,int b){
    
	char* s = a;
	if (*a == '_' || ((*a <= 'Z' && *a >= 'A') || (*a <= 'z') && (*a >= 'a'))) {
		a++;
		while (a-s<b) {
			if (!(((*a >= '0') && (*a <= '9')) || *a == '_' || ( * a <= 'Z' && *a >= 'A') || (*a <= 'z' && *a >= 'a'))) {
				return 0;
			}
		a++;
		}
		return 1;
	}
	else return 0;
}
int main(){
    int n;char in[101][400];
    int len;
    int yes=0,no=0;
    cin>>n;
    cin.ignore();
    for(int i=0;i<n;i++){
        gets(in[i]);
        len=strlen(in[i]);
        if(is_valid(in[i],len)){
            yes++;
        }
        else no++;
    }
    cout<<"Valid:"<<yes<<'\n'<<"Invalid:"<<no;
    return 0;
}