#include<iostream>
#include<vector>
#include<algorithm>
using namespace std; 

int TSP(int mask, int currentCity, vector<vector<int> >& distance, vector<vector<int> >& dp, int n, int startCity ){
    if(mask == (1<<n)-1){
        return distance[currentCity][startCity]; 
    }
    if(dp[mask][currentCity]!=-1){
        return dp[mask][currentCity]; 
    }
    int ans = INT_MAX; 
    for(int i=0; i<n; i++){
        if((mask & (1<<i)) ==0){
            int newAns = distance[currentCity][i] + TSP((1<<currentCity)| mask, i, distance, dp, n, startCity); 
            ans = min(ans, newAns); 
        }
    }
    return dp[mask][currentCity] = ans; 
}

int main(){
    int t; 
    cin>>t; 
    while(t--){
        int n; 
        cin>>n; 
        vector<vector<int> > distance(n, vector<int> (n)); 
        vector<vector<int> > dp ((1<<n), vector<int>(n, -1));
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin>>distance[i][j]; 
            }
        }
        cout<<TSP(1, 0, distance, dp , n, 0)<<endl; 
    }
    return 0;
}