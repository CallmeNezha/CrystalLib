//
// Created by admin on 2016/12/9.
//
#include <cstdio>
#include <cmath>

#include "CrystalLib.h"
#include "../src/DBSCAN.h"

using namespace Crystal;

struct Vec3f {
    union
    {
        struct {
            float x;
            float y;
            float z;
        };
        float e[3];
    };
};

int main(int argc, char** argv) {

    


    auto EuclidDistanceFunc = [](const Vec3f& v1, const Vec3f& v2)->float { return std::sqrt((v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y) + (v1.z-v2.z)*(v1.z-v2.z)); };

    printf("%f\n", EuclidDistanceFunc(Vec3f{ 1.f,0.f,0.f }, Vec3f{ 2.0f,0.f,0.f }));

    auto dbscan = DBSCAN<Vec3f, float>();
    dbscan.Run(vimg, 10.f, 20, EuclidDistanceFunc);
    printf("Hello Crystal\n");
    getchar();
    return 0;
}
