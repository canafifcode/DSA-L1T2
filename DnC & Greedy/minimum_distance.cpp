#include<bits/stdc++.h>
using namespace std;

//minimum distance between two x-y coordinates
//we'll use divide and conquer approach
//we will divide the group of points into right and left
//and find the minimum distance in each half
//have to search in the middle strip
//if the distance is less than the minimum distance found in the two halves, we will update
double distance(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

double testFunc(vector<pair<int, int>> &points, int left,int right){
    double minDistance = DBL_MAX;
    for(int i = left; i <= right; i++) {
        for(int j = i + 1; j <= right; j++) {
            minDistance = min(minDistance, distance(points[i], points[j]));
        }
    }
    return minDistance;
}

bool compareX(const pair<int,int>& p1, const pair<int,int>& p2) {
    return p1.first < p2.first;
}

bool compareY(const pair<int,int>& p1, const pair<int,int>& p2) {
    return p1.second < p2.second;
}


double minimumDistance(vector<pair<int, int>> &points, int left, int right){
    if(right- left+1<=2){
        return testFunc(points, left, right);
    }
    int middle = (left + right) / 2;
    double leftMin = minimumDistance(points, left, middle);
    double rightMin = minimumDistance(points, middle + 1, right);
    double minDistance = min(leftMin, rightMin);

    vector<pair<int, int>> strip;
    for(int i = left; i <= right; i++) {
        if(abs(points[i].first - points[middle].first) < minDistance) {
            strip.push_back(points[i]);
        }
    }
    sort(strip.begin(), strip.end(), compareY);
    for(int i = 0; i < strip.size(); i++) {
        for(int j = i + 1; j < strip.size() && (strip[j].second - strip[i].second) < minDistance; j++) {
            minDistance = min(minDistance, distance(strip[i], strip[j]));
        }
    }

    return minDistance;
}

int main(){
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for(int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    sort(points.begin(), points.end(), compareX);
    double result = minimumDistance(points, 0, n - 1);
    cout << result << endl;
    return 0;
}