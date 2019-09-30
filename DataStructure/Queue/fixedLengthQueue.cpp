#include<memory>
#include<cassert>

template<typename T>
class Queue{
private:
    std::unique_ptr<T[]> arr_;
    size_t length_;
    size_t front_ptr_;
    size_t back_ptr_;
    size_t next_(size_t ptr) const {
        return (ptr + 1) % length_; 
    }
public:
    Queue(size_t length=100){
        length_ = length + 1; // +1 is buffer
        arr_.reset(new T[length_]);
        front_ptr_ = 0;
        back_ptr_ = 0;
    }
    ~Queue(){
        arr_.reset();
    }

    bool empty() const {
        return front_ptr_ == back_ptr_;
    }

    size_t length() const {
        return length_;
    } 

    void push(T element){
        assert(next_(back_ptr_) != front_ptr_);

        arr_[back_ptr_] = element;
        back_ptr_ = next_(back_ptr_);
    }

    void pop(){
        assert(!empty());

        front_ptr_ = next_(front_ptr_);
    }

    T front() const {
        assert(!empty());

        return arr_[front_ptr_];
    }
};