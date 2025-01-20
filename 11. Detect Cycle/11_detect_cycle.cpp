#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
#include <climits>
using namespace std;
vector<int> currPath; 
vector<int> cycleNodes; 
int minSum = INT_MAX; 

int nodeSum(vector<int>& path){
    int sum = 0; 
    for(int i=0; i<path.size(); i++){
        sum+=path[i]; 
    }
    return sum; 
}

void findCycle(vector<vector<int>>& adjList, int currNode, vector<bool>& visited, vector<int>& currPath){
    visited[currNode] = true; 
    currPath.push_back(currNode);
    for(int i : adjList[currNode]) {
        if(!visited[i]){
            findCycle(adjList, i, visited, currPath); 
        }
        else{
            if(currPath[0]!=i) continue;
            else{
                if(nodeSum(currPath)<minSum){
                    minSum = nodeSum(currPath);
                    cycleNodes = currPath; 
                }
            }
        }
    }
    visited[currNode] = false; 
    currPath.pop_back(); 
}
int main(){
    int n, m; 
    cin>>n>>m; 
    vector<vector<int>> adjList(n+1); 
    vector<bool> visited(n+1, false); 
    for(int i=0; i<m; i++){
        int a, b; 
        cin>>a>>b; 
        adjList[a].push_back(b); 
    }

    for(int i=1; i<=n; i++){
        findCycle(adjList, i, visited, currPath); 
    }
    
    sort(cycleNodes.begin(), cycleNodes.end()); 
    for(int i=0; i<cycleNodes.size(); i++){
        cout<<cycleNodes[i]<<" "; 
    }
    cout<<endl; 
}