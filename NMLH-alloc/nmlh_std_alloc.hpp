#pragma once

#include <cstddef>
#include <cstdlib>
#include <memory>

namespace nmlh{
    template<class T>
    class allocator{
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef const T* const_pointer;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        template<class U>
        struct rebind{
            typedef allocator<U> other;
        };

        allocator(){}
        ~allocator(){}

        pointer address(reference x) const {return &x;}
        const_pointer address(const_reference x) const {return &x;}
        size_type max_size() const noexcept {return size_type(-1) / sizeof(value_type);}

        pointer allocate(size_type n, allocator<void>::const_pointer hint = 0){
            return (pointer)malloc(n * sizeof(value_type));
        }

        void deallocate(pointer p, size_type n){
            free(p);
        }

        template<class U, class... Args>
        void construct(U* p, Args&&... args){new (p) U (forward<Args>(args)...);}

        template<class U, class... Args>
        void destroy(U* p, Args&&... args){p->~U();}
    };
}