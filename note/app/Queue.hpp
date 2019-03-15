//queue.h
#ifndef QUEUE_HPP
#define QUEUE_HPP


template <typename T>
class Queue
{
private:
	struct Node { T item; struct Node * next;};
	const static int Q_SIZE = 10;
	Node * front;												// pointer to front of Queue
	Node * rear;												// pointer to rear of Queue
	int count;													// current number of items in Queue
	const int qsize;											// maximum number of items in Queue

	// preemptive definitions to prevent public copying
	Queue(const Queue & q) : qsize(0) {};
	Queue & operator=(const Queue & q) {return *this;};

public:
	Queue(int qs = Q_SIZE);										// create queue with a qs limit
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const T &);									// add item to end
	bool dequeue(T &);											// remove item from front
};

#endif /* QUEUE_H_ */