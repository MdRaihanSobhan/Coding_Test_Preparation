#include <cmath>
#include <cstdio>
#include <vector>
#include<climits>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include<queue>
using namespace std;

vector<int> dc = {-1, 0, 1}; 
int playGame(int r, int c, vector<vector<int>>& grid, vector<vector<vector<vector<int>>>> dp, int safeRows, bool bombUsed){
    if(r==0){
        return 0; 
    }
    if(dp[r][c][safeRows][bombUsed]!=-1) return dp[r][c][safeRows][bombUsed]; 
    int maxCoins = 0; 
    for(int i=0;i<3; i++){
        int nr = r-1; 
        int nc = c+dc[i]; 
        if( nr<0 || nc>=5 || nc<0) continue;
        if(grid[nr][nc]==2){
            if(!bombUsed){
                maxCoins= max(maxCoins, playGame(nr, nc, grid, dp, 5, true)); 
            }
            else{
                if(safeRows>0){
                    maxCoins = max(maxCoins, playGame(nr, nc, grid, dp, safeRows-1, bombUsed)); 
                }
                else{
                    continue;
                }
            }
        }
        else{
            int coins = grid[nr][nc]; 
            maxCoins = max(maxCoins, coins + playGame(nr, nc, grid, dp, safeRows-(safeRows>0), bombUsed)); 
        }
    }
    return dp[r][c][safeRows][bombUsed] = maxCoins; 
}
int main(){
    int t;
    cin>>t; 
    for(int tc = 1; tc<=t; tc++){
        int n; 
        cin>>n; 
        vector<vector<int>> grid(n, vector<int>(5)); 
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(5, vector<vector<int>>(6, vector<int>(2, -1)))); 
        for(int i=0; i<n; i++){
            for(int j=0; j<5; j++){
                cin>>grid[i][j]; 
            }
        }
        cout<<"#"<<tc<<" "<<playGame(n, 2,grid, dp,0,false )<<endl; 
    }
}