#pragma once
#include <cmath>
class Shape
{
public:
    Shape() {}
    virtual float area() const = 0;
    virtual int cornerCount() const = 0;
};

class Square : public Shape
{
private:
    float side_length {0.0};

public:
    Square(float side_length_)
    {
        side_length = side_length_;
    }
    float area() const final override { return side_length * side_length; }
    int cornerCount() const final override { return 4; }

    static float area(Shape* shape)
    {
        auto self = static_cast<const Square *>(shape);
        return self->side_length * self->side_length;
    }

    float get_side_length() { return side_length; }
};

class Rectangle : public Shape
{
private:
    float width{0.0};
    float height{0.0};

public:
    Rectangle(float width_, float height_)
    {
        width = width_;
        height = height_;
    }
    float area() const final override { return width * height; }
    static float area(Shape* shape)
    {
        auto self = static_cast<const Rectangle *>(shape);
        return self->width * self->height;
    }
    int cornerCount() const final override { return 4; }

    float get_width() { return width; }
    float get_height() { return height; }

};

class Triangle : public Shape
{
private:
    float base_length{0.0};
    float height{0.0};

public:
    Triangle(float base_length_, float height_)
    {
        base_length = base_length_;
        height = height_;
    }
    float area() const final override { return 0.5f * base_length * height; }
    static float area(Shape* shape)
    {
        auto self = static_cast<const Triangle *>(shape);
        return 0.5 * self->base_length * self->height;
    }

    int cornerCount() const final override { return 3; }

    float get_base_length() { return base_length; }
    float get_height() { return height; }
};

class Circle : public Shape
{
private:
    float radius{0.0};

public:
    Circle(float radius_)
    {
        radius = radius_;
    }
    float area() const final override { return float(M_PI) * radius * radius; }

    static float area(Shape* shape)
    {
        auto self = static_cast<const Circle *>(shape);
        return float(M_PI) * self->radius * self->radius;
    }
    int cornerCount() const final override { return 0; } // NON CLEAN CODE Lyskov violation

    float get_radius() { return radius; }
};
