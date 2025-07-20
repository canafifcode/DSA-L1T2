#include<bits/stdc++.h>
using namespace std;
/*
Problem Statement
Given an array of integers A[] of size n, the task is to find the maximum difference between two
elements in the array such that the larger element appears after the smaller element in the array.
Input
The size of the array, n An array A of integers.
Output
A single integer representing the maximum difference A[j] − A[i] such that j > i and A[j] > A[i].
Constraints
• 1 ≤ n ≤ 105
• −109 ≤ A[i] ≤ 109
Approach
You must solve this problem using the Divide and Conquer technique.
*/

int maxConsecutiveDiff(int arr[], int left,int right) {
    if (left >= right) return INT_MIN;

    int mid = (left + right) / 2;

    // Solve left and right halves
    int leftAns = maxConsecutiveDiff(arr, left, mid);
    int rightAns = maxConsecutiveDiff(arr, mid + 1, right);

    int leftMin = arr[left];
    for (int i = left + 1; i <= mid; i++) {
        leftMin = min(leftMin, arr[i]);
    }

    int rightMax = arr[mid + 1];
    for (int i = mid + 2; i <= right; i++) {
        rightMax = max(rightMax, arr[i]);
    }

    int crossAns = rightMax - leftMin;

    return max({leftAns, rightAns, crossAns});
}

int main(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int ConsecutiveDiff= maxConsecutiveDiff(arr, 0,n-1);
    cout << ConsecutiveDiff << endl;
    return 0;
}