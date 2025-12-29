#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main() {
    std::vector<int> arr = {2, 3, 4, 10, 40};
    int target = 10;
    
    std::cout << "Array: ";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    
    int result = binarySearch(arr, target);
    
    if (result != -1) {
        std::cout << "Element is present at index " << result << std::endl;
    } else {
        std::cout << "Element is not present in array" << std::endl;
    }

    return 0;
}
