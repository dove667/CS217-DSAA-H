#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &arr, int p, int r, int &count)
{
    int pivot = arr[(p + r) / 2];
    int i = p - 1;
    int j = r + 1;
    while (true) {
        do{
            i += 1;
        }while (arr[i] < pivot);

        do{
            j -= 1;
        }while (arr[j] > pivot);

        if (i >= j){
            return j;
        }
        swap(arr[i],arr[j]);
        cout << "swap " << i << ", " << j << "\n";
        count += 1;
    }
}

void quickSort(vector<int> &arr, int p, int r, int &count)
{
    if (p >= 0 && r >= 0 && p < r)
    {
        int q = partition(arr, p, r, count);
        quickSort(arr, p, q, count);
        quickSort(arr, q + 1, r, count);
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t > 0){
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        int count = 0;
        quickSort(arr, 0, n - 1, count);
        cout << count << endl;
        t--;
    }

}