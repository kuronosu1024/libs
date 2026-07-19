#pragma once

#include <cstdint>
#include <algorithm>
#include <functional>

namespace nskr{
    uint64_t binary_gcd(uint64_t a, uint64_t b){
        if(a==0) return b;
        if(b==0) return a;
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

    template <typename T>
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
}

/**
 * @brief GCD (binary_gcd, 普通のgcd)
 */