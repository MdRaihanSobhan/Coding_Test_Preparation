#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to calculate the minimum walking distance for all fishermen
int minDistance(vector<int>& gatePosition, vector<int>& menCount, int n) {
    int minDist = INT_MAX; // Initialize the minimum distance to a very large value
    
    // Calculate the last possible starting positions for each gate
    int first_gate_last_start = n - menCount[0] - menCount[1] - menCount[2] + 1; 
    int second_gate_last_start = first_gate_last_start + menCount[0]; 
    int third_gate_last_start = second_gate_last_start + menCount[1]; 

    // Iterate over all possible starting positions for gate 1
    for (int i = 1; i <= first_gate_last_start; i++) {
        // Iterate over all possible starting positions for gate 2
        for (int j = i + menCount[0]; j <= second_gate_last_start; j++) {
            // Iterate over all possible starting positions for gate 3
            for (int k = j + menCount[1]; k <= third_gate_last_start; k++) {
                int dist = 0; // Initialize the total distance for the current configuration
                
                // Calculate the distance for fishermen at gate 1
                for (int m = i; m < i + menCount[0]; m++) {
                    int gate1_cost = abs(gatePosition[0] - m) + 1; // Distance from gate 1 to spot m
                    dist += gate1_cost; 
                }

                // Calculate the distance for fishermen at gate 2
                for (int m = j; m < j + menCount[1]; m++) {
                    int gate2_cost = abs(gatePosition[1] - m) + 1; // Distance from gate 2 to spot m
                    dist += gate2_cost; 
                }

                // Calculate the distance for fishermen at gate 3
                for (int m = k; m < k + menCount[2]; m++) {
                    int gate3_cost = abs(gatePosition[2] - m) + 1; // Distance from gate 3 to spot m
                    dist += gate3_cost; 
                }

                // Update the minimum distance if the current configuration is better
                minDist = min(minDist, dist); 
            }
        }
    }

    return minDist; // Return the minimum distance found
}

int main() {
    int n; 
    cin >> n; // Input the number of fishing spots

    vector<int> gatePosition(3); // Positions of the three gates
    vector<int> menCount(3);     // Number of fishermen at each gate

    // Input gate positions
    for (int i = 0; i < 3; i++) {
        cin >> gatePosition[i]; 
    }

    // Input the number of fishermen at each gate
    for (int i = 0; i < 3; i++) {
        cin >> menCount[i]; 
    }

    // Output the minimum walking distance
    cout << minDistance(gatePosition, menCount, n) << endl; 

    return 0;
}
