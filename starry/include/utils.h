/**
\file utils.h
\brief Miscellaneous utilities and definitions used throughout the code.

*/

#ifndef _STARRY_UTILS_H_
#define _STARRY_UTILS_H_

// Includes
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/SparseLU>
#include <unsupported/Eigen/AutoDiff>
#include <random>
#include <chrono>

//! Compiler branching optimization: likely branch
#define likely(x)                   __builtin_expect (!!(x), 1)

//! Compiler branching optimization: unlikely branch
#define unlikely(x)                 __builtin_expect (!!(x), 0)

//! Max iterations in elliptic integrals
#ifndef STARRY_ELLIP_MAX_ITER
#   define STARRY_ELLIP_MAX_ITER        200
#endif

//! Max iterations in computing the M & N integrals
#ifndef STARRY_MN_MAX_ITER
#   define STARRY_MN_MAX_ITER           100
#endif

//! Max iterations in computing the I & J integrals
#ifndef STARRY_IJ_MAX_ITER
#   define STARRY_IJ_MAX_ITER           200
#endif

//! Refine the downward recursion in the J integral at this index
#ifndef STARRY_REFINE_J_AT
#   define STARRY_REFINE_J_AT           25
#endif

//! Cutoff value for `b` below which we reparametrize LD evaluation
#ifndef STARRY_BCUT
#   define STARRY_BCUT                 1.0e-3
#endif

//! Things currently go numerically unstable in our bases for high `l`
#ifndef STARRY_MAX_LMAX
#   define STARRY_MAX_LMAX             50
#endif

//! The value of `pi` in double precision
#ifndef M_PI
#   define M_PI                        3.14159265358979323846264338328
#endif

//! Square root of `pi` in double precision
#ifndef M_SQRTPI
#   define M_SQRTPI                    1.77245385090551602729816748334
#endif

// Bounds checks
#ifdef STARRY_DEBUG
    //! Check matrix shape (debug mode only)
#   define CHECK_SHAPE(MATRIX, ROWS, COLS)\
        assert((static_cast<size_t>(MATRIX.cols()) == static_cast<size_t>(COLS)) && \
        (static_cast<size_t>(MATRIX.rows()) == static_cast<size_t>(ROWS)))
    //! Check matrix columns (debug mode only)
#   define CHECK_COLS(MATRIX, COLS)\
        assert(static_cast<size_t>(MATRIX.cols()) == static_cast<size_t>(COLS))
    //! Check matrix rows (debug mode only)
#   define CHECK_ROWS(MATRIX, ROWS)\
        assert(static_cast<size_t>(MATRIX.rows()) == static_cast<size_t>(ROWS))
    //! Check index bounds (debug mode only)
#   define CHECK_BOUNDS(INDEX, IMIN, IMAX)\
        assert((static_cast<size_t>(INDEX) >= static_cast<size_t>(IMIN)) && \
        (static_cast<size_t>(INDEX) <= static_cast<size_t>(IMAX)))
#else
    //! Check matrix shape (debug mode only)
#   define CHECK_SHAPE(MATRIX, ROWS, COLS)  do {} while(0)
    //! Check matrix columns (debug mode only)
#   define CHECK_COLS(MATRIX, COLS)  do {} while(0)
    //! Check matrix rows (debug mode only)
#   define CHECK_ROWS(MATRIX, ROWS)  do {} while(0)
    //! Check index bounds (debug mode only)
#   define CHECK_BOUNDS(INDEX, IMIN, IMAX)  do {} while(0)

#endif

namespace starry_theano { 
namespace utils {


//! Commonly used stuff throughout starry
using std::abs;
using std::max;
using std::isinf;
using std::swap;


// --------------------------
// ----- Linear Algebra -----
// --------------------------


//! Matrices
using Eigen::Ref;
using Eigen::MatrixBase;
using Eigen::ColMajor;
using Eigen::RowMajor;
template <typename T>
using Vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;
template <typename T>
using UnitVector = Eigen::Matrix<T, 3, 1>;
template <typename T>
using RowVector = Eigen::Matrix<T, 1, Eigen::Dynamic>;
template <typename T>
using OneByOne = Eigen::Matrix<T, 1, 1>;
template <typename T, int StorageOrder=ColMajor>
using Matrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, StorageOrder>;
template <typename T, int N>
using ADScalar = Eigen::AutoDiffScalar<Eigen::Matrix<T, N, 1>>;


// --------------------------
// -------- Constants -------
// --------------------------


// Tag forwarding hack
template <class T> 
struct tag {};

//! Pi for current type
template <class T> 
inline T pi() { 
    return static_cast<T>(M_PI); 
}

//! Square root of pi for current type
template <class T> 
inline T root_pi() { 
    return static_cast<T>(M_SQRTPI); 
}

//! Machine precision for current type
template <class T> 
inline T mach_eps(tag<T>) { 
    return std::numeric_limits<T>::epsilon(); 
}
template <class T> 
inline Eigen::AutoDiffScalar<T> mach_eps(
    tag<Eigen::AutoDiffScalar<T>>
) {
    return std::numeric_limits<typename T::Scalar>::epsilon();
}
template <class T> 
inline T mach_eps() { 
    return mach_eps(tag<T>()); 
}


// --------------------------
// ----- Utility Funcs ------
// --------------------------


//! Check if a number is even (or doubly, triply, quadruply... even)
inline bool is_even (
    int n, 
    int ntimes=1
) {
    for (int i = 0; i < ntimes; i++) {
        if ((n % 2) != 0) return false;
        n /= 2;
    }
    return true;
}


// --------------------------
// ------ Unit Vectors ------
// --------------------------


// Some useful unit vectors
static const UnitVector<double> xhat_double({1, 0, 0});
static const UnitVector<double> yhat_double({0, 1, 0});
static const UnitVector<double> zhat_double({0, 0, 1});

//! Unit vector in the xhat direction
template <typename T> 
inline UnitVector<T> xhat (){
    return xhat_double.template cast<T>();
}

//! Unit vector in the yhat direction
template <typename T> 
inline UnitVector<T> yhat (){
    return yhat_double.template cast<T>();
}

//! Unit vector in the zhat direction
template <typename T> 
inline UnitVector<T> zhat (){
    return zhat_double.template cast<T>();
}

// Normalize a unit vector
template <typename T>
inline UnitVector<T> norm_unit(const UnitVector<T>& vec) {
    UnitVector<T> result = vec / sqrt(vec(0) * vec(0) +
                                      vec(1) * vec(1) +
                                      vec(2) * vec(2));
    return result;
}

} // namespace utils
} // namespace starry_theano

#endif