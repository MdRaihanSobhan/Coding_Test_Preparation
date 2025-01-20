#include<iostream> 
#include<vector>
#include<climits>
#include<cmath>
#include<queue>
#include<unordered_map>

using namespace std;

// Function to calculate Manhattan distance between two points
int manhattan_distance(pair<int, int> x, pair<int, int> y) {
    return abs(x.first - y.first) + abs(x.second - y.second); 
}

// Function implementing Dijkstra's algorithm to find the shortest path in a weighted graph
int dijkstra(vector<vector<int>>& adjMat, int src, int dest) {
    int n = adjMat.size(); // Number of nodes in the graph
    vector<int> distance(n, INT_MAX); // Distance array initialized to infinity
    // Priority queue to store nodes with their distances, sorted by distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
    distance[src] = 0; // Distance to the source is 0
    pq.push(make_pair(0, src)); 

    // Process nodes until the priority queue is empty
    while (!pq.empty()) {
        int currNode = pq.top().second; // Current node
        int currDist = pq.top().first; // Distance to the current node
        pq.pop(); 

        // Skip if the current distance is greater than the recorded distance
        if (currDist > distance[currNode]) continue;

        // Traverse all neighbors of the current node
        for (int i = 0; i < adjMat[currNode].size(); i++) {
            int nextNode = i; // Neighbor node
            int weight = adjMat[currNode][i]; // Weight of the edge
            // Relaxation step
            if (distance[nextNode] > distance[currNode] + weight) {
                distance[nextNode] = distance[currNode] + weight; 
                pq.push(make_pair(distance[nextNode], nextNode)); 
            }
        }
    }

    return distance[dest]; // Return the shortest distance to the destination
}

int main() {
    int t; 
    cin >> t; // Number of test cases
    while (t--) {
        int n; 
        cin >> n; // Number of wormholes
        int v = 2 * n + 2; // Total number of nodes (source, destination, and wormholes)
        vector<pair<int, int>> locations(v); // Stores coordinates of all nodes

        // Input source and destination coordinates
        cin >> locations[0].first >> locations[0].second; // Source
        cin >> locations[v - 1].first >> locations[v - 1].second; // Destination

        // Initialize adjacency matrix for the graph
        vector<vector<int>> adjMat(v, vector<int>(v, INT_MAX)); 

        // Input wormhole data
        for (int i = 1; i <= n; i++) {
            cin >> locations[i].first >> locations[i].second; // Entry point of wormhole
            cin >> locations[v - 1 - i].first >> locations[v - 1 - i].second; // Exit point of wormhole
            cin >> adjMat[i][v - 1 - i]; // Cost to use the wormhole
            adjMat[v - 1 - i][i] = adjMat[i][v - 1 - i]; // Bi-directional wormhole
        }

        // Fill adjacency matrix with Manhattan distances between all pairs of nodes
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                adjMat[i][j] = min(adjMat[i][j], manhattan_distance(locations[i], locations[j])); 
            }
        }

        // Find and output the minimum cost from source to destination
        cout << dijkstra(adjMat, 0, v - 1) << endl; 
    }
}
