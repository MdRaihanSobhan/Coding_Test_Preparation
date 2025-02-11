#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;                  // Total number of positions
int gatePos[3];         // Positions of the 3 gates (1-based index)
int men[3];             // Number of men for each gate
vector<bool> vis;       // A vector to mark positions as visited

// Function to find the distance to the nearest unvisited position on the left of position i
int left(int i)
{
    if(i > -1)
    {
        int dis = 0;
        for(int j = i; j > -1; j--)
        {
            dis++;           // Increment distance
            if(!vis[j])      // If an unvisited position is found
            {
                return dis;  // Return the distance
            }
        }
    }
    return INT_MAX;          // Return a large value if no unvisited position is found
}

// Function to find the distance to the nearest unvisited position on the right of position i
int right(int i)
{
    if(i < n)
    {
        int dis = 0;
        for(int j = i; j < n; j++)
        {
            dis++;           // Increment distance
            if(!vis[j])      // If an unvisited position is found
            {
                return dis;  // Return the distance
            }
        }
    }
    return INT_MAX;          // Return a large value if no unvisited position is found
}

// Function to calculate the distance for all men assigned to a specific gate
int findDist(int gate)
{
    int pos = gatePos[gate] - 1; // Convert to 0-based index
    int dis = 0;                // Total distance for men at this gate

    for(int i = 0; i < men[gate]; i++)
    {
        if(!vis[pos])          // If the current position is unvisited
        {
            dis++;             // Increment distance by 1
            vis[pos] = true;   // Mark the position as visited
        }
        else                  // If the current position is already visited
        {
            int l = left(pos - 1);  // Distance to the nearest unvisited position on the left
            int r = right(pos + 1); // Distance to the nearest unvisited position on the right

            if(l < r)              // Choose the closer position
            {
                dis += l + 1;      // Add distance to total
                if(pos - l > -1)
                    vis[pos - l] = true; // Mark the left position as visited
            } 
            else 
            {
                dis += r + 1;      // Add distance to total
                if(pos + r < n)
                    vis[pos + r] = true; // Mark the right position as visited
            }
        }
    }
    return dis;               // Return the total distance for this gate
}

// Function to calculate the total distance for a given order of gate processing
int placeInOrder(vector<int>& combo)
{
    int dis = 0;                        // Total distance for the current order
    vis = vector<bool>(n, false);       // Reset the visited positions for each combination

    for(int i = 0; i < combo.size(); i++)
        dis += findDist(combo[i]);      // Calculate distance for each gate in the current order

    return dis;                         // Return the total distance for this order
}

int main()
{
    ios::sync_with_stdio(false);        // Optimize input/output
    cin.tie(0);

    cin >> n;                           // Read the total number of positions

    for(int i = 0; i < 3; i++)
        cin >> gatePos[i];              // Read positions of the 3 gates

    for(int i = 0; i < 3; i++)
        cin >> men[i];                  // Read the number of men for each gate

    vector<vector<int>> combinations = {  // All possible orders of processing the gates
        {0, 1, 2},
        {1, 2, 0},
        {2, 0, 1},
        {2, 1, 0},
        {0, 2, 1},
        {1, 0, 2}
    };

    int min_dist = INT_MAX;             // Initialize minimum distance with a large value

    for(int i = 0; i < combinations.size(); i++) 
    {
        int xc = placeInOrder(combinations[i]); // Calculate distance for the current combination
        min_dist = min(min_dist, xc);  // Update the minimum distance if the current one is smaller
        cout << i << " " << min_dist << endl;  // Print the combination index and the minimum distance so far
    }

    cout << min_dist << endl;           // Print the final minimum distance
}
