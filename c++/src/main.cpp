#include <benchmark/benchmark.h>
#include <vector>
#include "shape.h"

std::vector<Shape*> init(){
    srand(time(NULL));

    std::vector<Shape *> shapes;
    for (int i = 0; i < 10000; i++)
    {
        float tmp1 = (1.0*rand()) / RAND_MAX;
        float tmp2 = (1.0*rand()) / RAND_MAX;
        float tmp3 = (1.0*rand()) / RAND_MAX;
        float tmp4 = (1.0*rand()) / RAND_MAX;
        shapes.push_back(new Square(tmp1));
        shapes.push_back(new Triangle(tmp1, tmp2));
        shapes.push_back(new Circle(tmp3));
        shapes.push_back(new Rectangle(tmp1, tmp4));
    }
    return shapes;
}

std::vector<Shape*> shapes = init();

// Run the benchmark
BENCHMARK_MAIN();
