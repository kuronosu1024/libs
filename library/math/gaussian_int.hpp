#pragma once

#include <compare>

#include "round_div.hpp"

namespace nskr{
    struct gint{
        int re, im;

        gint():re(0),im(0){;}
        gint(int x):re(x),im(0){;}
        gint(int x, int y):re(x),im(y){;}

        long long norm() const {
            return (long long)re*re + (long long)im*im;
        }

        gint& operator+=(const gint& x){re += x.re; im += x.im; return *this; }
        gint& operator-=(const gint& x){re -= x.re; im -= x.im; return *this; }
        gint& operator*=(const gint& x){
            gint r(re*x.re - im*x.im, re*x.im + im*x.re);
            *this = r;
            return *this; 
        }
        gint& operator/=(const gint& x){
            long long d = x.norm();
            long long nr = (long long)re * x.re + (long long)im * x.im;
            long long ni = (long long)im * x.re - (long long)re * x.im;
            *this = gint( round_div(nr, d), round_div(ni, d) );
            return *this;
        }

        gint operator-() const {return gint(-re, -im);}
        gint operator+() const {return *this;}

        gint operator+(const gint& x) const {return gint(*this)+=x;}
        gint operator-(const gint& x) const {return gint(*this)-=x;}
        gint operator*(const gint& x) const {return gint(*this)*=x;}
        gint operator/(const gint& x) const {return gint(*this)/=x;}

        gint operator%=(const gint& x) {
            *this -= (*this/x)*x;
            return *this;
        }
        gint operator%(const gint& x){
            return gint(*this)%=x;
        }

        
        bool operator==(const gint& x) const {return re==x.re && im==x.im;} //あまり正しくないが、便宜上半順序集合にしてあることに注意
        bool operator!=(const gint& x) const {return re!=x.re || im!=x.im;} 
        bool operator<(const gint& x) const {return this->norm() < x.norm();}
        bool operator<=(const gint& x) const {return this->norm() <= x.norm();}
        bool operator>(const gint& x) const {return this->norm() > x.norm();}
        bool operator>=(const gint& x) const {return this->norm() >= x.norm();}
    };
}


/**
 * @brief ガウス整数
 */