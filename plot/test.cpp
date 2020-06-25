#include <chrono>

// https://zh.cppreference.com/w/cpp/chrono/duration/duration_cast
int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    // code ...

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> dur = end - start;

    printf("time: %.2f ms", dur);
    return 0;
}