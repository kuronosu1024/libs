#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../../library/template/template.hpp"
#include "../../library/math/convolution.hpp"

using namespace nskr;
int main(void){
    
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t, m; cin >> t >> m;
    modint<0> x;x.set_mod(m);
    convolution<modint<0>> c;
    for(;t--;){
        int n,k; cin >> n >> k;
        c.preculc(max(n,k));
        cout << c.conv(n,k) << "\n";
    }
}