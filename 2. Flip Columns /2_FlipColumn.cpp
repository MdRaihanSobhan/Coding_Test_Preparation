#include<iostream>
#include<algorithm>
#include<climits>
#include<unordered_map>
#include<vector>
#include <cmath>
#include <cstdio>

using namespace std; 
int main(){
    int n, m, k; 
    cin>>n>>m>>k; 
    vector<vector<int> > boolMatrix(n, vector<int>(n)); 
    unordered_map<string, int> frequency; 
    int ans = 0; 
    for(int i=0; i<n; i++){
        int zeroes = 0; 
        string temp; 
        for(int j=0; j<m; j++){
            cin>>boolMatrix[i][j]; 
            if(boolMatrix[i][j]==0){
                zeroes++; 
            }
            temp+=('0'+boolMatrix[i][j]); 
        }
        if(zeroes<=k && (k-zeroes)%2==0){
            frequency[temp]++; 
        }
    }
    for(const auto& it : frequency){
        ans = max(ans, it.second); 
    }
    cout<<ans<<endl; 
}