#include <iostream>
#include <algorithm>
using namespace std;

// Global variables
int n, maxCoins; // n: number of rows, maxCoins: maximum coins collected
int grid[15][5]; // The game grid (max 15 rows, 5 columns)
int dc[] = {-1, 0, 1}; // Movement directions: left (-1), stay (0), right (+1)

// Recursive function to simulate the game
void playGame(int r, int c, int coins, bool useBomb, int safeRows) {
    // Base case: if we've reached the top of the grid
    if (r == 0) {
        maxCoins = max(maxCoins, coins); // Update maxCoins if this path yields more
        return;
    }

    // Explore all three possible movements (left, stay, right)
    for (int i = 0; i < 3; i++) {
        int nr = r - 1;     // Move to the previous row
        int nc = c + dc[i]; // Compute the new column position

        // Check if the move is within bounds
        if (nr >= 0 && nc >= 0 && nc < 5) {
            // If the next cell contains an enemy (2)
            if (grid[nr][nc] == 2) {
                // If the bomb has not been used yet, use it and clear the next 5 rows
                if (!useBomb) {
                    playGame(nr, nc, coins, true, 5);
                } 
                // If the bomb has already been used
                else {
                    // Check if we're still in a "safe" zone (after bomb usage)
                    if (safeRows > 0) {
                        playGame(nr, nc, coins, useBomb, safeRows - 1);
                    } 
                    // Otherwise, this path is invalid (encounter enemy without protection)
                    else {
                        continue;
                    }
                }
            } 
            // If the next cell does not contain an enemy
            else {
                // Collect the coin (if any) and proceed
                playGame(nr, nc, coins + grid[nr][nc], useBomb, safeRows - (safeRows > 0));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); // Optimize input/output
    cin.tie(0);

    int t; // Number of test cases
    cin >> t;

    // Process each test case
    for (int k = 1; k <= t; k++) {

        cin >> n; // Read the number of rows in the grid
        for (int i = 0; i < n; i++) {      // Input the grid
            for (int j = 0; j < 5; j++) {  // Each row contains 5 columns
                cin >> grid[i][j];
            }
        }

        maxCoins = 0; // Initialize the maximum coins collected for this test case
        playGame(n, 2, 0, false, 0); // Start the game from the bottom-middle cell
        
        cout << "#" << k << " "; // Print the test case number

        cout << maxCoins << endl; // Output the result for this test case
    }
    return 0;
}
