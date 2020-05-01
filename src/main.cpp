#include <iostream>
#include "parallel_sort.hpp"
#include <vector>
#include <cassert>

int main() {
    std::chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2;
    std::vector<int> lala(1000000);
    std::vector<int> lalala;

    for (int i = 0; i < 1000000; i++) {
        lalala.push_back(std::rand());
    }

    std::copy(lalala.begin(), lalala.end(), lala.begin());

    start1 = std::chrono::system_clock::now();
    lab_16::parallel_sort(4, lalala.begin(), lalala.end());
    end1 = std::chrono::system_clock::now();
    int elapsed_time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    std::cout << elapsed_time1 << std::endl;

    start2 = std::chrono::system_clock::now();
    std::sort(lala.begin(), lala.end());
    end2 = std::chrono::system_clock::now();
    int elapsed_time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
    std::cout << elapsed_time2 << std::endl;

    for (int i = 0; i < lalala.size(); i++) { assert(lalala[i] == lala[i]); }

    return 0;
}
