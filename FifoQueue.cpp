/*
AssignmentA01.cpp
Dan Costinett
danco@uw.edu

Goals
Create a class that implements a FIFO abstract data type. Provide an efficient implementation using a
circular buffer data structure. Use dynamically-allocated memory correctly.

Description
A FIFO queue is a common data structure for storing information. FIFO is an acronym for First In, First
Out. Items are taken out of the queue in the same order that were put in. The first data to be added to
the queue will be the first data to be removed. Elements are added to the end of the queue, and are
removed from the beginning of the queue. A common solution is to create a linked list of nodes.
Because there is the overhead of a pointer with each node, this is not the most efficient solution to store
small data.

Requirements

R1: Create a FIFO queue
Create a FIFO queue to hold characters whose internal storage is implemented using a circular buffer
and a plain C++ array. Do not use <queue>, <deque>, <vector> or another container from the standard
library to implement the array. The queue should be implemented as a C++ class, and should support
methods to add a character to the back of the queue, remove an element from the front of the queue,
get the element at the front of the queue without removal, get the number of elements in the queue,
and test if the queue is empty.

R2: Allow dynamic resizing
So that it can be resized, the array should be dynamically allocated using <new>. If an element is added
to the queue that exceeds the capacity of the queue, expand the queue to accommodate the element.
Include a method in the public interface to resize the queue to be as small as possible.

R3: Automate Testing
Use the CppUnitLite test harness to automate testing of the FIFO queue. Cover all partitions.
*/
#include "FifoQueue.h"

/*
	Default constructor
*/
FifoQueue::FifoQueue() :
	myQueue(new char[DEFAULT_QUEUE_SIZE + 1]), myHead(0), myTail(0), 
		myCapacity(DEFAULT_QUEUE_SIZE + 1), mySize(0)
{
}

/*
	Constructor with capacity initializer
*/
FifoQueue::FifoQueue(int capacity) :
	myQueue(new char[capacity + 1]), myHead(0), myTail(0), mySize(0)
{
	if (capacity < 0 )
	{
		throw InvalidStateException("Cannot initialize queue with negative capacity.");
	}
	myCapacity = capacity + 1;
}

/*
	Copy constructor, use initialization list to set 
	values of all member data in order of declaration
*/
FifoQueue::FifoQueue(const FifoQueue& src) :
	myQueue(new char[src.capacity() + 1]), 
		myHead(src.myHead), 
		myTail(src.myTail), 
		myCapacity(src.myCapacity), 
		mySize(src.mySize)
{
	for (size_t i = 0; i < size(); i++)
	{
		myQueue[(myHead + i) % capacity()] = src.myQueue[(myHead + i) % capacity()];
	}
}

/*
	Destructor -- deletes the memory allocated from the heap
*/
FifoQueue::~FifoQueue()
{
	delete [] myQueue;
}

/*
	Enqueue a char at the back of the queue
*/
void FifoQueue::push(char ch)
{
	if (isFull())
	{
		expand();
	}

	myQueue[myTail] = ch;
	++mySize;

	myTail = (myTail + 1) % myCapacity;
}

/*
	Remove an item from the front of the queue -- item not returned.
	You don't return it because that memory position is no longer valid 
	and can be overwritten at any time.
*/
void FifoQueue::pop()
{
	if (empty())
	{
		throw InvalidStateException("Attempt to dequeue an empty queue.");
	}

	char& head = myQueue[myHead];
	--mySize;
	
	myHead = (myHead + 1) % myCapacity;
}

/*
	Return a reference to the front of the queue
*/
char FifoQueue::front() const 
{
	if (empty())
	{
		throw InvalidStateException("Attempt to dequeue an empty queue.");
	}
	return myQueue[myHead];
}

/*
	Return a reference to the last element in the queue -- 
	NOT the position at which the next element will be added.
*/
char FifoQueue::back() const
{
	if (empty())
	{
		throw InvalidStateException("Attempt to dequeue an empty queue.");
	}
	return myQueue[myTail - 1];
}


/*
	Return the size of the queue
*/
size_t FifoQueue::size() const
{
	return mySize;
}

/*
	Return the count of the chars allocated for storage -- not the number
	of items in the queue, but the amount of storage allocated to hold items.
*/
size_t FifoQueue::capacity() const
{
	return myCapacity - 1;
}

/*
	Test if the queue is empty
*/
bool FifoQueue::empty() const
{
	return size() == 0;
}


/*
	Expand the queue to hold 50% additional characters
*/
size_t FifoQueue::expand()
{
	size_t expandedCapacity = myCapacity + max(myCapacity / 2, 1);
	char* tempQueue = new char[expandedCapacity];
	//Need to copy from head to tail, mySize number of
	// items from old array to new array, handling the wrap.
	for (size_t i = 0; i < size(); i++)
	{
		tempQueue[i] = myQueue[(myHead + i) % myCapacity];
	}
	// expand needs to fix up the head and tail to point to the new 
	// head and tail of the new queue
	myHead = 0;
	myTail = mySize;
	delete [] myQueue;
	myQueue = tempQueue;
	myCapacity = expandedCapacity;
	
	return capacity();
}

/*
	Shrink the queue to fit the available characters in the queue
*/
size_t FifoQueue::shrink()
{
	if (capacity() == size())
	{
		return size();
	}

	FifoQueue temp(size());
	size_t oldSize = size();
	for (size_t i = 0; i < oldSize; i++)
	{
		temp.myQueue[i] = front();
		pop();
	}
	temp.myTail = oldSize;
	temp.mySize = oldSize;
	swap(temp);

	return capacity();
}

/*
	The swap function to swap the properties of a FifoQueue with this one
*/
void FifoQueue::swap(FifoQueue& s)
{
    std::swap(myQueue, s.myQueue);
	std::swap(myHead, s.myHead);
	std::swap(myTail, s.myTail);
	std::swap(myCapacity, s.myCapacity);
	std::swap(mySize, s.mySize);
}

/*
	Copy the properties from a src queue
*/
void copy(const FifoQueue& src)
{

}



/*
	Determines if the queue is full and needs to get expanded.
*/
bool FifoQueue::isFull() const
{
	return (myTail + 1) % myCapacity == myHead;
}

/*
	Print out the queue
*/
std::ostream& operator<<(std::ostream& out, const FifoQueue& src)
{
	for (size_t i = src.myHead; i < src.mySize - 1; i++)
	{
		out << src.myQueue[(src.myHead + i) % src.myCapacity] << ", ";
	}
	out << src.myQueue[src.myTail - 1] << std::endl;
	return out;
}

/*
	Assignment operator
*/
FifoQueue& FifoQueue::operator=(const FifoQueue& src)
{
    FifoQueue temp(src);
    swap(temp);
    return *this;
}

