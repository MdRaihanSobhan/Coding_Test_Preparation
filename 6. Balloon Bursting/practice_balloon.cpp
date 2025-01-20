#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include<climits>

using namespace std; 

int burstBalloons(int left, int right, vector<int>& balloons, vector<vector<int>>& dp, bool flag){
    if(left>right) return 0; 
    if(dp[left][right]!=-1) return dp[left][right]; 
    int maxScore = INT_MIN; 
    for(int i=left; i<=right; i++){
        int leftScore = burstBalloons(left, i-1, balloons, dp, true); 
        int rightScore = burstBalloons(i+1, right, balloons, dp, true); 
        int burstScore; 
        if(flag){
            burstScore = balloons[left-1] * balloons[right+1]; 
        }
        else{
            burstScore = balloons[i]; 
        }
        maxScore = max(maxScore, leftScore + rightScore + burstScore); 
    }
    return dp[left][right] = maxScore; 
}
int main(){
    int n; 
    cin>>n; 
    vector<int> balloons(n+2, 1); 
    for(int i=1; i<=n; i++){
        cin>>balloons[i]; 
    }
    vector<vector<int> > dp(n+2, vector<int>(n+2, -1)); 
    cout<<burstBalloons(1, n, balloons, dp, false)<<endl; 

}