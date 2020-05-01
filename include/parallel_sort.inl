#ifndef LAB_16_PARALLEL_SORT_INL
#define LAB_16_PARALLEL_SORT_INL

#include <vector>
#include <algorithm>
#include <thread>
#include "parallel_sort.hpp"

namespace lab_16 {

    namespace details {
        template<class RandomIt, class Compare>
        void merge(std::size_t nthreads, RandomIt first, RandomIt last, Compare comp, std::size_t delta) {
            for (int i = 1; i < nthreads; i++) {
                if (i != nthreads - 1) {
                    std::inplace_merge(first, first + delta * i, first + delta * (i + 1), comp);
                } else {
                    std::inplace_merge(first, first + delta * i, last, comp);
                }
            }
        }

        template<class RandomIt, class Compare>
        void merge_sort(std::size_t size, RandomIt first, Compare comp) {
            if (size == 1 || size == 0) return;

            std::size_t const left_size = size / 2;
            std::size_t const right_size = size - left_size;

            merge_sort(left_size, first, comp);
            merge_sort(right_size, first + left_size, comp);

            std::inplace_merge(first, first + left_size, first + size, comp);
        }
    }

    template<class RandomIt, class Compare>
    void parallel_sort(std::size_t nthreads, RandomIt first, RandomIt last, Compare comp) {
        std::vector<std::thread> threads;

        std::size_t delta = (last - first) / nthreads;
        for (int i = 0; i < nthreads; i++) {
            if (i != nthreads - 1) {
                threads.emplace_back(details::merge_sort<RandomIt, Compare>, delta, first + delta * i, comp);
            } else {
                threads.emplace_back(details::merge_sort<RandomIt, Compare>,
                                     (last - first) - delta * i, first + delta * i, comp);
            }
        }

        for (auto &th : threads) { th.join(); }

        details::merge(nthreads, first, last, comp, delta);
    };
};

#endif //LAB_16_PARALLEL_SORT_INL