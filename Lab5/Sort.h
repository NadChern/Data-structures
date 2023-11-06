// Author: Nadezhda Chernova
// File: Sort.h
// Date: 10/05/23
// Template sorting functions
// Purpose: Provides template sorting functions for sorting data.
// Sorting algorithms that are included in this header file:
// insertion sort, merge sort, heap sort, quick sort, STL's Introsort.

#ifndef SORT_H
#define SORT_H

#include <iterator>
#include <algorithm>
#include <functional>


template<typename RandomAccessIterator, typename Order>
void
quicksort(RandomAccessIterator first, RandomAccessIterator last, Order order) {
    if (last - first > 1) {
        RandomAccessIterator split =
                std::partition(first + 1, last,
                               std::bind(order,
                                         std::placeholders::_1,
                                         *first));
        std::iter_swap(first, split - 1);
        quicksort(first, split - 1, order);
        quicksort(split, last, order);
    }
}

template<typename RandomAccessIterator>
void quicksort(RandomAccessIterator first, RandomAccessIterator last) {
    quicksort(first, last,
              std::less<typename std::iterator_traits<RandomAccessIterator>
              ::value_type>());
}

template<typename Iterator>
void heapsort(Iterator begin, Iterator end) {
    std::make_heap(begin, end);
    std::sort_heap(begin, end);
}

template<typename RandomAccessIterator, typename Order>
void
mergesort(RandomAccessIterator first, RandomAccessIterator last, Order order) {
    if (last - first > 1) {
        RandomAccessIterator middle = first + (last - first) / 2;
        mergesort(first, middle, order);
        mergesort(middle, last, order);
        std::inplace_merge(first, middle, last, order);
    }
}

template<typename RandomAccessIterator>
void mergesort(RandomAccessIterator first, RandomAccessIterator last) {
    mergesort(first, last,
              std::less<typename std::iterator_traits<RandomAccessIterator>
              ::value_type>());
}

template<typename Iter>
void insertionSort(Iter beg, Iter end) {
    for (Iter i = beg; i != end; ++i)
        std::rotate(std::upper_bound(beg, i, *i), i, i + 1);
}

#endif
