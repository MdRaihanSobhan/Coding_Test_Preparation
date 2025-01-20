#include<cmath>
#include<cstring>
#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;


int string_to_num(string tmp){
    int num = 0; 
    for(int i=0; i<tmp.length(); i++){
        num = num*10+ (tmp[i]-'0'); 
    }
    return num; 
}

int main(){
    int k;
    cin>>k; 
    string st; 
    cin>>st; 
    int level = -1; 
    int ans = 0; 
    for(int i=0; i<st.length(); i++){
        if(st[i]=='(') level++;
        else if(st[i]==')') level--; 
        else if(level==k){
            string tmp ="";
            while(i<st.length() && st[i]!='(' && st[i]!=')' ){
                tmp+=st[i]; 
                i++; 
            }
            i--;
            ans+=string_to_num(tmp); 
        }
    }
    cout<<ans<<endl;
}