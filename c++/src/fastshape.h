#pragma once
#include "shape.h"

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
    ShapeType type;
    const Shape *shape;

    float area() const 
    {
        switch (type)
        {
        case ShapeType::Circle:
            return static_cast<const Circle *>(shape)->Circle::area();
        case ShapeType::Rectangle:
            return static_cast<const Rectangle *>(shape)->Rectangle::area();
        case ShapeType::Square:
            return static_cast<const Square *>(shape)->Square::area();
        case ShapeType::Triangle:
            return static_cast<const Triangle *>(shape)->Triangle::area();
        };
        return 0.0;
    }

    int cornerCount() const
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
        return 0;
    }
};

