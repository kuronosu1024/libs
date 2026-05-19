#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../library/template/template.hpp"
#include "../../library/datastructure/sortedset.hpp"

using namespace nskr;
int main(void){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n,q; cin >> n >> q;
    sortedset<int> s;
    int x;
    for(;n--;){cin >> x;s.insert(x);}
    for(;q--;){
        int t; cin>>t>>x;
        if(t==0){
            s.insert(x);
        }if(t==1){
            s.erase(x);
        }if(t==2){
            x--;
            if(x >= s.size()) cout << "-1\n";
            else{
                x = s[x];
                cout << x << "\n";
            }    
        }if(t==3){
            cout << s.rank(x) << "\n";
        }if(t==4){
            auto it = s.upper_bound(x);
            if(it == s.sentinel) cout << "-1\n";
            else cout << it->key << "\n";
        }if(t==5){
            auto it = s.lower_bound(x);
            if(it == s.sentinel) cout << "-1\n";
            else cout << it->key << "\n";
        }
    } 
}
