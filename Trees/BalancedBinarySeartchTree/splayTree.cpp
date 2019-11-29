
template<typename T> 
class SplayTree_Set{
private:
    template<typename U = T>
    class Node{
    public:
        Node<U>* par;
        Node<U>* left; 
        Node<U>* right;
        T value;
        size_t sub;
        Node() : par(nullptr), left(nullptr), right(nullptr){}
    };
private:
    void rotate_right(Node<T>* node){
        Node<T>* child = node->left;
        Node<T>* par = node->par;
        if(root == node) root = child;
        else {
            if(par->left == node) par->left = child;
            else par->right = child;
        }
        child->par = par;
        node->left = child->right;
        if(child->right) child->right->par = node;
        child->right = node;
        node->par = child;
    }
    void rotate_left(Node<T>* node){
        Node<T>* child = node->right;
        Node<T>* par = node->par;
        if(root == node) root = child;
        else {
            if(par->left == node) par->left = child;
            else par->right = child;
        }
        child->par = par;
        node->right = child->left;
        if(child->left) child->left->par = node;
        child->left = node;
        node->par = child;
    }
    void zig(Node<T>* node){
        if(node->par->left == node) rotate_right(node->par);
        else rotate_left(node->par);
    }
    void zig_zag(Node<T>* node){
        if(node->par->left == node){
            rotate_right(node->par);
            rotate_left(node->par);
        } else {
            rotate_left(node->par);
            rotate_right(node->par);            
        }
    }
    void zig_zig(Node<T>* node){
        if(node->par->left == node){
            rotate_right(node->par->par);
            rotate_right(node->par);
        } else {
            rotate_left(node->par->par);
            rotate_left(node->par);
        }
    }
    Node<T>* make_node(T val, Node<T>* par){
        Node<T>* node = new Node<T>();
        node->value = val;
        node->par = par;
        return node;
    }
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
    T at(int k){
        assert(size() > k);
        Node<T>* node = root;
        int idx = 0;
        while(k != idx){
            if(node->left != nullptr) idx = node->left->sub;
            else idx = 0;

            if(k == idx) return node->value;
            if(k < idx) node = node->left; 
            if(k > idx) {k -= (idx+1); node = node->right;}
        }
        return node->value;
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
            if(leaf->value == val) return;
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
        splay(node);
    }
    bool contains(T val){
        Node<T>* node = root;
        while(1){
            if(node->value == val){
                splay(node);
                return true;
            } 
            else if(node->value < val && node->right) node = node->right;
            else if(node->value >= val && node->left) node = node->left; 
            else{
                splay(node);
                return false;
            }
        }
        return false;
    }
    void remove(T val){
        if(!contains(val)) return;
        Node<T>* right = nullptr;
        Node<T>* left = nullptr;
        if(root->right){
            right = root->right;
            right->par = nullptr;
        }
        if(root->left){
            left = root->left;
            left->par = nullptr;
        }
        delete root;
        if(right && left){
            root = right;
            Node<T>* leaf = right;
            while(leaf->left != nullptr) leaf = right->left;
            leaf->left = left;
            left->par = leaf;
            splay(left);
        } else if(left){
            root = left;
        } else if(right){
            root = right;
        } else {
            root = nullptr;
        }
    }
    size_t find(T val);
    T lower_bound(T val);
    T upper_bound(T val);
    void test(Node<T>* node = nullptr){
        if(!node) node = root;
        cout << "value: "<<node->value << endl;
        if(node->left) test(node->left);
        if(node->right) test(node->right);
    }
};