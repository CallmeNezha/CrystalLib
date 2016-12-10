//
// Created by admin on 2016/12/9.
//

#ifndef __CRYSTALLIB_CRYSTALLIB_H__
#define __CRYSTALLIB_CRYSTALLIB_H__

#ifdef CRYSTAL_LIB_EXPORT
#define CRYSTAL_LIB_API   __declspec(dllexport)
#else
#define CRYSTAL_LIB_API   __declspec(dllimport)
#endif
#include <vector>
#include <Eigen/Core>

namespace Crystal
{
    typedef unsigned int    uint;
#ifndef USE_DOUBLE
    typedef Eigen::Vector3f vec3;
    typedef Eigen::Vector4f vec4;
    typedef Eigen::VectorXf vecX;
    typedef Eigen::MatrixXf matX;
    typedef Eigen::Matrix3f mat3;
    typedef Eigen::Matrix4f mat4;
    typedef float           ffloat;
#else
    typedef Eigen::Vector3d vec3;
    typedef Eigen::Vector4d vec4;
    typedef Eigen::VectorXd vecX;
    typedef Eigen::MatrixXd matX;
    typedef Eigen::Matrix3d mat3;
    typedef Eigen::Matrix4d mat4;
    typedef double          ffloat;
#endif

    // This class is exported from the MathLibrary.dll
    class Extract
    {
    public:
        // Returns a + b
        static CRYSTAL_LIB_API bool ExtractPlane(
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
        );


    private:
        static matX searchExpectedCluster(
            const matX& V
            , const matX& N
            , const vec3& majorAxis
            , const uint nCluster
            , const uint nIter
            , const uint nMin
            , const ffloat rthold
        );

        static bool searchNormalCluster(
            const matX& V
            , const matX& N
            , const vec3& majorAxis
            , const uint nCluster
            , std::vector<uint>& indices
            , vec3& center
        );
    };
}

#endif //__CRYSTALLIB_CRYSTALLIB_H__
