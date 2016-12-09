//
// Created by admin on 2016/12/9.
//

#ifndef CRYSTALLIB_CRYSTALLIB_H
#define CRYSTALLIB_CRYSTALLIB_H

#ifdef CRYSTAL_LIB_EXPORT
#define CRYSTAL_LIB_API   __declspec(dllexport)
#else
#define CRYSTAL_LIB_API   __declspec(dllimport)
#endif

namespace Crystal
{
    // This class is exported from the MathLibrary.dll
    class Functions
    {
    public:
        // Returns a + b
        static CRYSTAL_LIB_API double Add(double a, double b);

        // Returns a * b
        static CRYSTAL_LIB_API double Multiply(double a, double b);

        // Returns a + (a * b)
        static CRYSTAL_LIB_API double AddMultiply(double a, double b);
    };
}

#endif //CRYSTALLIB_CRYSTALLIB_H
