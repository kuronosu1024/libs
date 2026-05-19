#pragma once

#include <cstddef>
using namespace std;

namespace nskr{
    template<typename T>
    struct sortedset{
        struct node{
            T key;
            int level;
            node *left, *right;
            int lcount, rcount;
            
            node(T x) :key(x), level(0), left(nullptr), right(nullptr),lcount(0),rcount(0){}
        };
        
        node* sentinel;
        private:
        
        node* root;
        
        node* skew(node* x){ //左同levelを解決
            if(x==nullptr) return nullptr;
            if(x->left==nullptr) return x;
            if(x->left->level==x->level){
                node* leftnode = x->left;
                x->left = leftnode->right;
                leftnode->right = x;
                // swap(leftnode->rcount, x->lcount);
                // leftnode->lcount += x->rcount - leftnode->lcount;
                setcount(x);
                setcount(leftnode);
                return leftnode;
            }else{
                return x;
            }
        }
        
        node* split(node* x){ //右連続同levelを解決
            if(x==nullptr) return nullptr;
            if(x->right==nullptr) return x;
            if(x->right->right==nullptr) return x;
            if(x->right->right->level == x->level){
                node* rightnode = x->right;
                x->right = rightnode->left;
                rightnode->left = x;
                rightnode->level++;
                // swap(x->rcount,rightnode->lcount);
                // rightnode->lcount += x->lcount - rightnode->rcount;
                setcount(x);
                setcount(rightnode);
                return rightnode;
            }else{
                return x;
            }
        }

        void setcount(node* x){
            if(x==nullptr) return;
            if(x->left == nullptr) x->lcount = 0;
            else x->lcount = x->left->lcount + x->left->rcount + 1;
            if(x->right == nullptr) x->rcount = 0;
            else x->rcount = x->right->lcount + x->right->rcount + 1;
            x->rcount+=0;
            return;
        }
        
        node* insert(node* x, T key){
            if(x == nullptr) return new node(key);
            if(x->key < key){
                x->right = insert(x->right, key);
            }else if(x->key > key){
                x->left  = insert(x->left , key);
            } else return x;
            setcount(x);
            return split(skew(x));
        }

        node* erase(node* x, T key){
            if(x == nullptr) return nullptr;
            if(key < x->key) {
                x-> left = erase(x->left, key);
            }else if(key > x->key) x->right=erase(x->right, key);
            else{
                if(x->left == nullptr){
                    node* ret = x->right;
                    delete x;
                    return ret;
                }
                if(x->right == nullptr){
                    node* ret = x->left;
                    delete x;
                    return ret;
                }
                node* tgt = x->right;
                while(tgt->left != nullptr) tgt = tgt->left;
                x->key = tgt->key;
                x->right = erase(x->right, tgt->key);
            }
            setcount(x);
            
            int newlevel = min(
                (x->left == nullptr ? 0 : x->left->level),
                (x->right == nullptr ? 0 : x->right->level)    
            )+1;

            if(newlevel < x->level){
                x->level = newlevel;
                if(x->right != nullptr && newlevel < x->right->level){
                    x->right->level = newlevel; 
                }
            }

            x = skew(x);
            if(x->right != nullptr){
                x->right = skew(x->right);
                if(x->right->right != nullptr) x->right->right = skew(x->right->right);
            }

            x = split(x);
            if(x->right != nullptr) x->right = split(x->right);

            return x;
        }



        node* get(node* x, int t){
            if(x==nullptr) return nullptr;
            if(x->lcount < t) return get(x->right, t-x->lcount-1);
            if(x->lcount > t) return get(x->left, t);
            return x;
        }

        node* lower_bound(node* x, T key){//key以上の最小
            if(x == nullptr)return sentinel;
            if(x->key < key){
                return lower_bound(x->right, key);
            }if(x->key > key){
                node* ret = lower_bound(x->left, key);
                if(ret == sentinel) return x;
                else return ret;
            }
            return x;
        }

        node* upper_bound(node* x, T key){//key以下の最大
            if(x == nullptr)return sentinel;
            if(x->key > key){
                return upper_bound(x->left, key);
            }if(x->key < key){
                node* ret = upper_bound(x->right, key);
                if(ret == sentinel) return x;
                else return ret;
            }
            return x;
        }

    
        int rank(node* x, T key){
            if(x==nullptr) return 0;
            if(x->key==key) return  x->lcount+1;
            if(x->key<key){
                return rank(x->right,key) + x->lcount+1;
            }
            if(x->key>key){
                return rank(x->left,key);
            }
        }
        
        public:


        
        sortedset():root(nullptr),sentinel(0){}
        
        const T operator[](int t){
            node* x = get(root, t);
            if(x==nullptr) return T();
            else return x->key;
        }

        size_t size(){
            if(root==nullptr)return 0;
            return root->lcount + root->rcount + 1;
        }

        void insert(T key){root = insert(root, key);}
        void erase(T key){root = erase(root, key);}
        
        node* lower_bound(T key){return lower_bound(root,key);}
        node* upper_bound(T key){return upper_bound(root,key);}

        int rank(T key){return rank(root,key);}
    };
}

/**
 * @brief Sorted Set(AA Tree)
 */