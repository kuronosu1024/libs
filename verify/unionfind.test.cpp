#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define rep(i,n) for(i=0;i<(n);i++)
#define all(a) a.begin(), a.end()
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

namespace nskr{
    int i, j;
    struct unionfind{
        //unionfind - union by size, 経路圧縮
        vector<int> pr, sz;
        unionfind(int n){
            pr.resize(n);
            sz.resize(n,1);
            rep(i,n) pr[i] = i;
        }

        inline int find(int x){ 
            while(pr[x] != x){ 
                pr[x] = pr[pr[x]];
                x = pr[x];
            }
            return x;
        }
        
        inline void merge(int p, int q){ 
            p = find(p); q = find(q);
            if(p==q) return ;
            if(sz[p] < sz[q]) swap(p,q);
            pr[q] = p;
            sz[p] += sz[q];
            return ;
        }

        inline bool same(int p, int q){
            if(find(p) == find(q)) return true;
            return false;
        }

        int size(int x){
            return sz[find(x)];
        }
    };
}



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
