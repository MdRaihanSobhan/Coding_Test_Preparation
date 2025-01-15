#include<iostream>
#include<vector>
#include<climits>
#include<queue>
#include<algorithm>

using namespace std; 

// Structure to represent a pipe and its connectivity
typedef struct Node{
    bool left, right, up, down; // Connectivity in four directions
} Node; 

// Function to check if a cell is within the grid boundaries
bool withinGrid(int r, int c, int n, int m){
    if(r<n && r>=0 && c<m && c>=0) return true; // Return true if within bounds
    else return false; 
}

// BFS function to calculate reachable pipe cells
int bfs(vector<vector<Node> >& pipes, int startX, int startY, int length){
    Node startNode = pipes[startX][startY]; 

    // If the starting node has no connections, return 0
    if(startNode.left == false && startNode.right == false && startNode.up == false && startNode.down == false){
        return 0; 
    }

    int n = pipes.size(); // Number of rows in the grid
    int m = pipes[0].size(); // Number of columns in the grid

    // Visited and distance arrays for BFS
    vector<vector<bool> > visited (n, vector<bool> (m, false));  
    vector<vector<int> > distance(n, vector<int>(m,0)); 

    queue<pair<int,int> > q;       // Queue for BFS
    q.push(make_pair(startX, startY)); // Push the starting position
    visited[startX][startY] = true; // Mark the starting cell as visited
    distance[startX][startY] = 1; // Set the initial distance to 1
    
    int ans = 1; // Count of reachable cells

    while(!q.empty()){
        int r = q.front().first; // Current row
        int c = q.front().second; // Current column
        q.pop(); 

        // Continue exploring if within the endoscope's range
        if(distance[r][c]<length){
            // Check upward movement
            if(withinGrid(r-1, c, n, m) && visited[r-1][c]==false && pipes[r][c].up && pipes[r-1][c].down){
                ans++; 
                visited[r-1][c] = true; // Mark as visited
                distance[r-1][c] = 1+ distance[r][c]; // Update distance
                q.push(make_pair(r-1, c)); // Add to the queue
            }
            // Check downward movement
            if(withinGrid(r+1, c, n, m) && visited[r+1][c]==false && pipes[r][c].down && pipes[r+1][c].up){
                ans++;
                visited[r+1][c] = true; 
                distance[r+1][c] = 1+ distance[r][c]; 
                q.push(make_pair(r+1, c)); 
            }
            // Check leftward movement
            if(withinGrid(r, c-1, n, m) && visited[r][c-1]==false && pipes[r][c].left && pipes[r][c-1].right){
                ans++; 
                visited[r][c-1] = true; 
                distance[r][c-1] = 1+ distance[r][c]; 
                q.push(make_pair(r,c-1)); 
            }
            // Check rightward movement
            if(withinGrid(r, c+1, n, m) && visited[r][c+1]==false && pipes[r][c].right && pipes[r][c+1].left){
                ans++; 
                visited[r][c+1] = true; 
                distance[r][c+1] = 1+ distance[r][c]; 
                q.push(make_pair(r,c+1)); 
            }
        }
    }
    return ans; // Return the count of reachable cells
}

int main(){
    int t; // Number of test cases
    cin>>t; 

    while(t--){
        int n,m,r,c,l; // Grid dimensions, start position, and endoscope range
        cin>>n>>m>>r>>c>>l; 

        vector<vector<Node> > pipes(n, vector<Node>(m)); // Grid to store pipe connectivity
        
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int type; // Type of pipe at the current cell
                cin>>type; 

                // Define pipe connectivity based on its type
                if(type==0){
                    pipes[i][j] = {false, false, false, false}; // No connections
                }
                else if(type==1){
                    pipes[i][j] = {true, true, true, true}; // All directions
                }
                else if(type==2){
                    pipes[i][j] = {false, false, true, true}; // Up, Down
                }
                else if(type==3){
                    pipes[i][j] = {true, true, false, false}; // Left, Right
                }
                else if(type==4){
                    pipes[i][j] = {false, true, true, false}; // Up, Right
                }
                else if(type==5){
                    pipes[i][j] = {false, true, false, true}; // Down, Right
                }
                else if(type==6){
                    pipes[i][j] = {true, false, false, true}; // Down, Left
                }
                else if(type==7){
                    pipes[i][j] = {true, false, true, false}; // Up, Left
                }
            }
        }

        // Perform BFS and print the result for the current test case
        cout<<bfs(pipes, r, c, l)<<endl; 
    }
}
