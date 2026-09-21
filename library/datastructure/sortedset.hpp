#pragma once

#include <cstddef>
#include <iterator>
using namespace std;

namespace nskr{
    
    template<typename T>
    struct sortedset{
        // https://kuronosu1024.github.io/libs/docs/datastructure/sortedset.html
        struct node{
            T key;
            int level;
            node *left, *right, *parent;
            int lcount, rcount;
            
            node(T x) :key(x), level(0), left(nullptr), right(nullptr), parent(nullptr), lcount(0), rcount(0){}
            node() :key(), level(0), left(nullptr), right(nullptr), parent(nullptr), lcount(0), rcount(0){}
        };

        class const_iterator;

        class iterator{
            sortedset* owner;
            node* current;

            iterator(sortedset* owner, node* current)
                : owner(owner), current(current){}

            friend struct sortedset;
            friend class const_iterator;

        public:
            using difference_type = ptrdiff_t;
            using value_type = T;
            using pointer = const T*;
            using reference = const T&;
            using iterator_category = bidirectional_iterator_tag;

            iterator() : owner(nullptr), current(nullptr){}

            reference operator*() const { return current->key; }
            pointer operator->() const { return &current->key; }

            iterator& operator++(){
                if(current == nullptr) return *this;
                if(current->right != nullptr){
                    current = current->right;
                    while(current->left != nullptr) current = current->left;
                    return *this;
                }
                node* child = current;
                current = current->parent;
                while(current != nullptr && child == current->right){
                    child = current;
                    current = current->parent;
                }
                return *this;
            }

            iterator operator++(int){
                iterator ret = *this;
                ++*this;
                return ret;
            }

            iterator& operator--(){
                if(current == nullptr){
                    current = owner->root;
                    if(current != nullptr){
                        while(current->right != nullptr) current = current->right;
                    }
                    return *this;
                }
                if(current->left != nullptr){
                    current = current->left;
                    while(current->right != nullptr) current = current->right;
                    return *this;
                }
                node* child = current;
                current = current->parent;
                while(current != nullptr && child == current->left){
                    child = current;
                    current = current->parent;
                }
                return *this;
            }

            iterator operator--(int){
                iterator ret = *this;
                --*this;
                return ret;
            }

            bool operator==(const iterator& x) const{
                return owner == x.owner && current == x.current;
            }

            bool operator!=(const iterator& x) const{
                return !(*this == x);
            }
        };

        class const_iterator{
            const sortedset* owner;
            node* current;

            const_iterator(const sortedset* owner, node* current)
                : owner(owner), current(current){}

            friend struct sortedset;

        public:
            using difference_type = ptrdiff_t;
            using value_type = T;
            using pointer = const T*;
            using reference = const T&;
            using iterator_category = bidirectional_iterator_tag;

            const_iterator() : owner(nullptr), current(nullptr){}
            const_iterator(const iterator& x) : owner(x.owner), current(x.current){}

            reference operator*() const { return current->key; }
            pointer operator->() const { return &current->key; }

            const_iterator& operator++(){
                iterator x(const_cast<sortedset*>(owner), current);
                ++x;
                current = x.current;
                return *this;
            }

            const_iterator operator++(int){
                const_iterator ret = *this;
                ++*this;
                return ret;
            }

            const_iterator& operator--(){
                iterator x(const_cast<sortedset*>(owner), current);
                --x;
                current = x.current;
                return *this;
            }

            const_iterator operator--(int){
                const_iterator ret = *this;
                --*this;
                return ret;
            }

            bool operator==(const const_iterator& x) const{
                return owner == x.owner && current == x.current;
            }

            bool operator!=(const const_iterator& x) const{
                return !(*this == x);
            }
        };

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        
        node* sentinel;  // == st.end()

        private:
        
        node* root;

        void destroy(node* x){
            if(x == nullptr) return;
            destroy(x->left);
            destroy(x->right);
            delete x;
        }
        
        node* skew(node* x){ //左同levelを解決
            if(x==nullptr) return nullptr;
            if(x->left==nullptr) return x;
            if(x->left->level==x->level){
                node* leftnode = x->left;
                leftnode->parent = x->parent;
                x->left = leftnode->right;
                if(x->left != nullptr) x->left->parent = x;
                leftnode->right = x;
                x->parent = leftnode;
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
                rightnode->parent = x->parent;
                x->right = rightnode->left;
                if(x->right != nullptr) x->right->parent = x;
                rightnode->left = x;
                x->parent = rightnode;
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
                x->right->parent = x;
            }else if(x->key > key){
                x->left  = insert(x->left , key);
                x->left->parent = x;
            } else return x;
            setcount(x);
            return split(skew(x));
        }

        node* erase(node* x, T key){
            if(x == nullptr) return nullptr;
            if(key < x->key) {
                x-> left = erase(x->left, key);
                if(x->left != nullptr) x->left->parent = x;
            }else if(key > x->key){
                x->right=erase(x->right, key);
                if(x->right != nullptr) x->right->parent = x;
            }else{
                if(x->left == nullptr){
                    node* ret = x->right;
                    if(ret != nullptr) ret->parent = x->parent;
                    delete x;
                    return ret;
                }
                if(x->right == nullptr){
                    node* ret = x->left;
                    if(ret != nullptr) ret->parent = x->parent;
                    delete x;
                    return ret;
                }
                node* tgt = x->right;
                while(tgt->left != nullptr) tgt = tgt->left;
                x->key = tgt->key;
                x->right = erase(x->right, tgt->key);
                if(x->right != nullptr) x->right->parent = x;
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
                x->right->parent = x;
                if(x->right->right != nullptr) x->right->right = skew(x->right->right);
                if(x->right->right != nullptr) x->right->right->parent = x->right;
            }

            x = split(x);
            if(x->right != nullptr){
                x->right = split(x->right);
                x->right->parent = x;
            }

            return x;
        }



        node* get(node* x, int t){
            if(x==nullptr) return nullptr;
            if(x->lcount < t) return get(x->right, t-x->lcount-1);
            if(x->lcount > t) return get(x->left, t);
            return x;
        }

        node* find(node* x, T key) const {
            if(x==nullptr) return sentinel;
            if(x->key < key) return find(x->right, key);
            if(x->key > key) return find(x->left, key);
            return x;
        }

        node* lower_bound(node* x, T key) const {//key以上の最小
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

        node* upper_bound(node* x, T key) const {//key超過の最小
            if(x == nullptr)return sentinel;
            if(!(x->key > key)){
                return upper_bound(x->right, key);
            }if(!(x->key < key)){
                node* ret = upper_bound(x->left, key);
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
            // ここに来ることは仕様上ないはずだが、コンパイルエラーがうるさいので一応
            return -1;
        }
        
        public:


        
        sortedset():sentinel(nullptr),root(nullptr){}
        ~sortedset(){destroy(root);}

        sortedset(const sortedset&) = delete;
        sortedset& operator=(const sortedset&) = delete;
        
        const T operator[](int t){
            node* x = get(root, t);
            if(x==nullptr) return T();
            else return x->key;
        }

        size_t size(){
            if(root==nullptr)return 0;
            return root->lcount + root->rcount + 1;
        }

        void insert(T key){
            root = insert(root, key);
            if(root != nullptr) root->parent = nullptr;
        }

        void erase(T key){
            root = erase(root, key);
            if(root != nullptr) root->parent = nullptr;
        }

        iterator find(T key){
            node* x = find(root, key);
            return iterator(this, x);
        }

        const_iterator find(T key) const {
            node* x = find(root, key);
            return const_iterator(this, x);
        }

        size_t count(T key){
            node* x = find(root, key);
            if(x == sentinel) return 0;
            return 1;
        }

        iterator begin(){
            node* x = root;
            while(x != nullptr && x->left != nullptr) x = x->left;
            return iterator(this, x);
        }

        iterator end(){return iterator(this, nullptr);}

        const_iterator begin() const{
            node* x = root;
            while(x != nullptr && x->left != nullptr) x = x->left;
            return const_iterator(this, x);
        }

        const_iterator end() const{return const_iterator(this, nullptr);}

        const_iterator cbegin() const{return begin();}
        const_iterator cend() const{return end();}

        reverse_iterator rbegin(){return reverse_iterator(end());}
        reverse_iterator rend(){return reverse_iterator(begin());}

        const_reverse_iterator rbegin() const{
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend() const{
            return const_reverse_iterator(begin());
        }

        const_reverse_iterator crbegin() const{
            return const_reverse_iterator(end());
        }

        const_reverse_iterator crend() const{
            return const_reverse_iterator(begin());
        }
        
        iterator lower_bound(T key){return iterator(this,lower_bound(root,key));}
        iterator upper_bound(T key){return iterator(this,upper_bound(root,key));}
        
        const_iterator lower_bound(T key) const {return const_iterator(this,lower_bound(root,key));}
        const_iterator upper_bound(T key) const {return const_iterator(this,upper_bound(root,key));}
 
        int rank(T key){return rank(root,key);}
    };

}

/**
 * @brief ランダムアクセス可能なSet (AA Tree)
 */
