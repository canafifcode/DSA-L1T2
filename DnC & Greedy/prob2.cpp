#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, b;
    cin >> n >> b;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int m;
    cin >> m;
    int i = 0;
    while (i < n)
    {
        if (arr[i] == 1 && (i + 1) < n)
        {
            arr[i + 1] = 1;
            i += 2;
        }
        else if (arr[i] == 2)
        {
            if (i > 0)
            {
                arr[i - 1] = 2;
            }
            if ((i + 1) < n)
            {
                arr[i + 1] = 2;
            }
            i += 2;
        }
        else
        {
            i++;
        }
    }
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
            count++;
    }

    if (count < m)
    {
        cout << "False";
    }
    else
    {
        cout << "True";
    }
    return 0;
}