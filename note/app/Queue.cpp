//queue.cpp
#include "Queue.hpp"

template <typename T>
Queue<T>::Queue(int qs)
{
	qsize = qs;
	count = 0;
	front = rear = nullptr;
}

template <typename T>
Queue<T>::~Queue()
{
	Node * temp;						// create temporary address store
	while(front != (void *) 0)			// while the queue is not empty
	{
		temp = front;
		front = front->next;			// advance the front object to the next
		delete temp;					// delete the temporary data
	}
}

template <typename T>
bool Queue<T>::isempty() const
{
	return count == 0;
}

template <typename T>
bool Queue<T>::isfull() const
{
	return count == qsize;
}

template <typename T>
int Queue<T>::queuecount() const
{
	return count;
}

template <typename T>
bool Queue<T>::enqueue(const T &data)  	// add item to end
{
	if(isfull())						// if queue is full halt queuing
		return false;

	Node * add = new Node;				// create node
	add->item = data;					// set node pointers
	add->next = (void *) 0;				// or nullptr;
	count++;
	if (front == (void *) 0)			// if queue is empty,
		front = add;					// place item at front
	else
		rear->next = add;				// else place at rear
	rear = add;							// have rear point to new node

	return true;
}

template <typename T>
bool Queue<T>::dequeue(T &data)			// remove item from front
{
	if(front == (void *) 0)				// front node is empty, queue is empty
		return false;

	data = front->item;					// set data to first item in queue
	count--;							// decrement item count
	Node * temp = front; 				// save location of first item
	front = front->next; 				// reset front to next item
	delete temp;						// delete former first item

	if (count == 0)						// if the queue is now empty set rear to point to nothing
		rear = (void *)0;

	return true;

}