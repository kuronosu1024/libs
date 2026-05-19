#pragma once

#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

namespace nskr{
    template <class S, S (*op)(S,S), S (*inv)(S), S (*e)()>
    struct unionfind_p{
        //unionfind (with potential) - union by size, 経路圧縮
        // S には operator!= が定義されている必要がある
        // op : 積 / inv : 逆元 / e : 単位元
        vector<int> pr, sz;
        vector<S> val;
        unionfind_p(int n){
            pr.resize(n);
            sz.resize(n,1);
            val.resize(n,e()); 
            for(int i=0;i<n;i++) pr[i] = i;
        }

        pair<int,S> find(int x){ 
            if(x == pr[x]) return {x,e()};
            pair<int,S> y = find(pr[x]);
            val[x] = op(val[x],y.second);
            pr[x] = y.first;
            return {pr[x],val[x]};
        }
        
        bool murge(int p, int q, S x){ 
            pair<int, S> P = find(p), Q = find(q);
            if(P.first==Q.first){
                if(P.second != op(x,Q.second)) return false; //invalid;
                return true; //valid
            }
            if(sz[P.first] < sz[Q.first]) {swap(P,Q); x = inv(x);}
            pr[Q.first] = P.first;
            val[Q.first] = op(op(inv(Q.second), inv(x)),P.second);
            sz[p] += sz[q];
            return true; //valid
        }

        pair<bool,S> get(int p, int q){
            pair<int, S> P = find(p), Q = find(q);
            if(P.first == Q.first){
                return {true,op(P.second,inv(Q.second))};
            }
            return {false,e()};
        }
    };


}
