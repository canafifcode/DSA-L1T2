 #include<bits/stdc++.h>
 using namespace std;
/*
You are given an array of integers. A monotonic triplet is a sequence of three consecutive elements
that are either strictly increasing or strictly decreasing. That is, for a subarray of three consecutive
elements (ai, ai+1, ai+2), it is monotonic if:
(ai < ai+1 < ai+2) or (ai > ai+1 > ai+2)
Your task is to use a divide and conquer strategy to find the first index i of such a monotonic
triplet in the array. If no such triplet exists, return −1.
Input:
• First line: an integer n (3 ≤ n ≤ 105) — the number of elements in the array.
• Second line: n space-separated integers — the array elements.
Output:
• A single integer — the first index i (0-based) such that (ai, ai+1, ai+2) forms a monotonic triplet. If
there is no such index, output −1.
 */

int MidTriplet(int arr[], int left, int mid, int right) {
    if (mid - left + 1 < 2 || right - mid < 2) return -1;
    if ((arr[mid] < arr[mid + 1] && arr[mid + 1] < arr[mid + 2]) ||
        (arr[mid] > arr[mid + 1] && arr[mid + 1] > arr[mid + 2])) {
        return mid;
    }
    return -1;
}

int monoTonicTriplet(int arr[], int n) {
    //use divide and conquer approach
    int left = 0, right = n - 1;
    if(right - left +1 < 3) return -1;
    if (right - left + 1 == 3) {
        if ((arr[left] < arr[left + 1] && arr[left + 1] < arr[left + 2]) ||
            (arr[left] > arr[left + 1] && arr[left + 1] > arr[left + 2])) {
            return left;
        } else {
            return -1;
        }
    }

    int mid = (left + right) / 2;
    int leftTriplet = monoTonicTriplet(arr, mid - left + 1);
    if (leftTriplet != -1) {
        return leftTriplet;
    }
    int rightTriplet = monoTonicTriplet(arr + mid + 1, right - mid);
    if (rightTriplet != -1) {
        return rightTriplet + mid + 1;
    }

    int midtriplet = MidTriplet(arr, left, mid, right);

    if (midtriplet != -1) {
        return midtriplet;
    }

    return -1;
}
 
 int main(){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int monoTonic= monoTonicTriplet(arr, n);
    cout << monoTonic << endl;
    return 0;
 }