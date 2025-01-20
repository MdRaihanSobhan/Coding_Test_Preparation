#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<cstring>
#include<cmath> 

using namespace std; 

int modifiedTSP(int mask, int current, vector<vector<int> >& dp, vector<vector<int> >& distance, int n, int home){
    if(mask == (1<<(n-1))-1){
        return distance[current][home]; 
    }
    if(dp[mask][current]!=-1){
        return dp[mask][current]; 
    }
    int ans = INT_MAX; 
    for(int i=0; i<n-1; i++){
        if((mask & (1<<i))==0){
            int newAns = distance[current][i] + modifiedTSP((mask | (1<<i)), i, dp, distance, n, home); 
            ans = min(ans, newAns); 
        }
    }
    return dp[mask][current] = ans; 
}

int manhattan_distance(pair<int, int> x, pair<int, int> y){
    return abs(x.first - y.first) + abs(x.second - y.second); 
}
int main(){
    int t = 10; 
    for(int tc=1; tc<=t; tc++){
        int n; 
        cin>>n; 
        n+=2; 
        vector<vector<int> > distance(n, vector<int>(n)); 
        vector<vector<int> > dp ((1<<n), vector<int> (n, -1)); 
        vector<pair<int, int>> locations(n); 
        cin>>locations[0].first>>locations[0].second; 
        cin>>locations[n-1].first>>locations[n-1].second; 
        for(int i=1; i<n-1; i++){
            cin>>locations[i].first>>locations[i].second; 
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                distance[i][j] = manhattan_distance(locations[i], locations[j]); 
            }
        }
        cout<<"# " << tc<< " "<<modifiedTSP(1, 0, dp, distance, n, n-1)<<endl; 
    }
}