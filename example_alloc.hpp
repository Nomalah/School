#include <cstdlib>
#include <cstdint>
#include <unistd.h>
#include <utility>
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wdeprecated-declarations"

using word_t = intptr_t;
 

struct Block {
    size_t size;
    bool used;
    Block *next;
    word_t data[1];
};

static Block *heapStart = nullptr;
 
static auto top = heapStart;

inline size_t align(size_t n) {
  return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}

inline size_t allocSize(size_t size) {
  return size + sizeof(Block) - sizeof(std::declval<Block>().data);
}

Block *requestFromOS(size_t size) {
  auto block = (Block *)sbrk(0);                // (1)
 
  // OOM.
  if (sbrk(allocSize(size)) == (void *)-1) {    // (2)
    return nullptr;
  }
 
  return block;
}


word_t *alloc(size_t size) {
  size = align(size);
 
  auto block = requestFromOS(size);
 
  block->size = size;
  block->used = true;
 
  // Init heap.
  if (heapStart == nullptr) {
    heapStart = block;
  }
 
  // Chain the blocks.
  if (top != nullptr) {
    top->next = block;
  }
 
  top = block;
 
  // User payload:
  return block->data;
}

Block *getHeader(word_t *data) {
  return (Block *)((char *)data + sizeof(std::declval<Block>().data) -
                   sizeof(Block));
}