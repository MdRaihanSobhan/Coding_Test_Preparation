#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Function to convert a string to an integer
// This function takes a string representing a number and converts it to an integer.
int tonum(string str)
{
    int num = 0;
    // Loop through each character in the string
    for(int i = 0; i < str.size(); i++)
    {
        // Multiply the current value of 'num' by 10 and add the current digit
        num = num * 10 + (str[i] - '0');
    }
    return num; // Return the resulting integer
}

int main() 
{
    // Read the target level (K) and the tree string
    int k;
    cin >> k;

    string s;
    cin >> s;

    // Initialize variables
    int level = -1;  // Start at level -1 (before the root)
    int sum = 0;     // Sum of nodes at level K
    int n = s.size(); // Size of the input string

    // Traverse through the tree string
    for(int i = 0; i < n; i++)
    {
        // If we encounter '(', it indicates we are going deeper into the tree, so increment the level
        if(s[i] == '(')
            level++;

        // If we encounter ')', it means we're closing the current subtree, so decrement the level
        else if(s[i] == ')') 
            level--;

        // If we're at the desired level (level == k), process the node value
        else if(level == k)
        {
            string tmp; // Temporary string to store the number at the current level
            // Loop through until we encounter another '(' or ')', which are boundary markers for nodes
            while(i < n && s[i] != '(' && s[i] != ')')
            {
                tmp.push_back(s[i]); // Add the current character (digit) to the temporary string
                i++;  // Move to the next character
            }
            i--; // Decrement i to ensure we don't skip a character
            // Convert the string (tmp) to an integer and add it to the sum
            sum += tonum(tmp);
        }
    }

    // Output the sum of the values at level K
    cout << sum << endl;

    return 0; // Program ends successfully
}
