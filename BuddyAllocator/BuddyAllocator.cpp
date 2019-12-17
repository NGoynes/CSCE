#include "BuddyAllocator.h"
#include <iostream>
using namespace std;

BuddyAllocator::BuddyAllocator (int _basic_block_size, int _total_memory_length){
	int i = 1;

	//get the mulitiplier to determine the size of the memory (this is verification)
	basic_block_size = _basic_block_size;
	while((_basic_block_size*i) < _total_memory_length) {
		i*=2;
	}
	total_memory_size = _basic_block_size*i;

	//make root of vector and give it the total memory size
	root = new char[int(total_memory_size)];
	BlockHeader* insert = (BlockHeader*) root;
	//initialize root
	insert->active = false;
	insert->block_size = total_memory_size;
	insert->next = nullptr;

	//find the location of where we should put the root in the vector
	freeSize = int(log2(total_memory_size/basic_block_size)) + 1;
	//make sure vector is the right size
	FreeList.resize(freeSize);
	FreeList.at(this->getNext(total_memory_size)).insert(insert);
}

BuddyAllocator::~BuddyAllocator (){
	//simply delete the root of the vector of linked lists and then clear the vector
	delete(root);
	FreeList.clear();
}

char* BuddyAllocator::alloc(int _length) {
	//these will be used for indexing up and down the vector
  int i = 0;
	int j = 1;

	//make sure we have enough memory
	if(_length > total_memory_size - sizeof(BlockHeader)) {
		return nullptr;
	}

	//find block size that will satisfy length requirement
	while ((basic_block_size*j) - sizeof(BlockHeader) < _length) {
		j*=2;
		i++;
	}
	int max = basic_block_size*j;

	//did we not find a linked list to insert into?
	if (FreeList.at(i).getSize() <= 0) {
		BlockHeader* splitter = nullptr;
		//find a linkedlist to insert into
		while (FreeList.at(i).getSize() == 0) {
			i++;
			if (i >= freeSize) {
				return nullptr;
			}
		}
		//get the size of the block we are currently at
		int size = FreeList.at(i).head->block_size;
		//split until we find the right size
		while (max != size) {
			BlockHeader* insert = (BlockHeader*) FreeList.at(getNext(size)).head;
			splitter = this->split(insert);
			insert = splitter;
			size/=2;
		}
		//remove the block from the freelist and return it with the blockheader size added
		FreeList.at(getNext(size)).remove((BlockHeader*) splitter);
		char* newSplit = (char*) splitter;
		return (newSplit + sizeof(BlockHeader));
	}
	else { //yes we did!
		BlockHeader* insert = FreeList.at(i).head;
		insert->active = true;
		insert->next = nullptr;
		FreeList.at(i).remove(insert);
		char* mem = (char*) insert;
		return (char*) (mem + sizeof(BlockHeader));
	}

  return nullptr;
}

int BuddyAllocator::free(char* _a) {
	//find starting memory of blockheader
  BlockHeader* start = (BlockHeader*) (_a - sizeof(BlockHeader));
	BlockHeader* addr = start;

	FreeList.at(getNext(addr->block_size)).insert(addr);
	bool active = true;
	uint nextSize = addr->block_size;

	//merge until you can't anymore!
	while (active) {
		BlockHeader* bud = getbuddy(start);
		if(!arebuddies(start,bud)) {
			active = false;
		}
		else {
			start = merge(start,bud);
			addr = (BlockHeader*) start;
		}
	}
	return 0;
}

void BuddyAllocator::printlist (){
  cout << "Printing the Freelist in the format \"[index] (block size) : # of blocks\"" << endl;
  for (int i=0; i<FreeList.size(); i++){
    cout << "[" << i <<"] (" << ((1<<i) * basic_block_size) << ") : ";  // block size at index should always be 2^i * bbs
    int count = 0;
    BlockHeader* b = FreeList [i].head;
    // go through the list from head to tail and count
    while (b){
      count ++;
      // block size at index should always be 2^i * bbs
      // checking to make sure that the block is not out of place
      if (b->block_size != (1<<i) * basic_block_size){
        cerr << "ERROR:: Block is in a wrong list" << endl;
        exit (-1);
      }
      b = b->next;
      }
    cout << count << endl;
  }
}

BlockHeader* BuddyAllocator::getbuddy (BlockHeader * addr) {
	char* newAddr = (char*)addr;
	return (BlockHeader*)(((newAddr-root) ^ (addr->block_size)) + root);
}

bool BuddyAllocator::arebuddies (BlockHeader* block1, BlockHeader* block2) {
	return (!block2->active && (block1->block_size == block2->block_size));
}

BlockHeader* BuddyAllocator::merge (BlockHeader* block1, BlockHeader* block2) {
	//initialize l and r to nullptr
	BlockHeader* left = nullptr;
	BlockHeader* right = nullptr;

	//determine which blocks are left and right based on pointer size
	if(block1 < block2) {
		left = block1;
		right = block2;
	}
	else if (block1 > block2) {
		right = block1;
		left = block2;
	}

	//set new size, remove both left and right and then insert new block with double size
	uint size = left->block_size;
	uint nextSize = size*2;

	FreeList.at(this->getNext(size)).remove(left);
	FreeList.at(this->getNext(size)).remove(right);
	FreeList.at(this->getNext(nextSize)).insert(left);

	//block to be returned
	BlockHeader* merged = left;
	merged->block_size = nextSize;

	return merged;
}

BlockHeader* BuddyAllocator::split (BlockHeader* block) {
	//make left block and remove it
	BlockHeader* left = block;
	uint firstSize = left->block_size;
	FreeList.at(this->getNext(firstSize)).remove(left);
	uint split = firstSize/2;
	char* add = (char*)block;
	//set right block as buddy of left through pointer arithmetic
	BlockHeader* right = (BlockHeader*)(add + split);

	//set sizes of left and right with next pointing null
	left->block_size = split;
	left->next = nullptr;
	right->block_size = split;
	right->next = nullptr;

	//add left and right to free list
	FreeList.at(this->getNext(split)).insert(left);
	FreeList.at(this->getNext(split)).insert(right);

	return left;
}
