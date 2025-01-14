#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


// Function to solve TSP using DP and bit masking
// Parameters:
// - mask: A bitmask representing the set of visited cities
// - currentCity: The current city position
// - distance: The distance matrix
// - dp: The DP table for memoization
// - n : the number of cities.
// The function returns the minimum distance to travel all the cities starting from the currentCity and visiting all the cities exactly once.

int myTSP(int mask, int currentCity, vector<vector<int> >&distance, vector<vector<int> >& dp, int n, int startCity){
    if(mask== (1<<n)-1){
        return distance[currentCity][startCity]; // If all the cities are visited, return the distance from the current city to the starting city.
    }
    if(dp[mask][currentCity]!=-1){
        return dp[mask][currentCity]; // If the result is already calculated, return the result. 
    }
    int ans = INT_MAX; 
    for(int i=0; i<n; i++){
        if((mask & 1<<i) == 0 ){ // If the city is not visited, visit the city.
            int newAns = distance[currentCity][i] + myTSP(1<<currentCity | mask, i, distance, dp, n, startCity);  
            // Add the distance from the current city to the new city and call the function recursively for the new city.
            ans = min(ans, newAns); // Update the answer with the minimum distance.
        }

    }
    return dp[mask][currentCity] = ans;  // Store the result in the memoization table and return the result. 
}
int main(){
    int t; 
    cin>>t; 
    while(t--){
        int n;
        cin>>n;
        vector<vector<int> > distance(n, vector<int>(n)); 

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin>>distance[i][j]; 
            }
        }
        vector<vector<int> > dp(1<<n, vector<int>(n,-1)); 
        int first_City = n-1;
        int result = myTSP(1<<first_City, first_City, distance, dp, n, first_City); 
        cout<<result<<endl; 
    }
    
}