#pragma once

#include "modint.hpp"
#include <vector>
namespace nskr{
    template<typename mint>
    struct convolution{
        vector<mint> fac;
        convolution():fac({mint(1)}){}
        
        void preculc(int n){
            fac.reserve(n);
            while(fac.size() <= n){
                fac.push_back( (*fac.rbegin()) * mint(fac.size()) );
            }
            return;
        }

        mint conv(int n, int r){ 
            if(r>n || r<0 || n<0) return 0;
            if(n-r < r) r = n-r;
            if(fac.size() > n) return fac[n] * fac[r].inv() * fac[n-r].inv();
            else{
                mint ret = fac[r].inv();
                for(;r--;) ret *= (n-r+1);
                return ret;
            }
        }
    };
}



/**
 * @brief 二項係数
 */