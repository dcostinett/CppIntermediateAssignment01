/* 
 * File:   FifoQueue.h
 * Author: dcostinett
 *
 * Created on March 31, 2013, 5:48 AM

Define the FifoQueue class to meet the following requirements


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
#if !defined FIFOQUEUE_H_ALREADY_DEFINED
#define FIFOQUEUE_H_ALREADY_DEFINED

#include "Assignment01.h"
#include "InvalidStateException.h"

class FifoQueue
{
public:

	FifoQueue();
	explicit FifoQueue(int capacity);
	FifoQueue(const FifoQueue& src);

	~FifoQueue();

	void push(char ch);
	void pop();
	char front() const;
	size_t size() const;
	size_t capacity() const;
	bool empty() const;

	size_t shrink();

    void swap(FifoQueue& s);

	friend std::ostream& operator<<(std::ostream& out, const FifoQueue& src);
    FifoQueue& operator=(const FifoQueue& src);

private:
	static const size_t DEFAULT_QUEUE_SIZE = 10;
	char* myQueue;
	size_t myHead;
	size_t myTail;
	size_t myCapacity;
	size_t mySize;

	char back() const;
	size_t expand();
    void copy(const FifoQueue& src);
	bool isFull() const;
};

#endif