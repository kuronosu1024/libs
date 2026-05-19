#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../library/template/template.hpp"

#include "../library/datastructure/unionfind.hpp"

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using ld = long double;
#define rep(i,n) for(i=0;i<(n);i++)
#define all(a) a.begin(), a.end()


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
