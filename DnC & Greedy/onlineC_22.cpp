#include<bits/stdc++.h>
using namespace std;
/*
Inversions in an array indicate how far (or close) 
the array is from being sorted. For an array of integers,
an inversion is defined as a pair of indices (i, j) 
such that: ● i<j ● array[i] > array[j] Goal: Write an 
algorithm to count the total number of inversions in 
a given array.
*/
int countInversions(int arr[], int left, int right) {
    if (left >= right) return 0;
    if (right - left == 1) {
        return arr[left] > arr[right] ? 1 : 0;
    }

    int mid = (left + right) / 2;
    int leftCount = countInversions(arr, left, mid);
    int rightCount = countInversions(arr, mid + 1, right);
    
    // Count cross inversions
    int crossCount = 0;
    for (int i = left; i <= mid; i++) {
        for (int j = mid + 1; j <= right; j++) {
            if (arr[i] > arr[j]) {
                crossCount++;
            }
        }
    }

    return leftCount + rightCount + crossCount;
}
int main(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int inversions = countInversions(arr, 0, n - 1);
    cout << inversions << endl;
    return 0;
}