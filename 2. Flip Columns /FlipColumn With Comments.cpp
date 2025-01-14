#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Function to calculate the maximum number of rows that can become all 1's
int flipColumn(int n, int m, int k, vector<vector<int> >& boolMatrix) {
    unordered_map<string, int> tracker; // Map to track row patterns and their frequency

    // Iterate over each row in the matrix
    for (int i = 0; i < n; i++) {
        string temp; // String representation of the current row
        int zeroes = 0; // Count the number of zeroes in the current row

        for (int j = 0; j < m; j++) {
            if (boolMatrix[i][j] == 0) {
                zeroes++; // Increment the zero count for this row
            }
            temp += ('0' + boolMatrix[i][j]); // Convert row to string
        }

        // Check if the row can be toggled to all 1's with k toggles
        if (k >= zeroes && (k - zeroes) % 2 == 0) {
            tracker[temp]++; // Increment count for this row pattern
        }
    }

    int ans = 0; // Variable to store the maximum number of rows that can be all 1's

    // Iterate through the tracker map to find the maximum frequency of valid patterns
    for (const auto& it : tracker) {
        ans = max(ans, it.second); // Update the maximum rows count
    }

    return ans; // Return the result
}

int main() {
    int n, m, k;
    cin >> n >> m >> k; // Input dimensions of matrix and the number of toggles
    vector<vector<int>> boolMat(n, vector<int>(m)); // Initialize the matrix

    // Input the matrix values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> boolMat[i][j];
        }
    }

    // Output the maximum number of rows that can become all 1's
    cout << flipColumn(n, m, k, boolMat) << endl;

    return 0;
}
