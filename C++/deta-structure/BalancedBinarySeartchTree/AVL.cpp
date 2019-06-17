#include<bits/stdc++.h>

 
template<typename T>
class Node{
public:
    T value;
    int64_t height;
    Node* left, right;
    Node() : value(0), height(1), left(nullptr), right(nullptr) {};
};

template<typename T>
class AVLTree{
public:
    class Node{
    public:
        T value;
        int64_t height;
        Node* left, right;
        Node() : value(0), height(1), left(nullptr), right(nullptr) {};
    };
private:
    Node<T>* root = nullptr;

    int64_t height(Node<T>* N){
        if(N == nullptr) return 0;
        return N->height;
    }

    Node<T>* newNode(T val){
        Node<T>* node = new Node<T>();
        node->value = val;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;

        return node;
    }

    Node<T>* rightRotate(Node<T>* Y){
        Node<T>* X = Y->left;
        Node<T>* T2 = X->right;

        X->right = Y;
        Y->left = T2;

        Y->height = std::max(height(Y->left), height(Y->right)) + 1;
        X->height = std::max(height(X->left), height(X->right)) + 1;
        
        return X;
    }

    Node<T>* leftRotate(Node<T>* X){
        Node<T>* Y = X->right;
        Node<T>* T2 = Y->left;

        Y->left = X;
        X->right = T2;

        X->height = std::max(height(X->left), height(X->left)) + 1;
        Y->height = std::max(height(Y->left), height(Y->right)) + 1;

        return Y;
    }

    int64_t diffHeightLR(Node<T>* N){
        if(N == nullptr) return 0;
        return height(N->left) - height(N->right);
    }

    Node<T>* setNode(Node<T>* node, T val){
        if(node == nullptr) return newNode(val);

        if(val < node->value) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int64_t balance = diffHeightLR(node);
        
        if(balance > 1 && val < node->left->value){
            return rightRotate(node);
        }
        if(balance < -1 && val > node->right->value){
            return leftRotate(node);
        }
        if(balance > 1 && val > node->left->value){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance < -1 && val < node->right->value){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T>* minValueNode(Node<T>* node){
        if(node->left != nullptr)  node = minValueNode(node->left);
        return node;
    }

    Node<T>* removeNode(Node<T>* node, T val){
        if(node == nullptr) return node;

        if(val < node->value){
            node->left = removeNode(node->left, val);
        }
        else if(val > node->value){
            node->right = remove(node->right, val);
        }
        else{
            if(node->left == nullptr && node->right == nullptr){
                node = nullptr;
            }
            else if(node->left == nullptr || node->right == nullptr){
                *node = node->left ? *(node->left) : *(node->right);
            }
        }


        if(node == nullptr) return node;

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int64_t balance = diffHeightLR(node);
        int64_t balanceL = diffHeightLR(node->left);
        int64_t balanceR = diffHeightLR(node->right);

        if(balance > 1 && balanceL >= 0){
            return rightRotate(node);
        }
        if(balance > 1 && balanceL < 0){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance < -1 && balanceR <= 0){
            return leftRotate(node);
        }
        if(balance < -1 && balanceR > 0){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T>* searchNode(Node<T>* node, T val){
        if(node == nullptr) return node;

        if(val < node->value) node = searchNode(node->left, val);
        else if(val > node->value) node = searchNode(node->right, val);

        return node;
    }

public:
    void insert(T val){ root = setNode(root, val); }
    void remove(T val){ root = removeNode(root, val); }
    Node<T>* search(T val) { return searchNode(root, val); }
    AVLTree() : root(nullptr);
};