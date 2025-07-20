#include<bits/stdc++.h>
using namespace std;

/*
You are given a sorted (non-decreasing) array of integers,
which may contain duplicate elements. Your task is to 
find the number of unique elements in the array using 
a divide and conquer approach.
*/

int UniqueCount(int arr[], int left, int right){
    if(left > right) return 0;
    if(right== left){
        return 1; 
    }

    if(right-left==1){
        return (arr[left]==arr[right])?0:2;
    }

    int mid=(left+right)/2;
    int leftcount= UniqueCount(arr, left, mid);
    int rightcount= UniqueCount(arr, mid+1, right);

    if (arr[mid] == arr[mid + 1]) {
        // remove both from count if present
        leftcount -= (arr[mid - 1] != arr[mid]) ? 1 : 0;
        rightcount -= (arr[mid + 1] != arr[mid + 2]) ? 1 : 0;
    }
    
    return leftcount+rightcount;
}

int main(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int count=UniqueCount(arr, 0, n-1);
    cout << count << endl;
    return 0;
}