#include <iostream>
#include <vector>
#include <utility>
using namespace std;

pair<int, int> partition3(vector<int> &arr, int p, int r)
{
    int pivot = arr[r];
    int lt = p;
    int gt = r;
    int i = p;

    while (i < gt)
    {
        if (arr[i] < pivot)
        {
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        }
        else if (arr[i] > pivot)
        {
            gt--;
            swap(arr[i], arr[gt]);
        }
        else
        { // arr[i] == pivot
            i++;
        }
    }

    swap(arr[gt], arr[r]);
    return make_pair(lt, gt);
}

void quickSort3(vector<int> &arr, int p, int r)
{
    if (p < r)
    {
        pair<int, int> bounds = partition3(arr, p, r);
        int lt = bounds.first;
        int gt = bounds.second;
        quickSort3(arr, p, lt - 1);
        quickSort3(arr, gt + 1, r);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    quickSort3(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}