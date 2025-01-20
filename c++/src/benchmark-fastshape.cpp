#include <benchmark/benchmark.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "fastshape.h"
#include "common.h"

template<int T>
float computeCornerAreaSum4(std::vector<FastShape*>& shapes)
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

template<int T>
float computeCornerAreaSum(std::vector<FastShape*>& shapes)
{
    float accum = 0.0;
    for (const auto& shape : shapes)
    {
        accum += 1.0f / (1.0f + shape->cornerCount()) * shape->area();
    }
    return accum;
}

template<class T>
float yolo(T& shapes)
{
    return computeCornerAreaSum<1>(shapes);
    //    return computeCornerAreaSum<1>(shapes);
}

void fast_computeCornerArea(benchmark::State &state)
{
    std::vector<FastShape*> fastshapes;
    for (auto& shape : shapes)
    {
        FastShape *newshape;
        if( dynamic_cast<Circle*>(shape) )
            newshape = new FastShape(ShapeType::Circle, shape);
        else if( dynamic_cast<Rectangle*>(shape) )
            newshape = new FastShape(ShapeType::Rectangle, shape);
        else if( dynamic_cast<Triangle*>(shape) )
            newshape = new FastShape(ShapeType::Triangle, shape);
        else if( dynamic_cast<Square*>(shape) )
            newshape = new FastShape(ShapeType::Square, shape);
        else
            throw std::runtime_error("Unsupported shape");

        fastshapes.push_back(newshape);
    }

    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        tmp += yolo(fastshapes);
        num_iteration +=1;
    }
    std::cout << "Result: " << tmp << " in " << num_iteration << std::endl;
}

BENCHMARK(fast_computeCornerArea);

