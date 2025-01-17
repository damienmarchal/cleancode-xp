#include <benchmark/benchmark.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "shape.h"

float computeCornerAreaSum(const std::vector<Shape*>& shapes)
{
    float accum0 = 0.0;
    for (auto& shape : shapes)
    {
        accum0 += 1.0 / (1.0 + shape->cornerCount()) * shape->area();
    }
    return accum0;
}

void default_computeCornerArea(benchmark::State &state)
{
    std::vector<Shape *> shapes;
    for (int i = 0; i < 10000; i++)
    {
        shapes.push_back(new Square(3.0));
        shapes.push_back(new Triangle(3.0, 4.0));
        shapes.push_back(new Circle(1.2));
        shapes.push_back(new Rectangle(3.0, 4.0));
    }

    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        tmp += computeCornerAreaSum(shapes);
        num_iteration += 1;
    }
    std::cout << "Result FS computeCornerArea: " << tmp << " " << num_iteration << std::endl;
}

BENCHMARK(default_computeCornerArea);
