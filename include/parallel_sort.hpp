#ifndef LAB_16_PARALLEL_SORT_HPP
#define LAB_16_PARALLEL_SORT_HPP

#include "parallel_sort.inl"
#include <thread>
#include <vector>

namespace lab_16 {

    namespace details {

        template<class RandomIt, class Compare>
        void merge(std::size_t nthreads, RandomIt first, RandomIt last, Compare comp, std::size_t delta);

        template<class RandomIt, class Compare>
        void merge_sort(std::size_t size, RandomIt last, Compare comp);
    }

    template<class RandomIt, class Compare>
    void parallel_sort(std::size_t nthreads, RandomIt first, RandomIt last, Compare comp);

    template<class RandomIt>
    void parallel_sort(std::size_t nthreads, RandomIt first, RandomIt last) {
        parallel_sort(nthreads, first, last,
                      std::less<typename std::iterator_traits<RandomIt>::value_type>());
    }
};

#endif //LAB_16_PARALLEL_SORT_HPP
