#define CRYSTAL_LIB_EXPORT

#include "CrystalLib.h"
#include "helper.h"
#include "DBSCAN.h"
#include <cstdio>
#include <memory>
#include <algorithm>
#include <numeric>
#include <limits>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>


namespace  Crystal {

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
        return true;

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
        return matX();

    }




    bool Extract::searchMatchClusters(const matX& V, const matX& N, const vec3& majorAxis, const uint nCluster, const uint nBest, std::vector<std::vector<uint>>& indices, std::vector<vec3>& centers) {

        CC_ASSERT_RETURN(nBest < nCluster || nBest > 0 || nCluster > 0, false);

        std::unique_ptr<uint[]> counts(new uint[nCluster]{ 0 });

        //! opencv kmeans only supports float
        cv::Mat normals((int)V.rows(), 1, CV_32FC3, cv::Scalar(0, 0, 0));

        for (int i = 0; i < V.rows(); ++i) {
            cv::Vec3f& p = normals.at<cv::Vec3f>(i);
            p[0] = float(N(i, 0));
            p[1] = float(N(i, 1));
            p[2] = float(N(i, 2));
        }
        // !opencv kmeans only supports float
        cv::Mat mlabels, mcenters; 

        //! You should notice kmeans only supports float type
        cv::kmeans(normals, nCluster, mlabels, cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0), 3, cv::KMEANS_PP_CENTERS, mcenters);


        std::vector<vec3> centersNormed; centersNormed.resize(nCluster);
        {
            for (uint i = 0; i < nCluster; ++i) {
                const float* c = mcenters.ptr<float>(i);
                ffloat norm = std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
                centersNormed[i] = vec3(c[0], c[1], c[2]) / norm;
            }
        }

        // mcenters
        // label 1,      |    label 2,      |     label3        | ...
        // ------------------------------------------------------------
        // mcenters[0]   |    mcenters[1]   |     mcenters[2]   | ...

        // mlabels
        // vertex index    |   label
        // ------------------------------
        // 0               |   label2
        // 1               |   label1
        // ....            |   ....

        std::vector<uint> idxs(nCluster);
        {
            std::iota(idxs.begin(), idxs.end(), 0);
            std::sort(idxs.begin(), idxs.end(), [&centersNormed, &majorAxis](uint i1, uint i2)->bool {
                return helper::angle(centersNormed[i1], majorAxis) < helper::angle(centersNormed[i2], majorAxis);
            });
        }

        centers.clear(); centers.resize(nBest);
        for (uint i = 0; i < nBest; ++i) centers[i] = centersNormed[idxs[i]]; // Get first n centers

        // idxston  - Old index map to new index
        //  idxton[0]    |    idxton[1]    |    idxton[2]    |   idxton[3]
        //  -1                2                 1                -1

        std::vector<int> idxston(nCluster, -1);
        for (uint i = 0; i < nBest; ++i) idxston[idxs[i]] = i; // Mask first n indices

        indices.clear(); indices.resize(nBest);
        for (uint iv = 0; iv < mlabels.rows; ++iv) {
            const uint u = (uint)mlabels.at<int>(iv);
            if (-1 != idxston[u]) indices[idxston[u]].push_back(iv);
        }


        return true;
    }

}