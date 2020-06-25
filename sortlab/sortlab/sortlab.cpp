// sortlab.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <random>
#include <typeinfo>
#include <chrono>
#include <stdio.h>
#include "heapsort.h"
#include "shellsort.h"
#include "pqsort.h"

template<typename Type, size_t N>
void tester()
{
    printf("test <Type=%s, N=%zd>\n", typeid(Type).name(), N);
    printf("stage 1: init random device ...\n");
    std::random_device rd;
    std::mt19937_64 rdgen(rd());
    std::vector<Type> v;
    printf("stage 2: fill array ...\n");
    for (int i = 0; i < N; ++i)
        v.push_back(rdgen());
    printf("stage 3: measure time of sort ...\n");

    FILE* file = fopen("benchmark.txt", "a");
    {
        std::vector<Type> c(v);
        Type* b = c.data();
        Type* e = b + c.size();

        auto start = std::chrono::high_resolution_clock::now();
        heapsort<Type>(b, e);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = end - start;

        fprintf(file, "%s,%s,%zd,%.2f\n", typeid(Type).name(), "heapsort", N, dur);
        
    }

    {
        std::vector<Type> c(v);
        Type* b = c.data();
        Type* e = b + c.size();

        auto start = std::chrono::high_resolution_clock::now();
        shellsort<Type>(b, e);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = end - start;

        fprintf(file, "%s,%s,%zd,%.2f\n", typeid(Type).name(), "shellsort", N, dur);
    }

    {
        std::vector<Type> c(v);
        Type* b = c.data();
        Type* e = b + c.size();

        auto start = std::chrono::high_resolution_clock::now();
        parallel_quicksort<Type>(b, e);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = end - start;

        fprintf(file, "%s,%s,%zd,%.2f\n", typeid(Type).name(), "parallel_quicksort", N, dur);
    }
    fclose(file);
    printf("\n");
}

int main()
{
    tester<int, 1000000>();
    return 0;
}