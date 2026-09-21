#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include "../../library/template/template.hpp"
#include "../../library/function/fastIO.hpp"

using namespace nskr;
int main(void){
    int t = fIn.nextNum();
    int i;
    rep(i,t){
        ll a = fIn.nextNum();
        ll b = fIn.nextNum();
        fOut.printNum(a+b);
        *fOut.pos++ = '\n';
    }
}