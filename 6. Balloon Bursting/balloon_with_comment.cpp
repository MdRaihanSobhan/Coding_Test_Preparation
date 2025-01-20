#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define LL long long

using namespace std;

// Recursive function to solve the problem
LL getMaxScore(LL start, LL end, vector<LL>& balloons, bool considerNeighbors, vector<vector<LL>>& dp) {
    // Base case: no balloons in the range
    if (start > end) return 0;

    // Return precomputed result if available
    if (dp[start][end] != -1) return dp[start][end];

    LL maxScore = LLONG_MIN;

    // Try bursting each balloon in the range [start, end] as the last one
    for (LL last = start; last <= end; last++) {
        LL leftScore = getMaxScore(start, last - 1, balloons, true, dp);
        LL rightScore = getMaxScore(last + 1, end, balloons, true, dp);
        LL burstScore;

        if (considerNeighbors) {
            burstScore = balloons[start - 1] * balloons[end + 1];
        } else {
            burstScore = balloons[last];
        }

        maxScore = max(maxScore, leftScore + rightScore + burstScore);
    }

    // Store the result in the memoization table
    return dp[start][end] = maxScore;
}

int main() {
    LL numBalloons;
    cin >> numBalloons;

    vector<LL> balloons(numBalloons);
    for (LL i = 0; i < numBalloons; i++) {
        cin >> balloons[i];
    }

    // Add boundary values to simplify neighbor calculations
    balloons.insert(balloons.begin(), 1);
    balloons.push_back(1);

    // Initialize memoization table
    vector<vector<LL>> dp(numBalloons + 2, vector<LL>(numBalloons + 2, -1));

    // Solve the problem for the full range
    LL result = getMaxScore(1, numBalloons, balloons, false, dp);

    // Output the result
    cout << result << endl;

    return 0;
}
