//
// Created by admin on 2016/12/10.
//

#ifndef __CRYSTALLIB_HELPER_H__
#define __CRYSTALLIB_HELPER_H__

// Macro helpers
#define CC_ASSERT_RETURN(x, y) if(!(x)) { assert(x); return y; }


namespace  Crystal {
namespace  helper {

    template<typename T>
    ffloat angle(const T& t1, const T& t2) {
        return std::acos(t1.normalized().dot(t2.normalized()));
    }

    template<typename T>
    uint closestEuclid(const T* v, const T& s, const uint size) {
        ffloat min = std::numeric_limits<ffloat>::max();
        uint idx = 0;
        for (uint i = 0; i < size; ++i) {
            ffloat norm = (v[i] - s).squaredNorm();
            if (norm < min) { min = norm; idx = i; }
        }
        return idx;
    }

    template<typename T>
    uint closestEuler(const T* v, const T& s, const uint size) {
        ffloat min = std::numeric_limits<ffloat>::max();
        uint idx = 0;
        for (uint i = 0; i < size; ++i) {
            ffloat angle = angle(v[i], s);
            if (angle < min) { min = angle; idx = i; }
        }
        return idx;
    }



}
}

#endif //__CRYSTALLIB_HELPER_H__
