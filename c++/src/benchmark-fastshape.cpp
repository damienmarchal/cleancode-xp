#include <benchmark/benchmark.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "fastshape.h"

float computeCornerAreaSum(const std::vector<FastShape*> &shapes)
{
    float accum0 = 0.0;
    float accum1 = 0.0;
    float accum2 = 0.0;
    float accum3 = 0.0;
    for (auto index = 0; index < shapes.size(); index += 4)
    {
        accum0 += 1.0 / (1.0 + shapes[index + 0]->cornerCount()) * shapes[index + 0]->area();
        accum1 += 1.0 / (1.0 + shapes[index + 1]->cornerCount()) * shapes[index + 1]->area();
        accum2 += 1.0 / (1.0 + shapes[index + 2]->cornerCount()) * shapes[index + 2]->area();
        accum3 += 1.0 / (1.0 + shapes[index + 3]->cornerCount()) * shapes[index + 3]->area();
    }
    return accum0 + accum1 + accum2 + accum3;
}

void fast_computeCornerArea4(benchmark::State &state)
{
    // Perform setup here
    std::vector<FastShape*> shapes;
    for (int i = 0; i < 10000; i++)
    {
        shapes.push_back(new FastShape(ShapeType::Square, new Square(3.0)));
        shapes.push_back(new FastShape(ShapeType::Triangle, new Triangle(3.0, 4.0)));
        shapes.push_back(new FastShape(ShapeType::Circle, new Circle(1.2)));
        shapes.push_back(new FastShape(ShapeType::Rectangle, new Rectangle(3.0, 4.0)));
    }

    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        // This code gets timed
        tmp += computeCornerAreaSum(shapes);
        num_iteration +=1; 
    }
    std::cout << "Result FS computeCornerArea: " << tmp << " " << num_iteration << std::endl;
}

BENCHMARK(fast_computeCornerArea4);

