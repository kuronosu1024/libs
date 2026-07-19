#pragma once


namespace nskr{

    int round_div(int a, int b){
        if(b<0){ a=-a;b=-b; }

        if(a>=0) return (a+b/2)/b;
        else return (a-b/2)/b;
    }
    

    int round_div(int a, long long b){
        if(b<0){ a=-a;b=-b; }

        if(a>=0) return (a+b/2)/b;
        else return (a-b/2)/b;
    }

    long long round_div(long long a, long long b){
        if(b<0){ a=-a;b=-b; }

        long long rem = a%b;
        long long res = a/b;

        if(a>=0 && rem*2 >= b) return res+1;
        else if(a<0 && -rem*2 >= b) return res-1;
        else return res; 
    }
}


/**
 * @brief 浮動小数点数を介さない整数の商の四捨五入
 */