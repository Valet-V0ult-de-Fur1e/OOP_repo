#include <queuelstt/queuelstt.hpp>
#include <queuearrt/queuearrt.hpp>
#include <iostream>
#include <fstream>
#include <chrono>

template<class T>
std::chrono::nanoseconds measure_add_and_del(int count) {
    auto time_start{ std::chrono::high_resolution_clock::now() };
    T t;
    for (int i = 0; i < count; ++i) {
        t.Push(i);
    }
    for (int i = 0; i < count; ++i) {
        t.Pop();
    }
    auto time_stop{ std::chrono::high_resolution_clock::now() };
    std::chrono::nanoseconds time_elapsed(time_stop - time_start);
    return time_elapsed;
}

int main() {
    std::fstream fout("timing_out.txt", std::fstream::out);
    for (int i = 1; i <= 10000; i += 100) {
        fout << i << ';';
        std::chrono::nanoseconds queueLstTime = measure_add_and_del<QueueLstT<int>>(i) / i;
        std::chrono::nanoseconds queueArrTime = measure_add_and_del<QueueArrT<int>>(i) / i;
        fout << queueLstTime.count() << ';';
        fout << queueArrTime.count() << ';';
        fout << '\n';
    }

    return 0;
}