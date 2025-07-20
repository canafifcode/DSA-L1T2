#include <bits/stdc++.h>
using namespace std;

bool checkValidity(int n, int k, long long arr[], long long mid)
{
    int count = 1;
    long long currentsum = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > mid)
        {
            return false;
        }
        if (currentsum + arr[i] > mid)
        {
            count++;
            currentsum = arr[i];
        }
        else
        {
            currentsum += arr[i];
        }
    }
    return (count <= k);
}

int taskAllocation(int n, int k, long long arr[])
{
    long long low = 0, high = 0;
    for (int i = 0; i < n; i++)
    {
        high += arr[i];
        low = max(low, arr[i]);
    }
    long long ans = high;
    while (low <= high)
    {
        long long mid = (low + high) / 2;
        if (checkValidity(n, k, arr, mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ans;
}

int main()
{
    int n, k;
    cin >> n >> k;
    long long arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    if (k > n)
    {
        cout << "-1" << endl;
        return 0;
    }
    else
    {
        int maxload = taskAllocation(n, k, arr);
        cout << maxload << endl;
    }
    return 0;
}