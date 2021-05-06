/*
	mylist.h
	Date Written: 4/8
	Created by Kyin Edwards
*/

#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <stdexcept>
#include <stack>

/*
	Program for list ADT using a doubly-linked list and template structure.
*/

// Forward declarations.
template <class T> class mylist;
template <class T> std::ostream& operator<<(std::ostream&, const mylist<T>&);

template <class T> 
struct node {
	T value;
	node<T>* previous;
	node<T>* next;
	
	// Initialize the data members of the list node.
	node(const T& value = T(), node<T>* next = nullptr, node <T>* previous = nullptr) {
		this->value = value;
		this->next = next;
		this->previous = previous;
	}
};

template <class T> 
class mylist {
	
	friend std::ostream& operator<< <>(std::ostream&, const mylist<T>&); // friend for all specializations in the template.
	
	private:
		// Default constructor unecessary; values are initialized.
		node<T>* list_front = nullptr; // pointer to node<T> pointing to front node in list. 
		node<T>* list_back = nullptr; // pointer to node<T> pointing to back node of list.
		size_t list_size = 0; // For list size, n of elements or values currently stored in the list.
		
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

/*
	Default constructor to set the pointer data members to nullptr and list_size equal to 0 (set member function to default if unused). 
*/
template <class T> mylist<T>::mylist() {
	list_front = nullptr;
	list_back = nullptr;
	list_size = 0;
}

/* Destructor; calls the clear() method. */
template <class T> mylist<T>::~mylist() {
	clear();
}

/* 
	Copy constructor; like a linked queue, set the values to default and clone object x.
	
	@param x the mylist object with the linked list to copy.
*/
template <class T> mylist<T>::mylist(const mylist<T>& x) {
	list_front = list_back = nullptr;
	list_size = 0;
	
	clone(x); // Copy linked list.
}

/* 
	Overloaded assignment operator.
	
	@param x the mylist object with the linked list to copy.
	
	@return the *this pointer of the object after passing.
*/
template <class T> mylist<T>& mylist<T>::operator=(const mylist<T>& x) {
	if (this != &x) {
		clear();
		clone(x);
		list_size = x.list_size; // May need to be deleted.
	}

	return *this;
}

/* Set the list to empty deleting all nodes and setting list_size to 0. */
template <class T> void mylist<T>::clear() {
	while (!empty())
		pop_back();
	
	list_size = 0;
}

/* @return get the list_size data member. */
template <class T> size_t mylist<T>::size() const {
	return list_size;
}

/* @return true if the list_size is equal to 0. */
template <class T> bool mylist<T>::empty() const {
	return (list_size == 0);
}

/* 
	Return the front node of the list. If the list is empty, an error is thrown.
	
	@return get the list_front (pointing to value). 
*/
template <class T> T& mylist<T>::front() {
	if (empty())
		throw std::underflow_error("stack underflow in front()");
	
	return list_front->value;
}

/* 
	Return the front node of the list. If the list is empty, an error is thrown.
	
	@return get the list_front (pointing to value). 
*/
template <class T> const T& mylist<T>::front() const {
	if (empty())
		throw std::underflow_error("stack underflow in front()");
	
	return list_front->value;
}

/* 
	Return the back node of the list. If the list is empty, an error is thrown.
	
	@return get the list_back (pointing to value). 
*/
template <class T> T& mylist<T>::back() {
	if (empty())
		throw std::underflow_error("stack underflow in back()");
	
	return list_back->value;
}

/* 
	Return the back node of the list. If the list is empty, an error is thrown.
	
	@return get the list_back (pointing to value). 
*/
template <class T> const T& mylist<T>::back() const {
	if (empty())
		throw std::underflow_error("stack underflow in back()");
	
	return list_back->value;
}

/* 
	Insert an item at the front of the list.
	
	@param value the variable used for the new_node assignment.
*/
template <class T> void mylist<T>::push_front(const T& value) {
	node<T>* new_node = new node<T>(value);
	
	// Step 1
	new_node->next = list_front;
	
	// Step 2
	if (empty())
		list_back = new_node;
	else 
		list_front->previous = new_node;
	
	// Step 3
	list_front = new_node;
	
	list_size++;
}

/* 
	Insert an item at the back of the list.
	
	@param value the variable used for the new_node assignment.
*/
template <class T> void mylist<T>::push_back(const T& value) {
	node<T>* new_node = new node<T>(value);
	
	// Step 1
	new_node->previous = list_back;
	
	// Step 2
	if (empty())
		list_front = new_node;
	else 
		list_back->next = new_node;
	
	// Step 3
	list_back = new_node;
	
	list_size++;
}

/* Remove an item at the front of the list, if empty an error is thrown. */
template <class T> void mylist<T>::pop_front() {
	if (empty())
		throw std::underflow_error("stack underflow in pop_front()");

	node<T>* del_node = list_front; // (Step 1)
	list_front = del_node->next; // (Step 2)
	
	if (list_front == nullptr) // (Step 4)
		list_back = nullptr;
	else
		list_front->previous = nullptr;
	
	delete del_node; // (Step 4)
	
	list_size--;
}

/* Remove an item at the back of the list, if empty an error is thrown. */
template <class T> void mylist<T>::pop_back() {
	if (empty())
		throw std::underflow_error("stack underflow in pop_back()");

	node<T>* del_node = list_back; // (Step 1)
	list_back = del_node->previous; // (Step 2)
	
	
	if (list_back == nullptr) // (Step 3)
		list_front = nullptr; // List is now empty, so both nullptr
	else
		list_back->next = nullptr;
	
	delete del_node; // (Step 4)
	
	list_size--;
}

/* 
	Equality operator overloaded to allow comparison of two mylist objects, returning true if the two lists contain the same number of nodes and if each element stored in the left-hand-side list is equal to the corresponding element of the right-hand-side list.
	
	@param rhs the mylist object to access private data member list_front.
	
	@return if any elements of the same index in the nodes are not equal, false is returned.
*/
template <class T> bool mylist<T>::operator==(const mylist<T>& rhs) const {
	if (list_size != rhs.list_size)
		return false; 

	node<T>* lhs = list_front;
	node<T>* rhs_node = rhs.list_front;
	bool flag = true;
	
	while (flag == true && lhs != nullptr) { // (i < list_size)
		if (lhs->value == rhs_node->value)
			flag = true;
		
		else 
			flag = false;
		
		lhs = lhs->next;
		rhs_node = rhs_node->next;
	}
	
	if (flag == true)
		return true;
		
	return false; // All elements would be equal. 
}

/*
	Less than operator overloaded to allow comparison of two mylist objects, perfoming a "lexicographical" comparison of the two lists (meaning "dictionary", element-by-element ordering).
	
	@param rhs the rhs mylist object for accessing data members.
	
	@return true if the value on the left hand side is less than the rhs for all elements of the lists.
*/
template <class T> bool mylist<T>::operator<(const mylist<T>& rhs) const {
	node<T>* lhs = list_front;
	node<T>* rhs_node = rhs.list_front;
	
	// Looping through both lists returning true if the lhs at any element is less than the rhs_node.
	while (lhs != nullptr && rhs_node != nullptr) { // (i < list_size)
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
		
	return false; // All elements would be equal. 
} 

/*
	Overloaded stream insertion operator so that entire mylist object can be sent to standard output. Simply sending the entire mylist object to standard inout.

	@param os standard input. 
	
	@param obj object used to access data member list_front.
	
	@return os return the object used for standard input stream.  
*/
template <class T> std::ostream& operator<<(std::ostream& os, const mylist<T>& obj) {
	node<T>* ptr;
	
	for (ptr = obj.list_front; ptr != nullptr; ptr = ptr->next)
		os << ptr->value << " ";
	
	return os;
}

/* 
	Makes a copy of a linked list.
	
	@param x the mylist object with the linked list to copy.
*/

template <class T> void mylist<T>::clone(const mylist<T>& x) {
    node<T>* ptr;
   
    for (ptr = x.list_front; ptr != nullptr; ptr = ptr->next)
        push_back(ptr->value);
}

#endif