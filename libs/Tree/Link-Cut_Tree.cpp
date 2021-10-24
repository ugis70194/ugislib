
template<typename T>
class LinkCutTree{
private:
    template<typename U = T>
    struct Node{
        Node<U>* par;
        Node<U>* left;
        Node<U>* right;
        U val;

        bool is_root(){
            return par == nullptr || (par -> left != this && par -> right != this);
        }

        void rotate_right(){
            Node<U>* par_p = par; 
            Node<U>* gra_p = par->par;

            par_p->left = right;
            if(par_p->left != nullptr) par_p->left->par = par_p;
            par_p->par = this;
            right = par_p;
            par = gra_p;
            if(gra_p != nullptr){
                if(gra_p->left == par_p) gra_p->left = this;
                if(gra_p->right == par_p) gra_p->right = this;
            }
        }

        void rotate_left(){
            Node<U>* par_p = par; 
            Node<U>* gra_p = par->par;

            par_p->right = left;
            if(par_p->right != nullptr) par_p->right->par = par_p;
            par_p->par = this;
            left = par_p;
            par = gra_p;
            if(gra_p != nullptr){
                if(gra_p->left == par_p) gra_p->left = this;
                if(gra_p->right == par_p) gra_p->right = this;
            }
        }

        void splay(){
            while(is_root() == false){
                Node<U>* par_p = par;
                if(par_p->is_root()){
                    if(par_p->left == this) rotate_right();
                    if(par_p->right == this) rotate_left();
                } else {
                    Node<U>* gra_p = par_p->par;
                    bool zigzag = false;
                    if(par_p->left == this) zigzag ^= 1;
                    if(gra_p->left == par_p) zigzag ^= 1;
                    if(zigzag){
                        if(par_p->left == this){rotate_right(); rotate_left();}
                        if(par_p->right == this){rotate_left(); rotate_right();}
                    } else {
                        if(par_p->left == this){par_p->rotate_right(); rotate_right();}
                        if(par_p->right == this){par_p->rotate_left(); rotate_left();}
                    }
                }
            }
        }
    };

    Node<T>*  expose(Node<T>* node){
        Node<T>* right_p = nullptr;
        for(Node<T>* x = node; x != nullptr; x = x->par){
            x->splay();
            x->right = right_p;
            right_p = x;
        }
        node->splay();
        return node;
    }

    void cut(Node<T>* x){
        expose(x);
        Node<T>* par_p = x->left;
        x->left = nullptr;
        par_p->par = nullptr;
    }

    void link(Node<T>* x, Node<T>* p){
        expose(p);
        expose(x);
        p->right = x;
        x->par = p;
    }
};