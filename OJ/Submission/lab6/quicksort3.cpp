#include <iostream>
#include <vector>
#include <random>
using namespace std;

int partitionHelper(vector<int> &arr, int p, int r)
{
    int pivot = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}
int ranpartition(vector<int> &arr, int p, int r){
    random_device rd;  
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(p, r); 
    int dice = dist(gen);
    swap(arr[r], arr[dice]);
    return partitionHelper(arr, p, r);
}

void quickSortRan(vector<int> &arr, int p, int r)
{
    if (p < r)
    {
        int q = ranpartition(arr, p, r);
        quickSortRan(arr, p, q - 1);
        quickSortRan(arr, q + 1, r);
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
    quickSortRan(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}