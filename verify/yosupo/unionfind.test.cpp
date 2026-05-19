#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../../library/template/template.hpp"

#include "../../library/datastructure/unionfind.hpp"

using namespace nskr;
int main(void){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    unionfind uf(n);
    for(;q--;){
        int t,u,v; cin >> t >> u >> v;
        if(t){
            if(uf.same(u,v))cout << "1\n";
            else cout << "0\n";
        }else{
            uf.merge(u,v);
        }
    }
}
