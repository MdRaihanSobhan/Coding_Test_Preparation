#include<iostream>
#include<vector>
#include<climits>
#include<cmath>

using namespace std; 

int solve(vector<int>& gatePosition, vector<int>& menCount, int n){
    int third_gate_last_start = n - menCount[2] + 1; 
    int second_gate_last_start = third_gate_last_start - menCount[1]; 
    int first_gate_last_start = second_gate_last_start - menCount[0]; 
    int minDist = INT_MAX; 
    for(int i=1; i<=first_gate_last_start; i++){
        for(int j=i+menCount[0]; j<=second_gate_last_start; j++){
            for(int k=j+menCount[1]; k<=third_gate_last_start; k++){
                int ans = 0; 
                for(int m=i; m<i+menCount[0]; m++){
                    ans+= (abs(m-gatePosition[0]) + 1); 
                }
                for(int m=j; m<j+menCount[1]; m++){
                    ans+= (abs(m-gatePosition[1])+ 1); 
                }
                for(int m=k; m<k+menCount[2]; m++){
                    ans+= (abs(m-gatePosition[2]) + 1); 
                }
                minDist = min(minDist, ans); 
            }
        }
    }
    return minDist; 
}

int main(){
    int n; 
    cin>>n; 
    vector<int> gatePosition(3); 
    vector<int> menCount(3); 
    for(int i=0; i<3; i++){
        cin>>gatePosition[i]; 
    }
    for(int i=0; i<3; i++){
        cin>>menCount[i]; 
    }
    cout<<solve(gatePosition, menCount, n)<<endl; 

}