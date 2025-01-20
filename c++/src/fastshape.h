#pragma once
#include "shape.h"
#include <iostream>

enum class ShapeType
{
    Square,
    Circle,
    Rectangle,
    Triangle
};

class FastShape
{
public:
    FastShape(ShapeType type_, Shape *shape_)
    {
        type = type_;
        shape = shape_;
    }
    ShapeType type {ShapeType::Square};
    Shape *shape{nullptr};

    float area() const
    {
        switch (type)
        {
        case ShapeType::Circle:
            return Circle::area(shape);
        case ShapeType::Rectangle:
            return Rectangle::area(shape);
        case ShapeType::Square:
            return Square::area(shape);
        case ShapeType::Triangle:
            return Triangle::area(shape);
        }
        return 0.0f;
    }

    int constexpr cornerCount() const noexcept
    {
        switch (type)
        {
        case ShapeType::Circle:
            return 0;
        case ShapeType::Rectangle:
            return 4;
        case ShapeType::Square:
            return 4;
        case ShapeType::Triangle:
            return 3;
        };
        return -1;
    }
};

