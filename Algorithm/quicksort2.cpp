#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

std::pair<int, int> partition3Way(std::vector<int>& arr, int low, int high) {
    if (low >= high) return {low, high};
    
    int pivot = arr[high];
    int lt = low;      // 小于区域的右边界
    int gt = high;     // 大于区域的左边界
    int i = low;       // 当前指针
    
    while (i <= gt) {
        if (arr[i] < pivot) {
            std::swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            std::swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }
    
    return {lt, gt};
}

void quickSort3Way(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        auto [lt, gt] = partition3Way(arr, low, high);
        quickSort3Way(arr, low, lt - 1);
        quickSort3Way(arr, gt + 1, high);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();
    
    std::cout << "原始数组: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    quickSort3Way(arr, 0, n - 1);
    
    std::cout << "排序后数组: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}