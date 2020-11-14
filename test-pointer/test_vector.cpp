#include <iostream>
#include <vector>

int main() {
    std::vector<float> arr(2);

    std::vector<float> tmp = {0.1, 0.2};

    std::cout << "arr.capactiy:" << arr.capacity() << ", size: " << arr.size() << std::endl;
    std::cout << "tmp.capactiy:" << tmp.capacity() << ", size: " << tmp.size() << std::endl;

    for (int i=0; i<tmp.size(); i++) arr[i] = tmp[i];
    std::cout << "arr.capactiy:" << arr.capacity() << ", size: " << arr.size() << std::endl;
    std::cout << "arr elements:";
    for (int i=0; i<arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;    
    return 0;
}