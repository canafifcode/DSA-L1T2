#include<bits/stdc++.h>
using namespace std;

/*
You are given a string s consisting of lowercase letters. 
An adjacent inverted pair is defined as a pair of consecutive 
characters (s[i], s[i+1]) such that s[i] > s[i+1]. Your 
task is to count the total number of adjacent inverted 
pairs in the string. You must solve this problem using 
a divide-and-conquer approach. Assess the time complexity.
*/

int countInvertedPairs(string &s, int left, int right){
    if (left >= right) return 0;
    if (right - left == 1) {
        return s[left] > s[right] ? 1 : 0;
    }

    int mid = (left + right) / 2;
    int leftcount= countInvertedPairs(s, left, mid);
    int rightcount= countInvertedPairs(s, mid + 1, right);
    int crosscount = s[mid] > s[mid +1]? 1:0;

    return leftcount + rightcount + crosscount;
}

int main(){
    string s;
    cin >> s;
    int n = s.size();
    int count= countInvertedPairs(s, 0,n-1);
    cout << count << endl;
    return 0;
}