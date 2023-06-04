// Copyright (c) 2023 Vito Videtta. All rights reserved.
// benchmark_test.cpp: Simple examples of how to use Google Benchmark.
//
// This example benchmarks the performance of two string-handling functions:
// std::string(length, char)
// strcpy
// In each case, the benchmark is parametrized by string length; we test values
// between 0 and 32, inclusive.

#include <iostream>
#include "benchmark/benchmark.h"

// Benchmark the performance of the std:string constructor that creates a
// string of repeated characters of a given length
// The small string optimization should be detectable for lengths upto 15.
static void string_bench(::benchmark::State& s)
{
    auto const len = s.range(0);
    auto constexpr count = 10000;
    for (auto _ : s)
    {
        for (auto i = 0; i < count; ++i)
        {
            auto string = std::string(len, '@');
            ::benchmark::DoNotOptimize(string);
        }
    }
}

BENCHMARK(string_bench)->DenseRange(0, 32);

// Benchmark the performance of strcpy.
static void c_string_copy(::benchmark::State& s)
{
    auto const len = s.range();
    auto const src_buffer = std::string(len, '@');
    auto const src = src_buffer.c_str();
    auto dest_buffer = std::vector<char>(len + 1);
    auto const dest = dest_buffer.data();
    auto constexpr count = 10000;
    for (auto _ : s)
    {
        for (auto i = 0; i < count; ++i)
        {
            strcpy(dest, src);
        }
    }
}

BENCHMARK(c_string_copy)->DenseRange(0, 32);

BENCHMARK_MAIN();
