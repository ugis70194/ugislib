#include<cassert>
#include<memory>
#include<array>
#include<iostream>

template<typename T>
class AVLTree{
private:
    class Node;
    using NodeRef = std::unique_ptr<Node>;
    NodeRef r;
    NodeRef rightRotate(NodeRef Y);
    NodeRef leftRotate(NodeRef X);
    
    class Node{
    private:
        T val;
        size_t sz;
        int64_t hei;
        std::array<NodeRef, 2> childlen;
    public:
        //constractor
        T& value();
        size_t size();
        int64_t height();
        NodeRef& child(size_t dir);

        int64_t diff();
        void fix();    
    };

public:
    // constractor
    NodeRef& search(T x); 
    void insert(T x);
    void remove(T x);
    size_t size();
};
