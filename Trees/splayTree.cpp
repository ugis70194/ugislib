#include<iostream>
#include<memory>
#include<cstdint>
#include<random>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

template<typename T>
class RandomizedQueue{
private:
    std::random_device seed_gen;
    std::mt19937_64 rng;
    std::vector<T> que;
    size_t len;
public:
    RandomizedQueue() : len(0), rng(seed_gen()) {}
    RandomizedQueue(std::vector<T>& vec) : rng(seed_gen()){
        que = vec;
        len = que.size();
    }
    RandomizedQueue(int begin, int end) : len(end - begin + 1), rng(seed_gen()){
        que.reserve(end - begin + 1);
        for(int i = begin; i <= end; ++i){
            que.emplace_back(i);
        }
    }

    void push(T n){
        if(len + 1 > que.size()) que.resize(2*que.size());
        que[len] = n;
        ++len;
    }

    void push(size_t begin, size_t end){
        if(len + (end-begin+1) > que.size()) que.resize(2*(len+(end-begin+1)));
        for(size_t i = begin; i <= end; ++i){
            que[len] = i;
            len++;
        }
    }

    void push(std::vector<T>& vec){
        if(len + vec.size() > que.size()) que.resize(2*(len+vec.size()));
        for(size_t i = 0; i < vec.size(); ++i){
            que[len] = vec[i];
            ++len;
        }
    }

    T pop(){
        assert(len > 0);
        size_t idx = rng() % len;
        std::swap(que[idx], que[len-1]);
        --len;
        if(len < que.size() / 3) que.resize(que.size() / 2);
        return que[len];
    }

    size_t size() {
        return size;
    }
};

template<typename T> 
class SplayTree_Set{
/*
private:
    class Node;
    void rotate_right(Node<T>* node);
    void rotate_left(Node<T>* node);
    void zig(Node<T>* node);
    void zig_zag(Node<T>* node);
    void zig_zig(Node<T>* node);
    Node<T>* make_node(T val);
    void splay(Node<T>* node);
    void insert_node(Node<T>* node);
    void remove_node(Node<T>* node);
    bool find_node(Node<T>* node);
    Node<T>* root;
public:
    SplayTree_Set() : root(nullptr) {}
    void insert(T val);
    void remove(T val);
    bool contains(T val);
    T lower_bound(T val);
    T upper_bound(T val);
*/
private:
    template<typename U = T>
    class Node{
    public:
        Node<U>* par;
        Node<U>* left; 
        Node<U>* right;
        T value;
        Node() : par(nullptr), left(nullptr), right(nullptr){}
    };
private:
    void rotate_right(Node<T>* node){
        Node<T>* par = node->par;
        Node<T>* gra = par->par;
        if(gra != nullptr){
            if(gra->left == par) gra->left = node;
            else gra->right = node;
        }
        par->par = node;
        par->left = node->right;

        node->par = gra;
        node->right = par;

        if(node->par == nullptr) root = node;
    }
    void rotate_left(Node<T>* node){
        Node<T>* par = node->par;
        Node<T>* gra = par->par;
        if(gra != nullptr){
            if(gra->left == par) gra->left = node;
            else gra->right = node;
        }
        par->par = node;
        par->right = node->left;

        node->par = gra;
        node->left = par;

        if(node->par == nullptr) root = par;
    }
    void zig(Node<T>* node){
        Node<T>* par = node->par;
        if(par->left == node) rotate_right(node);
        else rotate_left(node);
    }
    void zig_zag(Node<T>* node){
        Node<T>* par = node->par;
        if(par->left == node){
            rotate_right(node);
            rotate_left(node);
        } else {
            rotate_left(node);
            rotate_right(node);            
        }
    }
    void zig_zig(Node<T>* node){
        Node<T>* par = node->par;
        if(par->left == node){
            rotate_right(par);
            rotate_right(node);
        } else {
            rotate_left(par);
            rotate_left(node);
        }
    }
    Node<T>* make_node(T val, Node<T>* par){
        Node<T>* node = new Node<T>();
        node->value = val;
        node->par = par;
        return node;
    }
private:
    void splay(Node<T>* node){
        while(node->par) {
            Node<T>* par = node->par;
            if(par == root) zig(node);
            else{
                bool zigzag = false;
                Node<T>* gra = par->par;
                if(gra->left == par) zigzag ^= 1;
                if(par->left == node) zigzag ^= 1;
                if(zigzag) zig_zag(node);
                else zig_zig(node);
            }
        }
    }
    
public:
    Node<T>* root;
    SplayTree_Set() : root(nullptr) {}
    void insert(T val){
        Node<T>* leaf = root;
        bool end = false;
        if(root == nullptr){
            root = make_node(val, nullptr);
            return;
        }
        while(!end){
            if(leaf->value < val) {
                if(leaf->right == nullptr) end = true;
                else leaf = leaf->right;
            }
            else {
                if(leaf->left == nullptr) end = true;
                else leaf = leaf->left;
            }
        }

        Node<T>* node = make_node(val, leaf);
        if(leaf->value < val && !leaf->right) leaf->right = node;
        else if(leaf->value >= val && !leaf->left) leaf->left = node;
        cout << "asdf1" << endl;
        splay(node);
    }
    bool find(T val){
        Node<T>* node = root;
        bool found = false;
        while(!found){
            if(node->value == val) found = true;
            else if(node->value < val && node->right) node = node->right;
            else if(node->value >= val && node->left) node = node->left; 
            else break;
        }
        if(found) splay(node);
        return found; 
    }
    void remove(T val);
    bool contains(T val);
    T lower_bound(T val);
    T upper_bound(T val);
    void test(Node<T>* node = nullptr){
        if(!node) node = root;
        cout << "isRoot " << (node == root) << "value: "<<node->value << endl;
        if(node->left) test(node->left);
        if(node->right) test(node->right);
    }
};

int main(){
    int N;
    cin >> N;
    SplayTree_Set<int> spTree;
    RandomizedQueue<int> que(1, 1333);
    RandomizedQueue<int> Q(1, 1333);

    for(int i = 0; i < N; i++){
        int k = que.pop();
        spTree.insert(que.pop());
        cout << "insert: " << k << endl;
        cout << "root: "<< spTree.root->value << endl;
    }
    for(int i = 0; i < N; i++){
        //int k = Q.pop();
        //cout << k << " find: " << spTree.find(k) << endl;
    }
}
