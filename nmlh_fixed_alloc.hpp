#pragma once 

//#define DEBUG

#if defined(__APPLE__)
    #include <sys/mman.h>
    #include <unistd.h>
    #include <iostream>
    #include <stdint.h>
#endif

namespace nmlh{
    typedef unsigned long long nmlhsize_t;
    const nmlhsize_t KB = 1024;
    const nmlhsize_t MB = 1024 * KB;
    const nmlhsize_t GB = 1024 * MB;
    const nmlhsize_t TB = 1024 * GB;

    struct memBlock{
        nmlhsize_t blockInfo;
        memBlock* nextBlock;

        inline nmlhsize_t size(){return blockInfo & ~7;}
        inline bool used(){return blockInfo & 1;}
        [[maybe_unused]] inline bool flag2(){return blockInfo & 2;}
        [[maybe_unused]] inline bool flag3(){return blockInfo & 4;}
        inline nmlhsize_t flags(){return blockInfo & 7;}
    };
    
    inline nmlhsize_t align(nmlhsize_t size){ 
        return (size + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
    }

    memBlock* getMemBlock(void* ptr){
        return (memBlock*)((unsigned char*)ptr - sizeof(memBlock));
    }

    class allocator{
        private:
            unsigned char* heap;
            nmlhsize_t size;
            unsigned char* brk;
            memBlock* listStart = nullptr;
            memBlock* listTop = listStart;
        public:
            allocator();
            template<typename T>
            T* alloc(nmlhsize_t length);

            template<typename T>
            void free(T*& freePtr);
        private:
            void* sbrk(nmlhsize_t inc);
            memBlock* request(nmlhsize_t size);
            void* genAlloc(nmlhsize_t sizeInBytes);
            memBlock* findBlock(nmlhsize_t size);
    };
}

namespace nmlh{

    allocator::allocator(){
        size = 4 * MB;
        heap = (unsigned char*)mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0);
        brk = (unsigned char*)heap;
    }

    void* allocator::sbrk(nmlhsize_t inc){
        if(inc == 0)
            return brk;

        if(brk + inc > heap + size)
            return nullptr;

        brk += inc;

        return brk;
    }

    template<typename T>
    T* allocator::alloc(nmlhsize_t length){
#ifdef DEBUG
        std::cerr << "Allocating: " << sizeof(T) * length  << " bytes" << std::endl;
#endif
        return (T*)genAlloc(sizeof(T) * length);
    }

    void* allocator::genAlloc(nmlhsize_t sizeInBytes){
        if(sizeInBytes == 0)
            return nullptr;

        sizeInBytes = align(sizeInBytes);

        // Check Free list
        if(memBlock* allocBlock = findBlock(sizeInBytes)){
            // set the block to used
            allocBlock->blockInfo |= 1;
            return allocBlock + 1;
        }

#ifdef DEBUG
        std::cerr << "Requesting: " << sizeInBytes << " bytes" << std::endl;
#endif
        memBlock* allocBlock = request(sizeInBytes);

        allocBlock->blockInfo = sizeInBytes | 1;

#ifdef DEBUG
        std::cerr << "Allocation at: " << allocBlock << std::endl;
#endif

        if(listStart == nullptr)
            listStart = allocBlock;

        if(listTop != nullptr)
            listTop->nextBlock = allocBlock;

        listTop = allocBlock;

        return allocBlock + 1;
    }

    memBlock* allocator::findBlock(nmlhsize_t desiredSize){
        memBlock* curBlock = listStart;

        while(curBlock != nullptr){
            if(!curBlock->used() && curBlock->size() >= desiredSize)
                return curBlock;

            curBlock = curBlock->nextBlock;
        }
#ifdef DEBUG
        std::cerr << "Could not find available block!" << std::endl;
#endif
        return nullptr;
    } 

    template<typename T>
    void allocator::free(T*& freePtr){
        getMemBlock(freePtr)->blockInfo &= ~1;
#ifdef DEBUG
        std::cerr << "Freed " << freePtr << std::endl;
#endif
        freePtr = nullptr;
    }

    memBlock* allocator::request(nmlhsize_t size){
        memBlock* req = (memBlock*)sbrk(0);
#ifdef DEBUG
        std::cerr << "Current Break: " << req << std::endl;
        std::cerr << "Move Break By: " << size + sizeof(memBlock) << std::endl;
#endif

        if(sbrk(sizeof(memBlock) + size) == nullptr){
            #ifdef DEBUG
                std::cerr << "Out Of Memory" << std::endl;
            #endif
            return nullptr;
        }
#ifdef DEBUG
        std::cerr << "New Break: " << sbrk(0) << std::endl;
#endif

        return req;
    }
}