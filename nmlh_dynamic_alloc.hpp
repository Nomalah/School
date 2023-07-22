#pragma once

#include <cstddef>
#include <cstdint>
#include <unistd.h>
#include <sys/mman.h>

namespace nmlh{
    const size_t KB = 1024;
    const size_t MB = 1024 * KB;
    const size_t GB = 1024 * MB;
    const size_t TB = 1024 * GB;

    typedef unsigned char byte_t;
    typedef uintptr_t word_t;

    /**
     * @brief This is the struct that directly precedes user memory.
     * @details This structure encapsulates a memory block, and the
     *          raw user memory will follow directly after this struct.
     */
    struct memory_block{
        /**
         * @brief Memory Block Header, contains the size of the data, and flags.
         * @details There are 3 flags on x64 and 2 flags on x86, due to memory alignment,
         *          implemented functions only use 2 flags to maintain compatability with x86.
         */
        size_t block_header = 0;

        /**
         * @brief Pointer to the next memory block.
         * @details The memory blocks are stored in a linked list type format, 
         *          with each of the starts of the lists tied to a page sector.
         * @sa page_sector
         */
        memory_block* next_block = nullptr;

        /**
         * @brief Returns if the memory block is currently in use.
         * @note Function is inline & const
         * @return bool
         */
        inline bool used() const {return block_header & 1;}

        /**
         * @brief Returns if the memory block is in a private page sector
         * @note Function is inline & const
         * @return bool
         */
        inline bool private_sector() const {return block_header & 2;}

        /**
         * @brief Returns the size of the memory block data in bytes
         * @note Function is inline & const
         * @return std::size_t - size of the data that the memory block encapsulates
         */
        inline size_t size() const {return block_header & ~(sizeof(word_t) - 1);}

        /**
         * @brief Returns the location of this memory block's data
         * @note Function is inline & const
         * @return byte_t* - pointer to the start of the user's data
         */
        inline byte_t* data() const {return (byte_t*)(this + 1);}
    };

    // The sectors are linked together.
    struct page_sector{
        size_t sector_size = 0; // Full Sector Size
        page_sector* previous_sector = nullptr;
        page_sector* next_sector = nullptr;
        memory_block* top_memory_block = nullptr;
        byte_t* brk = (byte_t*)this + sizeof(page_sector);

        void* sbrk(size_t inc);
        memory_block* request(size_t size);
        inline memory_block* first_block() const {return (memory_block*)(this + 1);}
    };

    

    class allocator{
        private:    
            memory_block* find_free_block(size_t block_size){return nullptr;}
            static memory_block* get_memory_block(void* data_ptr){return (memory_block*)data_ptr - 1;}
            static size_t align(size_t size){return (size + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);}
        public:
            allocator();
            ~allocator();

            template<class C>
            [[nodiscard]] C* alloc(size_t count);
           
            template<class C>
            void dealloc(C* free_ptr);

            /*
            The library has a specialization for the void-type

            template<>
            void* alloc<void>(size_t size);
            template<>
            void dealloc<void>(void*& free_ptr);
            */

        private:
            page_sector* first_sector = nullptr;
            page_sector* top_sector = nullptr;
            size_t page_size = getpagesize();
            size_t page_sector_default_size = page_size * 256;
            const size_t private_page_size_cutoff = page_size;
    };
}

// Include the implementation of the template functions
#include "nmlh_dynamic_alloc_imp.hpp"