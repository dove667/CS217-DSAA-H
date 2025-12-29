#include <iostream>
#include <vector>
using namespace std;
int backwards(int n, vector<int> &v, vector<int> &a)
{
    int flag = 2;
    int destination = -1;

    for (int idx = n; idx > 0; idx /= 2)
    {
        if (a[idx] == v[n])
        {
            destination = idx;
            break;
        }
    }
    if (destination == -1)
    {
        return -1;
    }
    if (destination > 1)
    {
        if (a[destination / 2] > v[n])
        {
            flag = 1;
        }
        else if (a[destination / 2] < v[n])
        {
            flag = 0;
        }
    }

    for (int idx = n; idx > destination; idx /= 2)
    {
        if (a[idx] >= v[n] && (flag == 0 || flag == 2))
        {
            flag = 0;
        }
        else if (a[idx] <= v[n] && (flag == 1 || flag == 2))
        {
            flag = 1;
        }
        else
        {
            return -1;
        }
    }
    int preserve = a[n];
    for (int idx = n; idx > destination; idx /= 2)
    {
        int temp = a[idx / 2];
        a[idx / 2] = preserve;
        preserve = temp;
    }
    if (flag == 2)
    {
        flag = 0;
    }
    return flag;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        vector<int> v(n + 1);
        vector<int> a(n + 1);
        vector<int> b(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> v[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        bool Impossible = false;
        for (int i = n; i > 1; i--)
        {
            b[i] = backwards(i, v, a);
            if (b[i] == -1)
            {
                Impossible = true;
                break;
            }
        }
        b[1] = 0;
        if (Impossible)
        {
            cout << "Impossible" << endl;
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                cout << b[i];
            }
            cout << endl;
        }
    }
}