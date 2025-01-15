#include<iostream>
#include<vector>
#include<climits>
#include<queue>
#include<algorithm>

using namespace std; 

typedef struct Node{
    bool left, right, up, down; 
} Node; 

bool withinGrid(int r, int c, int n, int m){
    if(r<n && r>=0 && c<m && c>=0) return true; 
    else return false; 
}

int bfs(vector<vector<Node> >& pipes, int startX, int startY, int length){
    Node startNode = pipes[startX][startY]; 
    if(startNode.left == false && startNode.right == false && startNode.up == false && startNode.down == false){
        return 0; 
    }
    int n = pipes.size();
    int m = pipes[0].size(); 
    vector<vector<bool> > visited (n, vector<bool> (m, false));  
    vector<vector<int> > distance(n, vector<int>(m,0)); 
    queue<pair<int,int> > q;       
    q.push(make_pair(startX, startY)); 
    visited[startX][startY] = true; 
    distance[startX][startY] = 1; 
    int ans = 1; 
    while(!q.empty()){
        int r = q.front().first;
        int c = q.front().second; 
        q.pop(); 
        if(distance[r][c]<length){
            if(withinGrid(r-1, c, n, m) && visited[r-1][c]==false && pipes[r][c].up && pipes[r-1][c].down){
                ans++; 
                visited[r-1][c] = true; 
                distance[r-1][c] = 1+ distance[r][c]; 
                q.push(make_pair(r-1, c)); 
            }
            if(withinGrid(r+1, c, n, m) && visited[r+1][c]==false && pipes[r][c].down && pipes[r+1][c].up){
                ans++;
                visited[r+1][c] = true; 
                distance[r+1][c] = 1+ distance[r][c]; 
                q.push(make_pair(r+1, c)); 
            }
            if(withinGrid(r, c-1, n, m) && visited[r][c-1]==false && pipes[r][c].left && pipes[r][c-1].right){
                ans++; 
                visited[r][c-1] = true; 
                distance[r][c-1] = 1+ distance[r][c]; 
                q.push(make_pair(r,c-1)); 
            }
            if(withinGrid(r, c+1, n, m) && visited[r][c+1]==false && pipes[r][c].right && pipes[r][c+1].left){
                ans++; 
                visited[r][c+1] = true; 
                distance[r][c+1] = 1+ distance[r][c]; 
                q.push(make_pair(r,c+1)); 
            }

        }
    
    }
    return ans; 
 
}

int main(){
    int t; 
    cin>>t; 
    while(t--){
        int n,m,r,c,l; 
        cin>>n>>m>>r>>c>>l; 
        vector<vector<Node> > pipes(n, vector<Node>(m));
        
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int type; 
                cin>>type; 
                if(type==0){
                    pipes[i][j] = {false, false, false, false}; 
                }
                else if(type==1){
                    pipes[i][j] = {true, true, true, true}; 
                }
                else if(type==2){
                    pipes[i][j] = {false, false, true, true}; 
                }
                else if(type==3){
                    pipes[i][j] = {true, true, false, false}; 
                }
                else if(type==4){
                    pipes[i][j] = {false, true, true, false}; 
                }
                else if(type==5){
                    pipes[i][j] = {false, true, false, true}; 
                }
                else if(type==6){
                    pipes[i][j] = {true, false, false, true}; 
                }
                else if(type==7){
                    pipes[i][j] = {true, false, true, false}; 
                }                
            }
        }
        cout<<bfs(pipes, r, c, l)<<endl; 
    }
}