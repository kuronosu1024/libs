#pragma once

#include <cstdint>
#include <algorithm>
#include <functional>

namespace nskr{
    uint64_t binary_gcd(uint64_t a, uint64_t b){
        if(a*b==0) return a+b;

        char as = __builtin_ctzll(a);
        char bs = __builtin_ctzll(b);
        a>>=as;
        b>>=bs;

        while(a!=b){
            bool f = a>b;
            uint64_t c = (f ? a-b : b-a);
            char cs = __builtin_ctzll(c);
            a = (f ? b : a);
            b = c>>cs;
        }
        return a << (as > bs ? bs : as);
    }

    template <typename T> //Tがユークリッド整域であって、%演算子が適切に実装されていることを要求する
    T gcd(T a, T b){
        if(a==T(0)) return b;
        if(b==T(0)) return a;

        while(b!=T(0)){
            T c = b;
            b = a%b;
            a = c;
        }

        return a;
    }

    template <typename T> //Tがユークリッド整域であって、%演算子が適切に実装されていることを要求する
    array<T,3> extgcd(T a, T b){ // ax + by = gcd(a,b) を満たす x,y と gcd(a,b) をこの順で返す
        T x0 = T(1), x1 = T(0), x2, y0 = T(1), y1 = T(0), y2;
        while(b!=T(0)){
            T r = a%b;
            T q = (a-r)/b;

            x2 = x0 - q * x1;
            x0 = x1;
            x1 = x2;

            y2 = y0 - q * y1;
            y0 = y1;
            y1 = y2;
        }
        return {x0,y0,a};
    }
}

/**
 * @brief GCD (binary_gcd, 普通のgcd)
 */