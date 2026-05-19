#pragma once


namespace nskr{
    
    struct unionfind{
        //unionfind - union by size, 経路圧縮
        vector<int> pr, sz;
        unionfind(int n){
            pr.resize(n);
            sz.resize(n,1);
            int i;
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

