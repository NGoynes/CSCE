#include "Ackerman.h"
#include "BuddyAllocator.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

void easytest(BuddyAllocator* ba){
  // be creative here
  // know what to expect after every allocation/deallocation cycle

  // here are a few examples
  ba->printlist();
  // allocating a byte
  char * mem = ba->alloc (1);
  // now print again, how should the list look now
  ba->printlist ();

  ba->free (mem); // give back the memory you just allocated
  ba->printlist(); // shouldn't the list now look like as in the beginning

}


int main(int argc, char ** argv) {

  int basic_block_size = 128, memory_length = 128 * 1024 * 1024, args;
  bool sizeStatus = true;

  while((args = getopt(argc, argv, "b:s:")) != -1) {
    switch(args) {
      case 'b':
        basic_block_size = atoi(optarg);
        std::cout << "Size of Basic Block: " << basic_block_size << std::endl;
        break;
      case 's':
        memory_length = atoi(optarg);
        std::cout << "Size of Memory Length: " << memory_length << std::endl;
        break;
      case '?':
        std::cout << "Error: Command Arguments Invalid" << std::endl;
    }
  }

  if(basic_block_size > memory_length) {
    std::cout << "Please enter a block size less than the memory length" << std::endl;
    sizeStatus = false;
  }

  if(sizeStatus) {
    // create memory manager
    BuddyAllocator * allocator = new BuddyAllocator(basic_block_size, memory_length);

    // stress-test the memory manager, do this only after you are done with small test cases
    Ackerman* am = new Ackerman ();
    am->test(allocator); // this is the full-fledged test.

    // destroy memory manager
    delete allocator;
  }
}
