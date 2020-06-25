#include "nmlh_dynamic_alloc.hpp"

#ifdef NMLH_DEBUG
    #include <iostream>
#endif

namespace nmlh{
    void* page_sector::sbrk(size_t inc){
        if(inc == 0)
            return brk;

        if(brk + inc > (byte_t*)this + sector_size)
            return nullptr;

        brk += inc;

        return brk;
    }

    memory_block* page_sector::request(size_t size){
        // Get the current heap break of the current sector 
        memory_block* current_break = (memory_block*)sbrk(0);

        // If you were able to increase the current heap break
        if(sbrk(size + sizeof(memory_block)) != nullptr){
            // Link the memory blocks
            if(top_memory_block != nullptr)
                top_memory_block->next_block = current_break;

            // Set the new top memory block
            top_memory_block = current_break;

            // Set the block header, to the size, and set the used flag to true
            current_break->block_header &= size | 1;
            current_break->next_block = nullptr;

            // Return the old break
            return current_break;
        }
        return nullptr;
    }

    allocator::allocator(){}

    allocator::~allocator(){
        page_sector* current_sector = first_sector;
        while(current_sector != nullptr){
            page_sector* next_sector = current_sector->next_sector;
            munmap(current_sector, current_sector->sector_size);
            current_sector = next_sector;
        }
    }

    template<class C>
    C* allocator::alloc(size_t count){
        // alloc<void> is a raw allocation
        C* result = (C*)alloc<void>(count * sizeof(C));
        
        // You can only construct the object if it's at a valid memory address
        if(result)
            // For the count of objects
            for(size_t i = 0; i < count; i++)
                // Placement new: to construct the object, in place
                new (result + i) C();
        
        // Will return nullptr or a valid memory address
        return result;
    }

    template<>
    void* allocator::alloc<void>(size_t size){
        // You can't allocate 0 bytes
        if(size == 0)
            return nullptr;

        // Align the requested size
        size = align(size);

        if(size_t allocate_size = size + sizeof(page_sector) + sizeof(memory_block); allocate_size >= page_size){
            // mmap a new private page sector
            page_sector* private_sector = (page_sector*)mmap(nullptr, allocate_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
            if(private_sector == MAP_FAILED)
                return nullptr;

            *private_sector = {allocate_size, nullptr, nullptr, (byte_t*)private_sector + sizeof(page_sector)};

            private_sector->top_memory_block = private_sector->first_block();
            *private_sector->top_memory_block = {size, nullptr};
            return private_sector->top_memory_block->data();
        }
        
        // Find a free block
        if(memory_block* free_block = find_free_block(size); free_block != nullptr){ // Currently only returns nullptr
            // Set the block to used
            free_block->block_header |= 1;
            return free_block->data();
        }


        page_sector* current_sector = first_sector;
        while(current_sector != nullptr){
            memory_block* allocated_block = current_sector->request(size);

            if(allocated_block != nullptr)
                return allocated_block;
            
            // Move to the next sector
            current_sector = current_sector->next_sector;
        }

        // Could not find any available memory in previously allocated page sectors

        // Memory map a new page sector
        current_sector = (page_sector*)mmap(nullptr, page_sector_default_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
        if(current_sector == MAP_FAILED)
            return nullptr;

        current_sector->sector_size = page_sector_default_size;
        *current_sector = {page_sector_default_size, nullptr, nullptr, (byte_t*)current_sector + sizeof(page_sector)};

        if(first_sector == nullptr)
            first_sector = current_sector;

        if(top_sector != nullptr)
            top_sector = current_sector;

        top_sector = current_sector;

        memory_block* result = current_sector->request(size);
        if(result == nullptr)
            return nullptr;
        return result->data();
    }

    template<class C>
    void allocator::free(C*& free_ptr){   
        // You can only destroy the objects if they exist
        if(free_ptr != nullptr){
            memory_block* free_ptr_memory_block = get_memory_block(free_ptr);

            // For the count of objects
            for(size_t i = 0; i < free_ptr_memory_block->size / sizeof(C); i++)
                // Destroy each of the objects
                (result + i)->~C();
        
            // Free the raw memory
            free<void>(free_ptr);
        }
    }

    template<>
    void allocator::free<void>(void*& free_ptr){
        if(free_ptr != nullptr){
            memory_block* free_ptr_memory_block = get_memory_block(free_ptr);

            if(free_ptr_memory_block->private_sector()){
                page_sector* private_page_sector = (page_sector*)free_ptr_memory_block - 1;
                munmap(private_page_sector, private_page_sector->sector_size);
            }else{
                free_ptr_memory_block->block_header &= ~1;
            }

            free_ptr = nullptr;
        }
    }
}