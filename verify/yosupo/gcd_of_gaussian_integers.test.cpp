#define PROBLEM "https://judge.yosupo.jp/problem/gcd_of_gaussian_integers"

#include "../../library/template/template.hpp"
#include "../../library/math/gaussian_int.hpp"
#include "../../library/math/gcd.hpp"

using namespace nskr;
int main(void){
    
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    for(;t--;){
        int a, b, c, d; cin >> a >> b >> c >> d;
        gint x(a,b), y(c,d);
        gint r = gcd(x,y);
        cout << r.re << " " << r.im << "\n";
    }
}
