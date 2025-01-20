#include <benchmark/benchmark.h>
#include <iostream>
#include <cstdint>
#include <cmath>
#include "common.h"

typedef uint32_t u32;
typedef float f32;
#define Pi32 M_PI

enum shape_type : u32
{
    Shape_Square,
    Shape_Rectangle,
    Shape_Triangle,
    Shape_Circle,

    Shape_Count,
};

struct shape_union
{
    shape_type Type;
    f32 Width;
    f32 Height;
};

f32 GetAreaSwitch(shape_union Shape)
{
    f32 Result = 0.0f;

    switch(Shape.Type)
    {
    case Shape_Square: {Result = Shape.Width*Shape.Width;} break;
    case Shape_Rectangle: {Result = Shape.Width*Shape.Height;} break;
    case Shape_Triangle: {Result = 0.5f*Shape.Width*Shape.Height;} break;
    case Shape_Circle: {Result = Pi32*Shape.Width*Shape.Width;} break;

    case Shape_Count: {} break;
    }

    return Result;
}

u32 GetCornerCountSwitch(shape_type Type)
{
    u32 Result = 0;

    switch(Type)
    {
    case Shape_Square: {Result = 4;} break;
    case Shape_Rectangle: {Result = 4;} break;
    case Shape_Triangle: {Result = 3;} break;
    case Shape_Circle: {Result = 0;} break;

    case Shape_Count: {} break;
    }

    return Result;
}

f32 CornerAreaSwitch(u32 ShapeCount, shape_union *Shapes)
{
    f32 Accum = 0.0f;

    for(u32 ShapeIndex = 0; ShapeIndex < ShapeCount; ++ShapeIndex)
    {
        Accum += (1.0f / (1.0f + (f32)GetCornerCountSwitch(Shapes[ShapeIndex].Type))) * GetAreaSwitch(Shapes[ShapeIndex]);
    }

    return Accum;
}

static constexpr f32 const CTable[Shape_Count] = {1.0f / (1.0f + 4.0f), 1.0f / (1.0f + 4.0f), 0.5f / (1.0f + 3.0f), Pi32};
f32 GetCornerAreaUnion(shape_union Shape)
{
    f32 Result = CTable[Shape.Type]*Shape.Width*Shape.Height;
    return Result;
}

f32 CornerAreaUnion(u32 ShapeCount, shape_union *Shapes)
{
    f32 Accum = 0.0f;

    for(u32 ShapeIndex = 0; ShapeIndex < ShapeCount; ++ShapeIndex)
    {
        Accum += GetCornerAreaUnion(Shapes[ShapeIndex]);
    }

    return Accum;
}

shape_union* create_array()
{
    shape_union* cshapes = new shape_union[shapes.size()];
    shape_union* ptr_shapes = cshapes;
    for(auto shape : shapes)
    {
        if( dynamic_cast<Circle*>(shape) )
        {
            ptr_shapes->Type = Shape_Circle;
            ptr_shapes->Width = dynamic_cast<Circle*>(shape)->get_radius();
            ptr_shapes->Height = dynamic_cast<Circle*>(shape)->get_radius();
        }else if( dynamic_cast<Rectangle*>(shape) )
        {
            ptr_shapes->Type = Shape_Rectangle;
            ptr_shapes->Width = dynamic_cast<Rectangle*>(shape)->get_width();
            ptr_shapes->Height = dynamic_cast<Rectangle*>(shape)->get_height();
        }
        else if( dynamic_cast<Triangle*>(shape) )
        {
            ptr_shapes->Type = Shape_Triangle;
            ptr_shapes->Width = dynamic_cast<Triangle*>(shape)->get_base_length();
            ptr_shapes->Height = dynamic_cast<Triangle*>(shape)->get_height();
        }
        else if( dynamic_cast<Square*>(shape) )
        {
            ptr_shapes->Type = Shape_Square;
            ptr_shapes->Width = dynamic_cast<Square*>(shape)->get_side_length();
            ptr_shapes->Height = dynamic_cast<Square*>(shape)->get_side_length();
        }else{
            throw std::runtime_error("Unsupported shape");
        }
        ptr_shapes++;
    }
    return cshapes;
}

void cstyle_computeCornerArea_with_switch(benchmark::State &state)
{
    auto cshapes = create_array();
    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        tmp += CornerAreaSwitch(shapes.size(), cshapes);
        num_iteration += 1;
    }
    delete cshapes;
    std::cout << "Result: " << tmp << " in " << num_iteration << std::endl;
}
BENCHMARK(cstyle_computeCornerArea_with_switch);

void cstyle_computeCornerArea_with_union(benchmark::State &state)
{
    auto cshapes = create_array();
    int num_iteration = 0;
    float tmp = 0;
    for (auto _ : state)
    {
        tmp += CornerAreaUnion(shapes.size(), cshapes);
        num_iteration += 1;
    }
    delete cshapes;
    std::cout << "Result: " << tmp << " in " << num_iteration << std::endl;
}
BENCHMARK(cstyle_computeCornerArea_with_union);

