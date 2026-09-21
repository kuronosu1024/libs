#pragma once

#include "gcd.hpp"
#include "round_div.hpp"

namespace nskr{
    struct v2int{ //int型2次元ベクトル
        int x,y;

        v2int():x(0),y(0){;}
        v2int(int a):x(a),y(0){;}
        v2int(int a, int b):x(a),y(b){;}

        v2int& operator+=(const v2int& a){x += a.x; y += a.y; return *this;}
        v2int& operator-=(const v2int& a){x -= a.x; y -= a.y; return *this;}

        v2int operator+() const {return *this;}
        v2int operator-() const {return v2int(-x, -y);}

        v2int operator+(const v2int& a)const {return v2int(x+a.x,y+a.y);}
        v2int operator-(const v2int& a)const {return v2int(x-a.x,y-a.y);}

        v2int& operator*=(const int& a){x *= a; y *= a; return *this;}
        v2int& operator/=(const int& a){x /= a; y /= a; return *this;}

        friend v2int operator*(const v2int& a, const int& b){return v2int(a.x * b, a.y * b);}
        friend v2int operator/(const v2int& a, const int& b){return v2int(a.x / b, a.y / b);}

        friend v2int operator*(const int& b, const v2int& a){return v2int(a.x * b, a.y * b);}
        friend v2int operator/(const int& b, const v2int& a){return v2int(a.x / b, a.y / b);}

        bool operator==(const v2int& a)const {return (x==a.x && y==a.y);}
        bool operator!=(const v2int& a)const {return (x!=a.x || y!=a.y);}

        long long norm() const {
            return (long long)x*x + (long long)y*y;
        }

        v2int reduce() const {
            int g = binary_gcd(abs(x),abs(y)) * (x<0? -1 : 1);
            if(g) return v2int(x/g,y/g);
            else return v2int(0,0);
        }

        v2int& reduced(){
            int g = binary_gcd(abs(x),abs(y)) * (x<0 ? -1 : 1);
            if(!g) return *this;
            x/=g; y/=g;
            return *this;
        }
    };

    long long dot(const v2int& a, const v2int& b){
        return (long long)a.x*b.y + (long long)b.x*a.y;
    }

    struct l2int{ //int型2次元直線
        v2int a, b; // a+bt 

        l2int():a(v2int(0,0)),b(v2int(1,0)){;}
        l2int(const v2int& a0, const v2int& b0){// a_0 + b_0 * t
            b = b0.reduce();
            long long k = round_div(dot(a0,b),b.norm());
            a = a0 + k*b;
        }
        l2int(int a0,int b0,int c0){ //ax + by = c
            b = v2int(a0,-b0).reduced();
        }
    };



    
}


/**
 * @brief 平面ベクトル(幾何用)
 */