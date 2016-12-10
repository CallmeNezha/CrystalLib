#define CRYSTAL_LIB_EXPORT

#include "CrystalLib.h"
#include "helper.h"
#include <cstdio>
#include <memory>
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




    bool Extract::searchNormalCluster(const matX& V, const matX& N, const vec3& majorAxis, const uint nCluster, std::vector<uint>& indices, vec3& center) {

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
        cv::Mat labels, centers; 

        //! You should notice kmeans only supports float type
        cv::kmeans(normals, nCluster, labels, cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0), 3, cv::KMEANS_PP_CENTERS, centers);


        std::unique_ptr<vec3[]> centersNormed(new vec3[nCluster]{ vec3::Zero() });

        for (uint i = 0; i < nCluster; ++i) {
            const float* c = centers.ptr<float>(i);
            ffloat norm = std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
            centersNormed[i] = vec3(c[0], c[1], c[2]) / norm;
        }
        const uint idx = helper::closestEuler(centersNormed.get(), majorAxis, nCluster);

        indices.clear();
        for (uint i = 0; i < labels.rows; ++i) if (idx == (uint)labels.at<int>(i)) indices.push_back(i);

        return true;
    }

}