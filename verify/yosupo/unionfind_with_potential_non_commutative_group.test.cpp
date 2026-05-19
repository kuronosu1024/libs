#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential_non_commutative_group"

#include "../../library/template/template.hpp"

#include "../../library/datastructure/unionfind_with_potential.hpp"
#include "../../library/mathtype/modint.hpp"

using namespace nskr;

using mint = modint<998244353>;

struct s{
    mint a,b,c,d;
    bool operator!=(s x){
        return (a!=x.a||b!=x.b||c!=x.c||d!=x.d) ;
    }
};

s op(s a, s b){
    return {a.a*b.a + a.c*b.b, a.b*b.a+a.d*b.b, a.a*b.c + a.c*b.d, a.b*b.c+a.d*b.d};
}
s inv(s a){
    return {a.d,-a.b,-a.c,a.a};
}
s e(){
    return {1,0,0,1};
}


int main(void){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    unionfind_p<s, op, inv, e> uf(n);
    for(;q--;){
        int t; cin >> t;
        if(t){
            int u, v; cin >> u >> v;
            auto x = uf.get(u,v);
            if(!x.first) cout << "-1\n";
            else cout << x.second.a.val() << " " << x.second.b.val() << " " << x.second.c.val() << " " << x.second.d.val() << "\n";
        }else{
            int u,v,a,b,c,d;cin>>u>>v>>a>>b>>c>>d;
            s x = {a,b,c,d};
            bool z = uf.murge(u,v,x);
            if(z) cout << "1\n";
            else cout << "0\n";
        }
    }
}

