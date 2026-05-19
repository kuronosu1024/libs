#pragma once

namespace nskr{

    //nyaan氏の実装をかなり参考にした
    template <int mod>
    struct modint{
        int v;

        modint() :v(0){}
        modint(ll x) : v( (x>=0 ? x%mod : (x%mod + mod))){}

        ll val() const {return v;}

        modint& operator+=(const modint& x){if((v+=x.v) >= mod) v-=mod; return *this; }
        modint& operator-=(const modint& x){if((v-=x.v) <  0  ) v+=mod; return *this; }
        modint& operator*=(const modint& x){v = (int)(1ll * v * x.v % mod); return *this;}
        modint& operator/=(const modint& x){v = (int)(1ll * v * x.inv() % mod); return *this;}

        modint operator-() const {return modint(-v);}
        modint operator+() const {return this;}

        modint operator+(const modint& x) const {return modint(*this)+=x.v;}
        modint operator-(const modint& x) const {return modint(*this)-=x.v;}
        modint operator*(const modint& x) const {return modint(*this)*=x.v;}
        modint operator/(const modint& x) const {return modint(*this)/=x.v;}

        bool operator== (const modint& x) const {return v==x.v;}
        bool operator!= (const modint& x) const {return v!=x.v;}

        friend ostream &operator<<(ostream &os, const modint &p) { return os << p.v; }

        friend istream &operator>>(istream &is, modint &a) {
            int t;
            is >> t;
            a = modint<mod>(t);
            return (is);
        }


        modint pow(unsigned long long n) const { 
            modint ret(1), mul(v);
            while(n){
                if(n&1) ret *= mul;
                mul *= mul;
                n >>=1;
            }
            return ret;
        }

        modint inv() const{ //参考：　https://qiita.com/sesame0224/items/f2ac77c367f588c0d29d
            int a = v, b = mod, u = 1, w = 0;
            while(b){
                int t = a/b;                 
                swap(a -= t*b, b);
                swap(u -= t*w, w);
            }
            u%=mod;
            return(u<0?u+mod:u);
        }

        static constexpr int get_mod(){ return mod; }

    };
}
