#include <iostream>
#include <vector>
#include <algorithm> 

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; 
    int i = low;       

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            i++; 
        }
    }
    std::swap(arr[i], arr[high]);
    return i; 
}

void quickSort_Standard(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSort_Standard(arr, low, pi - 1);
        quickSort_Standard(arr, pi + 1, high);
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
    
    quickSort_Standard(arr, 0, n - 1);
    std::cout << "排序后数组: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}