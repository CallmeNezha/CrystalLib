#define CRYSTAL_LIB_EXPORT

#include "CrystalLib.h"
#include <cstdio>
#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>


namespace  Crystal {

#define CC_ASSERT_RETURN(x, val)    if(!(x)) { assert(x); return val;}


    CRYSTAL_LIB_API bool Extract::ExtractPlane(
        const matX&          V
        , const matX&        N
        , const mat3&        trans
        , const ffloat       rthrold
        , const uint         nCluster
        , const uint         nZCluster
        , const uint         nIter
        , const uint         nMin
        , vec4&              plane
        , std::vector<vec3>& chull
        , const vec3&        USER_COORD
        , const ffloat       ratio
        , vec3               crect[4]
    ) {
        // Validation
        CC_ASSERT_RETURN(V.rows() == N.rows(), false);
        CC_ASSERT_RETURN(mat3::Zero() != trans, false);
        CC_ASSERT_RETURN(rthrold > 0.0 && nCluster > 0 && nZCluster > 0 && nIter > 0 && nMin > 0, false);
        CC_ASSERT_RETURN(nMin > V.rows() / 2, false);
        CC_ASSERT_RETURN(ratio > 0 && ratio < 1, false);

        const vec3 right =   trans.row(0);
        const vec3 forward = trans.row(1);
        const vec3 upward =  trans.row(2);

        // Broad cluster based on normal
        

    }

    Crystal::matX Extract::searchExpectedCluster(
        const matX& V
        , const matX& N
        , const vec3& majorAxis
        , const uint nCluster
        , const uint nIter
        , const uint nMin
        , const ffloat rthold
    ) {
        vec3 bestMajorAxis = majorAxis;

        cv::Mat points;


    }



    Crystal::matX Extract::searchNormalCluster(const matX& V, const matX& N, const vec3& majorAxis, const uint nCluster) {
        std::unique_ptr<uint> counts(new uint[nCluster]{ 0 });

        cv::Mat p;
        cv::eigen2cv(V, p);
    }

}