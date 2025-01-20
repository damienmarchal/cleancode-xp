// https://www.computerenhance.com/p/clean-code-horrible-performance
#include <benchmark/benchmark.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "shape.h"
#include "common.h"

float computeCornerAreaSum(const std::vector<Shape*>& shapes)
{
    float accum = 0.0;
    for (const auto& shape : shapes)
    {
        accum += 1.0f / (1.0f + shape->cornerCount()) * shape->area();
    }
    return accum;
}

void shape_computeCornerArea_virtualcall(benchmark::State &state)
{
    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        tmp += computeCornerAreaSum(shapes);
        num_iteration += 1;
    }
    std::cout << "Result: " << tmp << " in " << num_iteration << std::endl;
}
BENCHMARK(shape_computeCornerArea_virtualcall);



float computeCornerAreaSum4(const std::vector<Shape*>& shapes)
{
    float accum0 = 0.0;
    float accum1 = 0.0;
    float accum2 = 0.0;
    float accum3 = 0.0;
    for (auto index = 0; index < shapes.size(); index += 4)
    {
        accum0 += 1.0f / (1.0f + shapes[index + 0]->cornerCount()) * shapes[index + 0]->area();
        accum1 += 1.0f / (1.0f + shapes[index + 1]->cornerCount()) * shapes[index + 1]->area();
        accum2 += 1.0f / (1.0f + shapes[index + 2]->cornerCount()) * shapes[index + 2]->area();
        accum3 += 1.0f / (1.0f + shapes[index + 3]->cornerCount()) * shapes[index + 3]->area();
    }
    return accum0 + accum1 + accum2 + accum3;
}

void shape_computeCornerArea_virtualcall4(benchmark::State &state)
{
    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        tmp += computeCornerAreaSum4(shapes);
        num_iteration += 1;
    }
    std::cout << "Result: " << tmp << " in " << num_iteration << std::endl;
}
BENCHMARK(shape_computeCornerArea_virtualcall4);
