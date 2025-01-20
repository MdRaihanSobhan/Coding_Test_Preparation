#include<iostream>
#include<climits>
#include<vector>
#include<queue>
#include<cstring>
#include<cmath>

using namespace std; 

int manhattan_distance(pair<int, int> x, pair<int, int> y){
    return abs(x.first-y.first) + abs(x.second-y.second); 
}

int main(){
    int t; 
    cin>>t; 
    while(t--){
        int n; 
        cin>>n; 
        int v = n*2 + 2; 
        vector<pair<int, int>> locations(v);
        vector<vector<int> > distance(v, vector<int>(v, INT_MAX)); 
        
        cin>>locations[0].first>>locations[0].second; 
        cin>>locations[v-1].first>>locations[v-1].second; 

        for(int i=1; i<=n; i++){
            cin>>locations[i].first>>locations[i].second;
            cin>>locations[v-1-i].first>>locations[v-1-i].second; 
            cin>>distance[i][v-1-i]; 
            distance[v-1-i][i] = distance[i][v-1-i]; 
        }
        for(int i=0; i<v; i++){
            for(int j=0; j<v; j++){
                distance[i][j] = min(distance[i][j], manhattan_distance(locations[i], locations[j])); 
            }
        }

        for(int k=0; k<v; k++){
            for(int i=0; i<v; i++){
                for(int j=0; j<v; j++){
                    if(distance[i][j]> distance[i][k] + distance[k][j]){
                        distance[i][j] =  distance[i][k] + distance[k][j]; 
                    }
                }
            }
        }
        cout<<distance[0][v-1]<<endl; 
    }
}