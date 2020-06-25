#include "nmlh_fixed_alloc.hpp"

namespace nmlh{
    void* page_sector::sbrk(size_t inc){
        if(inc == 0)
            return brk;

        if(brk + inc > (byte_t*)this + sector_size)
            return nullptr;

        brk += inc;

        return brk;
    }

    allocator::allocator(){
        first_sector = (page_sector*)mmap(nullptr, page_sector_default_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0);
        first_sector->sector_size = page_sector_default_size;
    }

    memory_block* allocator::request(page_sector* desired_sector, size_t size){
        // Get the current heap break of the current sector 
        memory_block* current_break = (memory_block*)current_sector->sbrk(0);

        // If you were able to increase the current heap break
        if(sbrk(size + sizeof(memory_block)) != nullptr){
            // Link the memory blocks
            if(current_sector->top_memory_block != nullptr)
                current_sector->top_memory_block->next_block = current_break;

            // Set the new top memory block
            current_sector->top_memory_block = current_break;

            // Set the block header, to the size, and set the used flag to true
            current_break->block_header &= size | 1;
            current_break->next_block = nullptr;

            // Return the old break
            return current_break;
        }
        
        return nullptr
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
        /*if(size + sizeof(page_sector) >= page_size){
            // mmap a new page sector
        }*/

        // Find a free block
        if(memory_block* free_block = find_free_block(size)){
            // Set the block to used
            free_block->blockInfo |= 1;
            return free_block->data();
        }

        page_sector* current_sector = first_sector;
        while(current_sector != nullptr){
            
            
            // Move to the next sector
            current_sector = current_sector->next_sector;
        }

        // Map general memory
        current_sector = (page_sector*)mmap(nullptr, page_sector_default_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0);
        current_sector->sector_size = page_sector_default_size;


    }
}