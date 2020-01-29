//
// Created by shaqfa on 06/12/2019.
//

#ifndef C__14_TYPES_H
#define C__14_TYPES_H

  /////////////////////////////////////////////////////
 ///               Mahmoud S. Shaqfa               ///
/////////////////////////////////////////////////////

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <memory>
#include <math.h>

  /////////////////////////////////////////////////////
 ///         Handy Types Definition                ///
/////////////////////////////////////////////////////

typedef unsigned int UInt;
typedef double Real;
typedef std::string Str;
typedef std::vector<Real> RealVec;
typedef std::vector<std::vector<Real>> RealMat;
typedef std::vector<std::vector<UInt>> UIntMat;
typedef std::vector<UInt> UIntVec;
const double PI = std::atan(1) * 4.;

#include <iostream>
#include <limits>

namespace vo {

      /////////////////////////////////////////////////////
     ///         Vectorized Operations                 ///
    /////////////////////////////////////////////////////

    // 1- one dimensional arrays - vectors
    template<typename T>
    void print(std::vector<T> &vec) {
        std::cout << "[";
        for (auto &&v: vec)std::cout << " " << v;
        std::cout << " ]" << std::endl;
    }

    template<typename T>
    UInt &max_idx(std::vector<T> &vec) {
        T current = std::numeric_limits<T>::lowest();
        static UInt idx = 0;
        for(UInt k = 0; k< vec.size(); ++k){
            if (current < vec[k]){
                idx = k; current = vec[k];
            }
        }
        return idx;
    }

    template<typename T>
    UInt &min_idx(std::vector<T> &vec) {
        T current = std::numeric_limits<T>::max();
        static UInt idx = 0;
        for(UInt k = 0; k< vec.size(); k++){
            if (current > vec[k]) {
                idx = k; current = vec[k];
            }
        }
        return idx;
    }

    template<typename T>
    T &max_val(std::vector<T> &vec) {
        static T current = std::numeric_limits<T>::lowest();
        for (auto &&v: vec) {
            if (v > current)
                current = v;
        }
        return current;
    }

    template<typename T>
    T &min_val(std::vector<T> &vec) {
        static T current = std::numeric_limits<T>::max();
        for (auto &&v: vec) {
            if (v < current)
                current = v;
        }
        return current;
    }

    template<typename T>
    T &sum(std::vector<T> &vec) {
        static T current = 0;
        for (auto &&v: vec)
            current += v;
        return current;
    }

    template<typename T>
    UInt &sum(std::vector<T> &vec, const T &val) {
        static UInt idx_sum = 0;
        for (auto &&v: vec) {
            if (val == v)
                idx_sum++;
        }
        return idx_sum;
    }

    // 2- matrices - arrays of arrays

    template<typename T>
    void print(std::vector<std::vector<T>> &mat) {
        for (auto &&vec: mat) {
            std::cout << "[";
            for (auto &&v: vec)
                std::cout << " " << v;
            std::cout << " ]" << std::endl;
        }
    }

    template<typename T>
    T &max_val(std::vector<std::vector<T>> &mat) {
        static T current = std::numeric_limits<T>::lowest();
        for (auto &&vec: mat) {
            for (auto &&v: vec) {
                if (current < v)
                    current = v;
            }
        }
        return current;
    }

    template<typename T>
    T &min_val(std::vector<std::vector<T>> &mat) {
        static T current = std::numeric_limits<T>::max();
        for (auto &&vec: mat) {
            for (auto &&v: vec) {
                if (current > v)
                    current = v;
            }
        }
        return current;
    }

    template<typename T>
    T &sum(std::vector<std::vector<T>> &mat) {
        static T current = 0;
        for (auto &&vec: mat) {
            for (auto &&v: vec)
                current += v;
        }
        return current;
    }

    template<typename T>
    UInt &sum(std::vector<std::vector<T>> &mat, const T &val) {
        static UInt current = 0;
        for (auto &&vec: mat) {
            for (auto &&v: vec) {
                if (val == v)
                    current++;
            }
        }
        return current;
    }

    template<typename T>
    void replace_row(std::vector<std::vector<T>> &mat,
                     std::vector<T> &newVector, const UInt &idx) {
        UInt id = 0;
        for (auto &&v: newVector) {
            mat[idx][id] = v;
            id++;
        }
    }

    template<typename T>
    UInt& sum_eq_col(std::vector<std::vector<T>>& mat, const UInt& idx, T& val){
        static UInt sum_count; sum_count=0;
        for (auto &&vec: mat) {
            if (vec[idx] == val)
                sum_count++;
        }
        return sum_count;
    }

    template<typename T>
    const T& min(const T& a, const T& b){
            return (b < a) ? b : a;
        }

    template<typename T>
    const T& max(const T& a, const T& b){
            return (b > a) ? b : a;
        }
}
#endif //C__14_TYPES_H