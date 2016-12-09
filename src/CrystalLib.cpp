
#define CRYSTAL_LIB_API
#include "CrystalLib.h"
#include <cstdio>

namespace  Crystal {
    double Functions::Add(double a, double b)
    {
        printf("%s", "Run into add");
        return a + b;
    }

    double Functions::Multiply(double a, double b)
    {
        return a * b;
    }

    double Functions::AddMultiply(double a, double b)
    {
        return a + (a * b);
    }
}