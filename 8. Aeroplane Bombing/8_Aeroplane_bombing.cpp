#include<iostream>
#include<vector>
#include<climits>
#include<cmath>
#include<algorithm>

using namespace std; 

int maxScore = 0; 
int dc[3] = {-1, 0, 1}; 
void playGame(int r, int c, vector<vector<int>>& grid, int coins, int safeRows, bool bombUsed){
    if(r==0){
        maxScore = max(maxScore, coins); 
        return; 
    }
    for(int i=0; i<3; i++){
        int nr = r-1; 
        int nc = c + dc[i]; 
        if(nr<0 || nc<0 || nc>=5) continue;

        if(grid[nr][nc] == 2){
            if(!bombUsed){
                playGame(nr, nc, grid, coins, 5, true); 
            }
            else{
                if(safeRows>0){
                    playGame(nr, nc, grid, coins, safeRows-1, bombUsed); 
                }
                else{
                    continue;
                }
            }
        }
        else{
            playGame(nr, nc, grid, coins+grid[nr][nc] , safeRows-(safeRows>0), bombUsed); 
        }
    }
}

int main(){
    int t; 
    cin>>t; 
    for(int tc = 1; tc<=t; tc++){
        int n; 
        cin>>n; 
        vector<vector<int>> grid (n, vector<int>(5)); 
        for(int i=0; i<n; i++){
            for(int j=0; j<5; j++){
                cin>>grid[i][j]; 
            }
        }
        maxScore = 0; 
        playGame(n, 2, grid, 0, 0, false); 
        cout<<"#"<<tc<<" "<<maxScore<<endl; 
    }
}