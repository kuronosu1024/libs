#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include "../../library/template/template.hpp"

#include "../../library/datastructure/unionfind_with_potential.hpp"
#include "../../library/mathtype/modint.hpp"

using namespace nskr;

using mint = modint<998244353>;


mint op(mint a, mint b){
    return a+b;
}
mint inv(mint a){
    return -a;
}
mint e(){
    return (mint)0;
}

int main(void){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    unionfind_p<mint,op,inv,e> uf(n);
    for(;q--;){
        int t; cin >> t;
        if(t){
            int u, v; cin >> u >> v;
            auto x = uf.get(v,u);
            if(!x.first) cout << "-1\n";
            else cout << x.second.val() << "\n";
        }else{
            int u,v,x;cin>>u>>v>>x;
            bool a = uf.murge(u,v,x);
            if(a) cout << "1\n";
            else cout << "0\n";
        }
    }
}

