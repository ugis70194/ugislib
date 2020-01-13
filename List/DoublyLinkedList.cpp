#include<iostream>
#include<unordered_set>
#include<cassert>
#include<memory>

template<typename T>
class Node{
public:
    Node* prev, next;
    T val;
    Node(){
        this->prev = nullptr;
        this->next = nullptr;
    }
    Node(Node* prev, Node* next, T val){
        this->prev = prev;
        this->next = next;
        this->val = val;
    }
};

template<typename T>
class DoublyLinkedList{
private:
    Node<T> dummy;
    size_t size;
public:
    DoublyLinkedList(){
        dummy.prev = &dummy;
        dummy.next = &dummy;
        size = 0;
    }

    Node<T>* getNode(size_t i){
        Node<T>* p;
        if(i < size / 2){
            p =  dummy.next;
            for(size_t j = 0; j < i; j++){
                p = p->next;
            }
        }
        else{
            p = &dummy;
            for(size_t j = size; j > i; j--){
                p = p->prev;
            }
        }
        return p;
    }

    T get(size_t i){
        return getNode(i)->val;
    }
    
    void set(size_t i, T val){
        Node<T>* p = getNode(i);
        p->val = val;
    }

    void add(size_t i, T val){
        Node<T>* p = getNode(i);
        Node<T>* n = new Node<T>;

        n->next = p;
        n->prev = p->prev;
        n->val = val;

        p->prev = n;
        p->prev->next = n;

        size++;
    }

    void remove(size_t i){
        Node<T>* p = getNode(i);
        p->next->prev = p->prev;
        p->prev->next = p->next;
        delete p;
        size--;
    }
};