#include<iostream> 
#include<vector>
#include<climits>
#include<cmath>
#include<queue>
#include<unordered_map>

using namespace std; 

int manhattan_distance(pair<int, int> x, pair<int, int> y){
    return abs(x.first - y.first) + abs(x.second - y.second); 
}

int dijkstra(vector<vector<int>>& adjMat, int src, int dest){

    int n = adjMat.size(); 
    vector<int> distance (n, INT_MAX); 
    priority_queue<pair<int, int>, vector<pair<int, int>> , greater<pair<int, int>>> pq; 
    distance[src] = 0; 
    pq.push(make_pair(0, src)); 

    while(!pq.empty()){
        int currNode = pq.top().second; 
        int currDist = pq.top().first; 
        pq.pop(); 

        if(currDist> distance[currNode]) continue;

        for(int i=0; i<adjMat[currNode].size(); i++){
            int nextNode = i; 
            int weight = adjMat[currNode][i]; 
            if(distance[nextNode]> distance[currNode] + weight){
                distance[nextNode] = distance[currNode] + weight; 
                pq.push(make_pair(distance[nextNode], nextNode)); 
            }
        }
    }

    return distance[dest]; 
}

int main(){
    int t; 
    cin>>t; 
    while(t--){
        int n; 
        cin>>n; 
        int v = 2*n + 2; 
        vector<pair<int, int> > locations(v); 
        cin>>locations[0].first>>locations[0].second; 
        cin>>locations[v-1].first>>locations[v-1].second; 
        vector<vector<int>> adjMat(v, vector<int>(v, INT_MAX)); 
        for(int i=1; i<=n; i++){
            cin>>locations[i].first>>locations[i].second; 
            cin>>locations[v-1-i].first>>locations[v-1-i].second; 
            cin>>adjMat[i][v-1-i]; 
            adjMat[v-1-i][i] = adjMat[i][v-1-i]; 
        }

        for(int i=0; i<v; i++){
            for(int j=0; j<v; j++){
                adjMat[i][j] = min(adjMat[i][j], manhattan_distance(locations[i], locations[j])); 
            }
        }

        cout<<dijkstra(adjMat, 0, v-1)<<endl; 
    }
}