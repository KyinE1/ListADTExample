#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <stdexcept>
#include <stack>

// Forward declarations.
template <class T> class mylist;
template <class T> std::ostream& operator<<(std::ostream&, const mylist<T>&);

template <class T> 
struct node {
	T value;
	node<T>* previous;
	node<T>* next;
	
	/** Constructor 
	 * 
	 * @param value: Node's value.
	 * @param next: Pointer to next node.
	 * @param previous: Pointer to previous node.
	 * */
	node(const T& value = T(), node<T>* next = nullptr, node <T>* previous = nullptr) {
		this->value = value;
		this->next = next;
		this->previous = previous;
	}
};

template <class T> 
class mylist {
	friend std::ostream& operator<< <>(std::ostream&, const mylist<T>&);
	
private:
	node<T>* list_front = nullptr;  
	node<T>* list_back = nullptr; 
	size_t list_size = 0;
	void clone(const mylist<T>&);

public:
	mylist();
	~mylist();
	mylist(const mylist<T>&);
	mylist<T>& operator=(const mylist<T>&);
	
	void clear();
	size_t size() const;
	bool empty() const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	void push_front(const T& value); 
	void push_back(const T& value);
	void pop_front();
	void pop_back();
	bool operator==(const mylist<T>& rhs) const;
	bool operator<(const mylist<T>& rhs) const;
};

/** Constructor. */
template <class T> mylist<T>::mylist() {
	list_front = nullptr;
	list_back = nullptr;
	list_size = 0;
}

/** Destructor. */
template <class T> mylist<T>::~mylist() {
	clear();
}

/** Copy constructor.
 *	
 * @param x: Linked list to copy.
 */
template <class T> mylist<T>::mylist(const mylist<T>& x) {
	list_front = list_back = nullptr;
	list_size = 0;
	
	clone(x);
}

/** Overloaded assignment operator.
 *	
 * @param x: Linked list to copy.	
 * @return: Object.
 */
template <class T> mylist<T>& mylist<T>::operator=(const mylist<T>& x) {
	if (this != &x) {
		clear();
		clone(x);
		list_size = x.list_size;
	}

	return *this;
}

/** Clear the list contents. */
template <class T> void mylist<T>::clear() {
	while (!empty())
		pop_back();
	
	list_size = 0;
}

/** Accessor methods. */
template <class T> size_t mylist<T>::size() const {
	return list_size;
}

/** Check if the list is empty.
 * 
 * @return true if the list_size is equal to 0. 
 */
template <class T> bool mylist<T>::empty() const {
	return (list_size == 0);
}

/** Return the front node of the list.
 *	
 * @return: The head node's value. 
 */
template <class T> T& mylist<T>::front() {
	if (empty())
		throw std::underflow_error("stack underflow in front()");
	
	return list_front->value;
}

/** Return the front node of the list.
 *	
 * @return: The head node's value. 
 */
template <class T> const T& mylist<T>::front() const {
	if (empty())
		throw std::underflow_error("stack underflow in front()");
	
	return list_front->value;
}

/** Return the back node of the list.
 * 	
 * @return: The tail node's value. 
 */
template <class T> T& mylist<T>::back() {
	if (empty())
		throw std::underflow_error("stack underflow in back()");
	
	return list_back->value;
}

/** Return the back node of the list.
 * 	
 * @return: The tail node's value. 
 */
template <class T> const T& mylist<T>::back() const {
	if (empty())
		throw std::underflow_error("stack underflow in back()");
	
	return list_back->value;
}

/** Insert an item at the front of the list.
 *	
 *	@param value: Value to create new node.
 */
template <class T> void mylist<T>::push_front(const T& value) {
	node<T>* new_node = new node<T>(value);

	new_node->next = list_front;
	
	// Check if the new node is the first in the list.
	if (empty())
		list_back = new_node;
	else 
		list_front->previous = new_node;
	
	list_front = new_node;
	list_size++;
}

/** Insert an item at the back of the list.
 *
 * @param value: Value to create new node.
 */
template <class T> void mylist<T>::push_back(const T& value) {
	node<T>* new_node = new node<T>(value);
	
	new_node->previous = list_back;
	
	if (empty())
		list_front = new_node;
	else 
		list_back->next = new_node;
	
	list_back = new_node;
	list_size++;
}

/** Remove the item at the front of the list. */
template <class T> void mylist<T>::pop_front() {
	if (empty())
		throw std::underflow_error("stack underflow in pop_front()");

	node<T>* del_node = list_front; 
	list_front = del_node->next; 
	
	if (list_front == nullptr) 
		list_back = nullptr;
	else
		list_front->previous = nullptr;
	
	delete del_node; 
	list_size--;
}

/** Remove an item at the back of the list. */
template <class T> void mylist<T>::pop_back() {
	if (empty())
		throw std::underflow_error("stack underflow in pop_back()");

	node<T>* del_node = list_back; 
	list_back = del_node->previous;
	
	if (list_back == nullptr) 
		list_front = nullptr; 
	else
		list_back->next = nullptr;
	
	delete del_node; 
	list_size--;
}

/** Equality operator overloaded to allow comparison of two mylist objects, returning 
 * true if the two lists contain the same number of nodes and if each element stored 
 * in the left-hand-side list is equal to the corresponding element of the 
 * right-hand-side list.
 * 
 * @param rhs: Object to access data members.
 * @return: If elements of the same index are not equal, returns false.
*/
template <class T> bool mylist<T>::operator==(const mylist<T>& rhs) const {
	if (list_size != rhs.list_size)
		return false; 

	node<T>* lhs = list_front;
	node<T>* rhs_node = rhs.list_front;
	bool flag = true;
	
	while (flag == true && lhs != nullptr) { 
		if (lhs->value == rhs_node->value)
			flag = true;
		else 
			flag = false;
		
		lhs = lhs->next;
		rhs_node = rhs_node->next;
	}
	
	if (flag == true)
		return true;
		
	return false; 
}

/** Compare objects (performing lexicographical comparison of the two lists).
 * 
 * @param rhs: Object to access data members.
 * @return: True if the value on the left hand side is less than the rhs for each 
 * element of the lists.
 */
template <class T> bool mylist<T>::operator<(const mylist<T>& rhs) const {
	node<T>* lhs = list_front;
	node<T>* rhs_node = rhs.list_front;
	
	while (lhs != nullptr && rhs_node != nullptr) { 
		if (lhs->value != rhs_node->value) {
			if (lhs->value < rhs_node->value)
				return true;
			else
				return false;
		}		
		
		lhs = lhs->next;
		rhs_node = rhs_node->next;
	}
	
	if (list_size < rhs.list_size)
		return true;
		
	return false; 
} 

/** Overloaded stream insertion operator for object to be sent to standard output.
 * 
 * @param os: Standard input.
 * @param obj: Object to access data members.
 * @return: The object used for standard input stream.  
 */
template <class T> std::ostream& operator<<(std::ostream& os, const mylist<T>& obj) {
	node<T>* ptr;
	
	for (ptr = obj.list_front; ptr != nullptr; ptr = ptr->next)
		os << ptr->value << " ";
	
	return os;
}

/** Makes a copy of a linked list.
 * 
 * @param x: Linked list to copy.
 */
template <class T> void mylist<T>::clone(const mylist<T>& x) {
    node<T>* ptr;
   
    for (ptr = x.list_front; ptr != nullptr; ptr = ptr->next)
        push_back(ptr->value);
}

#endif
