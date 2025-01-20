#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to assign fishermen to nearest available spots symmetrically
pair<int, vector<bool>> assignFishermen(vector<bool> spots, int gatePos, int fishermenCount) {
    int n = spots.size();
    int totalDistance = 0;
    vector<int> assignedSpots;
    vector<pair<int, int>> queue = {{gatePos, 0}}; // (spot index, distance)
    
    while (assignedSpots.size() < fishermenCount) {
        sort(queue.begin(), queue.end(), [](pair<int, int> a, pair<int, int> b) {
            return a.second == b.second ? a.first < b.first : a.second < b.second;
        });
        
        auto [spot, distance] = queue[0];
        queue.erase(queue.begin());
        
        if (spot >= 0 && spot < n && !spots[spot]) {
            assignedSpots.push_back(spot);
            totalDistance += distance;
            spots[spot] = true;
        } else {
            if (spot - 1 >= 0) queue.push_back({spot - 1, distance + 1});
            if (spot + 1 < n) queue.push_back({spot + 1, distance + 1});
        }
    }
    
    return {totalDistance, spots};
}

// Function to calculate the minimum walking distance using permutations
int minimizeWalkingDistance(int N, vector<int>& gates, vector<int>& fishermen) {
    int minDistance = INT_MAX;

    vector<int> order = {0, 1, 2}; // Gate indices
    do {
        int totalDistance = 0;
        vector<bool> spots(N, false); // Fishing spots availability
        
        for (int i : order) {
            int gatePos = gates[i] - 1; // Convert 1-based index to 0-based
            int fishermenCount = fishermen[i];
            auto [distance, updatedSpots] = assignFishermen(spots, gatePos, fishermenCount);
            spots = updatedSpots;
            totalDistance += distance;
        }
        
        minDistance = min(minDistance, totalDistance);
    } while (next_permutation(order.begin(), order.end()));
    
    return minDistance;
}

// Main function
int main() {
    // Input
    int N;
    cin >> N; // Number of fishing spots
    
    vector<int> gates(3), fishermen(3);
    for (int i = 0; i < 3; ++i) cin >> gates[i];       // Gate positions
    for (int i = 0; i < 3; ++i) cin >> fishermen[i];   // Fishermen count at each gate
    
    // Calculate and output the result
    int result = minimizeWalkingDistance(N, gates, fishermen);
    cout << result << endl;

    return 0;
}
