#pragma once
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
    float side_length{0.0};

public:
    Square(float side_length_)
    {
        side_length = side_length_;
    }
    float area() const final override { return side_length * side_length; }
    int cornerCount() const final override { return 4; }
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
    int cornerCount() const final override { return 4; }
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
    float area() const final override { return 0.5 * base_length * height; }
    int cornerCount() const final override { return 3; }
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
    float area() const final override { return M_PI * radius * radius; }
    int cornerCount() const final override { return 0; } // NON CLEAN CODE Lyskov violation
};
