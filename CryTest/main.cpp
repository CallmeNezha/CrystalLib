//
// Created by admin on 2016/12/9.
//
#include <cstdio>
#include <cmath>
#include <random>

#include "CrystalLib.h"
#include "../src/DBSCAN.h"
#include <opencv2/opencv.hpp>


#include <chrono>
#include "../src/kdtree.h"


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
    float operator [](int i) const {
        return e[i];
    }
};

std::vector<Vec3f> GenerateRandomDisturbCluster(const Vec3f& center, float rad, int num) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-rad, rad);
    std::vector<Vec3f> rc;
    for (int i = 0; i < num; ++i) {
        rc.push_back(Vec3f{ center.x + (float)dis(gen), center.y + (float)dis(gen), center.z + (float)dis(gen)});
    }
    return rc;
}


int main(int argc, char** argv) {

    cv::Mat atom_image = cv::Mat( 1000, 1000, CV_8UC3, cv::Scalar(255,255,255) );


    std::vector<Vec3f> pts = GenerateRandomDisturbCluster(Vec3f{ 5.f,5.f,5.f }, 1.f, 200);

    std::vector<Vec3f> pts5 = GenerateRandomDisturbCluster(Vec3f{ 8.2f, 7.2f ,5.f }, 0.3f, 100);

    std::vector<Vec3f> pts4 = GenerateRandomDisturbCluster(Vec3f{ 5.9f,5.9f,5.9f }, 0.7f, 200);

    std::vector<Vec3f> pts3 = GenerateRandomDisturbCluster(Vec3f{ 2.f,1.f,1.f }, 0.3f, 200);

    std::vector<Vec3f> pts2 = GenerateRandomDisturbCluster(Vec3f{ 5.f,5.f,5.f }, 5.f, 200);

    pts.insert(pts.end(), pts2.begin(), pts2.end());
    pts.insert(pts.end(), pts3.begin(), pts3.end());
    pts.insert(pts.end(), pts4.begin(), pts4.end());
    pts.insert(pts.end(), pts5.begin(), pts5.end());

    //auto EuclidDistanceFunc = [](const Vec3f& v1, const Vec3f& v2)->float { return 0; };

    //printf("%f\n", EuclidDistanceFunc(Vec3f{ 1.f,0.f,0.f }, Vec3f{ 2.0f,0.f,0.f }));


    using milli = std::chrono::milliseconds;
    auto start = std::chrono::high_resolution_clock::now();

    auto dbscan = DBSCAN<Vec3f, float>();
    dbscan.Run(&pts, 3, 0.4f, 4);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Run() took "
        << std::chrono::duration_cast<milli>(end - start).count()
        << " milliseconds\n";



    float scalar = 100.f;

    for (int ic = 0; ic < dbscan.Clusters.size(); ++ic) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 255);
        Vec3f clustercolor = Vec3f{ (float)dis(gen), (float)dis(gen), (float)dis(gen) };
        for (int ip = 0; ip < dbscan.Clusters[ic].size(); ++ip) {
            int pid = dbscan.Clusters[ic][ip];
            cv::circle(
                atom_image
                , cv::Point(scalar * pts[pid].x, scalar * pts[pid].y)
                , 4
                , cv::Scalar(clustercolor.x, clustercolor.y, clustercolor.y)\
                , -1
            );
        }
    }

    for (int ic = 0; ic < dbscan.Noise.size(); ++ic) {
        int pid = dbscan.Noise[ic];
        cv::circle(
            atom_image
            , cv::Point(scalar * pts[pid].x, scalar * pts[pid].y)
            , 4
            , cv::Scalar(0, 0, 0)
            , -1
        );
    }
    printf("Hello Crystal\n");
    getchar();
    return 0;
}
