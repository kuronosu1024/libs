#pragma once

#include "gcd.hpp"

namespace nskr{

    struct rint{
        int num,den;

        rint():den(1),num(0){;}
        rint(int x):den(1),num(x){;}
        rint(int x, int y):den(y),num(x){;} //(x / y)

        void reduce(){
            int g = binary_gcd(num, den);
            if(g == 0) return;
            num/=g; den/=g;
            if(den<0){
                den*=-1;
                num*=-1;
            }
        }

        rint& operator+=(const rint& x){
            int g = binary_gcd(den, x.den);
            *this = rint(num * (x.den / g) + x.num * (den / g), den / g * x.den);
            this->reduce();
            return *this;
        }
        rint& operator-=(const rint& x){
            int g = binary_gcd(den, x.den);
            *this = rint(num * (x.den / g) - x.num * (den / g), den / g * x.den);
            this->reduce();
            return *this;
        }
        rint& operator*=(const rint& x){
            long long nn = num * x.num, nd = den * x.den, g = binary_gcd(nn, nd);
            nn/=g; nd/=g;
            num = nn; den = nd;
            return *this;
        }
        rint& operator/=(const rint& x){
            long long nn = num * x.den, nd = den * x.num, g = binary_gcd(nn, nd);
            nn/=g; nd/=g;
            num = nn; den = nd;
            return *this;
        }

        rint operator-() const {return rint(-num, den);}
        rint operator+() const {return *this;}

        rint operator+(const rint& x) const {return rint(*this)+=x;}
        rint operator-(const rint& x) const {return rint(*this)-=x;}
        rint operator*(const rint& x) const {return rint(*this)*=x;}
        rint operator/(const rint& x) const {return rint(*this)/=x;}

        
        bool operator==(const rint& x) const {return num==x.num && den==x.den;} 
        bool operator!=(const rint& x) const {return num!=x.num || den!=x.den;} 
        bool operator<(const rint& x) const {return (long long)num * x.den < (long long)x.num * den ;}
        bool operator<=(const rint& x) const {return (long long)num * x.den <= (long long)x.num * den ;}
        bool operator>(const rint& x) const {return (long long)num * x.den > (long long)x.num * den ;}
        bool operator>=(const rint& x) const {return (long long)num * x.den >= (long long)x.num * den ;;}
        
    };
}

/**
 * @brief 有理数
 */