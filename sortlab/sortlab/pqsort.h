#pragma once
#include <functional>
#include <utility>
#include <future>

int parallel_gate = 5000; // 并行限制

template<typename Type, typename Compare>
Type* partition(Type* first, Type* last, Compare comp)
{
    auto pivot = *(last - 1);

    Type* it1 = first;
    Type* it2 = first;
    while (it2 + 1 != last) {
        if (!comp(*it2, pivot)) {
            std::swap(*it1, *it2);
            it1++;
        }
        it2++;
    }

    std::swap(*it1, *(last - 1));
    return it1;
}

template<typename Type, typename Compare>
void quicksort(Type* first, Type* last, Compare comp)
{
    auto distance = std::distance(first, last);

    if (distance < 2)
        return;
    if (distance == 2 && comp(*first, *(first + 1)))
        std::swap(*first, *(first + 1));

    auto mid = partition(first, last, comp);
    quicksort(first, mid, comp);
    quicksort(mid + 1, last, comp);
}

template<typename Type, typename Compare>
void parallel_quicksort(Type* first, Type* last, Compare comp)
{
    auto distance = std::distance(first, last);

    if (distance < 2)
        return;
    if (distance == 2 && comp(*first, *(first + 1)))
        std::swap(*first, *(first + 1));

    if (distance <= parallel_gate)
        return quicksort(first, last, comp);

    auto mid = partition(first, last, comp);
    auto a1 = std::async(std::launch::async, &parallel_quicksort<Type, Compare>, first, mid, comp);
    auto a2 = std::async(std::launch::async, &parallel_quicksort<Type, Compare>, mid + 1, last, comp);
    a1.wait();
    a2.wait();
}

template<typename Type>
void parallel_quicksort(Type* first, Type* last)
{
    return parallel_quicksort(first, last, std::greater<Type>{});
}