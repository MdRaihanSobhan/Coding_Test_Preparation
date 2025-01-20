#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

bool isValid(int r, int c, vector<vector<int>>& rockmap){
    int m = rockmap[0].size(); 
    int n = rockmap.size(); 

    if(r>=n || r<0 || c>=m || c<0 || rockmap[r][c] == 0) return false; 
    return true; 
}

int findLevel(vector<vector<int>>& rockMap){
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<> > pq;
    int n = rockMap.size(); 
    int m = rockMap[0].size(); 
    vector<vector<int>> level(n, vector<int>(m, INT_MAX));

    level[n-1][0] = 0; 

    pq.push(make_pair(0, make_pair(n-1, 0))); 

    vector<int> dc = {-1,0,1}; 
    while(!pq.empty()){
        int currentLevel = pq.top().first; 
        int r = pq.top().second.first; 
        int c = pq.top().second.second; 
        pq.pop(); 

        if(rockMap[r][c] == 3) return currentLevel; 

        for(int i=0; i<3; i++){
            int nc = c+ dc[i]; 
            if( isValid(r, nc, rockMap)){
                if(level[r][nc] > currentLevel){
                    level[r][nc] = currentLevel;  
                    pq.push(make_pair(currentLevel, make_pair(r, nc))); 
                }
            } 
        }

        for(int nr=0; nr<n; nr++){
            if(nr!=r && isValid(nr, c, rockMap)){
                if(level[nr][c]> level[r][c]){
                    int newlevel = max(currentLevel, abs(nr-r));
                    pq.push(make_pair(newlevel, make_pair(nr, c))); 
                    level[nr][c] = newlevel;  
                }
            }
        }
    }
    return -1; 
}
int main(){
    int n, m; 
    cin>>n>>m; 
    vector<vector<int>> rockMap(n, vector<int>(m)); 
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin>>rockMap[i][j]; 
        }
    }

    cout<<findLevel(rockMap)<<endl; 


}