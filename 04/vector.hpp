#pragma once

#include <stdlib.h>
#include <iterator>
#include <stddef.h>


template< class Iterator >
std::reverse_iterator<Iterator> makes_reverse_iterator(Iterator i){
    return std::reverse_iterator<Iterator>(i);
}

template<class T>
class Vector{
private:
    T* ptr;
    size_t size_;
    size_t capacity_;
    T default_val;
    bool have_val = false;

    void allocate(){
        if(size_ < capacity_)
            return;
        capacity_ = capacity_*2;
        ptr = (T*)realloc(ptr, sizeof(T)*capacity_);
        if(!ptr)
            throw std::runtime_error("need memory");
    }
public:

    class MyIterator: public std::iterator<std::input_iterator_tag, T, int64_t> {
        private:
            size_t i;
            T* p;
        public:
            MyIterator(T* ptr){
                p = ptr;
                i = 0;
            }
            MyIterator(T* ptr, size_t pos){
                p = ptr;
                i = pos;
            }
            typedef typename std::iterator<std::input_iterator_tag, T, int64_t>::pointer pointer;
            typedef typename std::iterator<std::input_iterator_tag, T, int64_t>::reference reference;
            typedef typename std::iterator<std::input_iterator_tag, T, int64_t>::difference_type difference_type;
            
            reference operator*() const {
                return p[i];
            }

            pointer operator->() const {
                return &p[i];
            }

            MyIterator& operator++() {
                ++i;
                return *this;
            }

            MyIterator& operator--() {
                --i;
                return *this;
            }

            MyIterator operator++(int) {
                return MyIterator(p, i++);
            }

            MyIterator operator--(int) { 
                return MyIterator(p, i--);
            }

            MyIterator operator+(const difference_type& n) const {
                return MyIterator(p, (i + n));
            }

            MyIterator& operator+=(const difference_type& n) {
                i += n;
                return *this;
            }

            MyIterator operator-(const difference_type& n) const {
                return MyIterator(p, (i - n));
            }

            MyIterator& operator-=(const difference_type& n) {
                i -= n;
                return *this;
            }

            reference operator[](const difference_type& n) const { return p[i + n]; }

            bool operator==(const MyIterator& other) const { return i == other.i; }

            bool operator!=(const MyIterator& other) const { return !(*this == other); }

            bool operator<(const MyIterator& other) const { return i < other.i; }

            bool operator>(const MyIterator& other) const { return !(*this < other || *this == other); }

            bool operator<=(const MyIterator& other) const { return !(*this > other); }

            bool operator>=(const MyIterator& other) const { return !(*this < other); }

            difference_type operator+(const MyIterator& other) const {
                return i + other.i;
            }

            difference_type operator-(const MyIterator& other) const {
                return i - other.i; 
            }
    };
        
    Vector(size_t n, T value){
        ptr =  (T*)malloc(n*sizeof(T));
        if(!ptr)
            throw std::runtime_error("need memory");
        for(size_t i = 0; i < n; ++i)
            ptr[i] = value;
        size_ = n;
        capacity_ = n;
        default_val = value;
        have_val = true;
    }

    Vector(size_t n){
        ptr = (T*)calloc(n, sizeof(T));
        if(!ptr)
            throw std::runtime_error("need memory");
        size_ = n;
        capacity_ = n;
    }

    Vector(){
        ptr = (T*)malloc(sizeof(T));
        size_ = 0;
        capacity_ = 1;
    }

    ~Vector(){
        if(!ptr)
            free(ptr);
    }

    T& operator[](size_t i);

    void push_back(T& value){
        allocate();
        ptr[size_] = value;
        ++size_;
    }

    void push_back(T&& value){
        allocate();
        ptr[size_] = value;
        ++size_;
    }

    template <typename... Args> 
    void emplace_back(Args&&... args) { 
        allocate();
        ptr[size_] = T(std::forward<Args>(args)...); 
        ++size_; 
    }

    void pop_back(){
        if(!size_)
            throw std::runtime_error("vector is empty");
        --size_;
    }

    void reserve(size_t n){
        if(n <= capacity_)
            return;
        
        T* t = (T*)realloc(ptr, sizeof(T)*n);
        if(!t)
            throw std::runtime_error("need memory");
        ptr = t;
        capacity_ = n;
    }

    void resize(size_t count){
        if(count > capacity_)
            reserve(count);
        if(have_val)
            for(size_t i = size(); i < count; ++i)
                ptr[i] = default_val;
        size_ = count;
        return;
    }

    bool empty(){
        return size_ == 0;
    }

    size_t size(){
        return size_;
    }

    void clear(){
        size_ = 0;
    }

    size_t capacity(){
        return capacity_;
    }

    MyIterator begin() {
        return MyIterator(ptr, 0);
    }

    MyIterator end() {
        return MyIterator(ptr, size_);
    }

    using reverse_iterator = std::reverse_iterator<MyIterator>;

    reverse_iterator rbegin(){
        return makes_reverse_iterator(end());
    }

    reverse_iterator rend(){
        return makes_reverse_iterator(begin());
    }
};

template<class T>
T& Vector<T>::operator[](size_t i){
    return ptr[i];
}