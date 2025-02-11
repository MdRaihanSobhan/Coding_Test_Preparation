#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int totalPositions;         // Total number of positions
int gatePositions[3];       // Positions of the 3 gates (1-based index)
int menCount[3];            // Number of men for each gate
vector<bool> visited;       // A vector to mark positions as visited

// Function to find the distance to the nearest unvisited position on the left of position i
int findLeftDistance(int position)
{
    if(position > -1)
    {
        int distance = 0;
        for(int j = position; j > -1; j--)
        {
            distance++;               // Increment distance
            if(!visited[j])           // If an unvisited position is found
                return distance;       // Return the distance
        }
    }
    return INT_MAX;                   // Return a large value if no unvisited position is found
}

// Function to find the distance to the nearest unvisited position on the right of position i
int findRightDistance(int position)
{
    if(position < totalPositions)
    {
        int distance = 0;
        for(int j = position; j < totalPositions; j++)
        {
            distance++;               // Increment distance
            if(!visited[j])           // If an unvisited position is found
                return distance;       // Return the distance
        }
    }
    return INT_MAX;                   // Return a large value if no unvisited position is found
}

// Function to calculate the distance for all men assigned to a specific gate
int calculateGateDistance(int gate)
{
    int position = gatePositions[gate] - 1;  // Convert to 0-based index
    int totalDistance = 0;                   // Total distance for men at this gate

    for(int i = 0; i < menCount[gate]; i++)
    {
        if(!visited[position])               // If the current position is unvisited
        {
            totalDistance++;                 // Increment distance by 1
            visited[position] = true;        // Mark the position as visited
        }
        else                                 // If the current position is already visited
        {
            int leftDist = findLeftDistance(position - 1);  // Distance to the nearest unvisited position on the left
            int rightDist = findRightDistance(position + 1); // Distance to the nearest unvisited position on the right

            if(leftDist < rightDist)                        // Choose the closer position
            {
                totalDistance += leftDist + 1;              // Add distance to total
                if(position - leftDist > -1)
                    visited[position - leftDist] = true;    // Mark the left position as visited
            } 
            else 
            {
                totalDistance += rightDist + 1;             // Add distance to total
                if(position + rightDist < totalPositions)
                    visited[position + rightDist] = true;   // Mark the right position as visited
            }
        }
    }
    return totalDistance;                     // Return the total distance for this gate
}

// Function to calculate the total distance for a given order of gate processing
int calculateTotalDistance(vector<int>& order)
{
    int totalDistance = 0;                        // Total distance for the current order
    visited = vector<bool>(totalPositions, false); // Reset the visited positions for each combination

    for(int i = 0; i < order.size(); i++)
        totalDistance += calculateGateDistance(order[i]); // Calculate distance for each gate in the current order

    return totalDistance;                         // Return the total distance for this order
}

int main()
{
    ios::sync_with_stdio(false);        // Optimize input/output
    cin.tie(0);

    cin >> totalPositions;              // Read the total number of positions

    for(int i = 0; i < 3; i++)
        cin >> gatePositions[i];        // Read positions of the 3 gates

    for(int i = 0; i < 3; i++)
        cin >> menCount[i];             // Read the number of men for each gate

    vector<vector<int>> gateOrders = {  // All possible orders of processing the gates
        {0, 1, 2},
        {1, 2, 0},
        {2, 0, 1},
        {2, 1, 0},
        {0, 2, 1},
        {1, 0, 2}
    };

    int minDistance = INT_MAX;          // Initialize minimum distance with a large value

    for(int i = 0; i < gateOrders.size(); i++) 
    {
        int currentDistance = calculateTotalDistance(gateOrders[i]); // Calculate distance for the current combination
        minDistance = min(minDistance, currentDistance);  // Update the minimum distance if the current one is smaller
        cout << i << " " << minDistance << endl;          // Print the combination index and the minimum distance so far
    }

    cout << minDistance << endl;        // Print the final minimum distance
}
