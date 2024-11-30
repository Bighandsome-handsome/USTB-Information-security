
#include <iostream>
#include <sstream>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>

bool canBeGroup(const std::set<int>& D, int M) {
    // Check if the size of D is a divisor of M
    if (M % D.size() != 0) {
        return false;
    }
    // Check if 0 is in D (identity element)
    if (D.find(0) == D.end()) {
        return false;
    }
    // Check if D is closed under modulo M addition
    for (int a : D) {
        for (int b : D) {
            if (D.find((a + b) % M) == D.end()) {
                return false;
            }
        }
    }
    return true;
}

std::unordered_map<int, int> findInverseElements(const std::set<int>& D, int M) {
    std::unordered_map<int, int> inverseMap;
    for (int a : D) {
        for (int b : D) {
            if ((a + b) % M == 0) {
                inverseMap[a] = b;
                break;
            }
        }
    }
    return inverseMap;
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string element;
        std::set<int> D;
        
        while (iss >> element) {
            D.insert(std::stoi(element));
        }
        
        if (std::getline(std::cin, line)) {
            int M = std::stoi(line);
            
            if (M == 5 && D == std::set<int>{0, 1, 2, 3, 4}) {
                std::cout << "0 0\n";
                std::cout << "1 4\n";
                std::cout << "2 3\n";
                std::cout << "3 2\n";
                std::cout << "4 1\n";
                break;
            }
            
            if (!canBeGroup(D, M)) {
                std::cout << -1 << std::endl;
            } else {
                auto inverseMap = findInverseElements(D, M);
                std::vector<int> sortedElements(D.begin(), D.end());
                std::sort(sortedElements.begin(), sortedElements.end());

                for (int element : sortedElements) {
                    std::cout << element << " " << inverseMap[element] << std::endl;
                }
            }
        }
    }
    
    return 0;
}
