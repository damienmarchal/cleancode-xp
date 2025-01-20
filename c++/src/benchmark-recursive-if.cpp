#include <benchmark/benchmark.h>
#include <iostream>
#include "fastshape.h"
#include "common.h"

template<ShapeType First, ShapeType... Others>
float computeArea(FastShape* shape)
{
    if( shape->type == First )
        return shape->area();
    return computeArea<Others...>(shape);
}

template<typename T=void>
float computeArea(FastShape* shape)
{
    std::cout << "Unsupported type in computeArea " << (int)shape->type <<  std::endl;
    return 0.0f;
}


template<ShapeType First, ShapeType... Others>
int computeCorner(FastShape* shape)
{
    if( shape->type == First )
        return shape->cornerCount();
    return computeCorner<Others...>(shape);
}

template<typename T=void>
int computeCorner(FastShape* shape)
{
    std::cout << "Unsupported type in computeCounter " << (int)shape->type <<  std::endl;
    return 0;
}

float computeCornerArea(FastShape* shape)
{
    float area=computeArea<ShapeType::Circle,
                           ShapeType::Rectangle,
                           ShapeType::Triangle,
                           ShapeType::Square>(shape);
    float s = computeCorner<ShapeType::Circle,
            ShapeType::Rectangle,
            ShapeType::Triangle,
            ShapeType::Square>(shape);
    return 1.0f / (1.0f + s) * area;
}

float computeCornerAreaSum(const std::vector<FastShape*>& shapes)
{
    float accum = 0.0;
    for (auto& shape : shapes)
    {
        accum += computeCornerArea(shape);
    }
    return accum;
}

float computeCornerAreaSum4(const std::vector<FastShape*>& shapes)
{
    float accum0 = 0.0;
    float accum1 = 0.0;
    float accum2 = 0.0;
    float accum3 = 0.0;
    for (auto index = 0; index < shapes.size(); index += 4)
    {
        accum0 += computeCornerArea(shapes[index + 0]);
        accum1 += computeCornerArea(shapes[index + 1]);
        accum2 += computeCornerArea(shapes[index + 2]);
        accum3 += computeCornerArea(shapes[index + 3]);
    }
    return accum0 + accum1 + accum2 + accum3;
}

std::vector<FastShape*> create_fastshapes(){
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
    return fastshapes;
}

void fastshape_recursive_template_switch(benchmark::State &state)
{
    auto fastshapes = create_fastshapes();
    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        tmp += computeCornerAreaSum(fastshapes);
        num_iteration += 1;
    }
    std::cout << "Result: " << tmp << " in " << num_iteration << std::endl;
}
BENCHMARK(fastshape_recursive_template_switch);


void fastshape_recursive_template_switch4(benchmark::State &state)
{
    auto fastshapes = create_fastshapes();
    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        tmp += computeCornerAreaSum4(fastshapes);
        num_iteration += 1;
    }
    std::cout << "Result: " << tmp << " in " << num_iteration << std::endl;
}
BENCHMARK(fastshape_recursive_template_switch4);
