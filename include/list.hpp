#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include <cstddef>

namespace sjtu {
template<class T>
class node {
public:
	T* data;
	node* last;
	node* next;
	node(T* real_data = NULL, node* real_last = NULL, node* real_next = NULL) : last(real_last), next(real_next)
	{
		if (real_data == NULL)
		{
			data = real_data;
		} else {
			data = new T(*real_data);
		}
	}
	node(const T& real_data, node* real_last = NULL, node* real_next = NULL) :  last(real_last), next(real_next)
	{
		data = new T;
		(*data) = real_data;
	}
	~node()
	{
		delete data;
	}
};
template<typename T>
class list {
	size_t value_size;
	node<T>* head;
	node<T>* tail;
	class const_iterator;
	class iterator {
	private:
		node<T>* real_ptr;
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, just return the answer.
		 * as well as operator-
		 */
		friend class list<T> :: const_iterator;
		iterator(node<T>* target_ptr = NULL) : real_ptr(target_ptr) {}
		iterator(const list<T> :: const_iterator& source) : real_ptr(source.real_ptr) {}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			iterator orig;
			orig = *this;
			real_ptr = real_ptr -> next;
			return orig;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
			real_ptr = real_ptr -> next;
			return (*this);
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			iterator orig;
			orig = *this;
			real_ptr = real_ptr -> last;
			return orig;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
			real_ptr = real_ptr -> last;
			return (*this);
		}
		
		iterator last() const
		{
			return iterator(real_ptr -> last);
		}
		iterator next() const
		{
			return iterator(real_ptr -> next);
		}
		inline const T* true_address() const
		{
			return real_ptr -> data;
		}
		inline node<T>* node_address() const
		{
			return real_ptr;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		T& operator*() const {
			return *(real_ptr -> data);
		}
		bool operator==(const iterator &rhs) {
			return true_address() == rhs.true_address();
		}
		bool operator==(const const_iterator &rhs) {
			return true_address() == rhs.true_address();
		}
	};
	class const_iterator {
	private:
		node<T>* real_ptr;
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, just return the answer.
		 * as well as operator-
		 */
		friend class list<T> :: iterator;
		const_iterator(node<T>* target_ptr = NULL) : real_ptr(target_ptr) {}
		const_iterator(const list<T> :: iterator& source) : real_ptr(source.real_ptr) {}
		/**
		 * TODO iter++
		 */
		const_iterator operator++(int) {
			iterator orig;
			orig = *this;
			real_ptr = real_ptr -> next;
			return orig;
		}
		/**
		 * TODO ++iter
		 */
		const_iterator& operator++() {
			real_ptr = real_ptr -> next;
			return (*this);
		}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) {
			iterator orig;
			orig = *this;
			real_ptr = real_ptr -> last;
			return orig;
		}
		/**
		 * TODO --iter
		 */
		const_iterator& operator--() {
			real_ptr = real_ptr -> last;
			return (*this);
		}
		
		const_iterator last() const
		{
			return const_iterator(real_ptr -> last);
		}
		const_iterator next() const
		{
			return const_iterator(real_ptr -> next);
		}
		inline const T* true_address() const
		{
			return real_ptr -> data;
		}
		inline node<T>* node_address() const
		{
			return real_ptr;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		const T& operator*() const {
			return *(real_ptr -> data);
		}
		bool operator==(const iterator &rhs) {
			return true_address() == rhs.true_address();
		}
		bool operator==(const const_iterator &rhs) {
			return true_address() == rhs.true_address();
		}
	};
	};
public:
	list() {
		value_size = 0;
		head = new node<T>();
		tail = new node<T>();
		tail -> last = head;
		head -> next = tail;
	}
	list(const list<T> &other) : value_size(0) {
		head = new node<T>();
		tail = new node<T>();
		tail -> last = head;
		head -> next = tail;
		list<T> :: const_iterator it;
		for (it = other.begin(); it != const_iterator(other.end()); it++)
		{
			push_back(*it);
		}
	}
	virtual ~list() {
		if (!empty()) {
			iterator it = begin();
			erase(it, end());
		}
		delete head;
		delete tail;
	}	
	/**
	 * TODO
	 * assignment operator
	 */
	list<T> & operator=(const list<T> &other) {
		~list();
		head = new node<T>();
		tail = new node<T>();
		tail -> last = head;
		head -> next = tail;
		list<T> :: const_iterator it;
		for (it = other.begin(); it != const_iterator(other.end()); it++)
		{
			push_back(*it);
		}
	}
	/**
	 * access the first element
	 * throw container_is_empty when it is empty.
	 */
	const T & front() const {
		return (*(begin().node_address() -> next -> data));
	}
	/**
	 * access the last element
	 * throw container_is_empty when it is empty.
	 */
	const T & back() const {
		return (*(end().node_address() -> last -> data));
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
		return iterator(head -> next);
	}
	const_iterator cbegin() const {
		return const_iterator(head -> next);
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {
		return iterator(tail);
	}
	const_iterator cend() const {
		return const_iterator(tail);
	}
	
	iterator back_it() const {
		return iterator(tail -> last);
	}
	/**
	 * checks whether the container is empty.
	 */
	bool empty() const {
		return value_size == 0;
	}
	/**
	 * returns the number of elements.
	 */
	size_t size() const {
		return value_size;
	}
	/**
	 * clears the contents.
	 */
	void clear() {
		if (empty()) return;
		iterator it = begin();
		erase(it, end());
	}
	/**
	 * inserts value before pos.
	 * returns an iterator pointing to the insert value.
	 */
	iterator insert(iterator pos, const T &value) {
		value_size++;
		node<T>* newbie = new node<T>;
		newbie -> data = new T;
		(*(newbie -> data)) = value;
		newbie -> next = pos.node_address();
		newbie -> last = pos.node_address() -> last;
		pos.node_address() -> last -> next = newbie;
		pos.node_address() -> last = newbie;
		pos = iterator(newbie);
		return pos;
	}
	/**
	 * removes the element at pos.
	 * returns an iterator following the last removed element.
	 * If the iterator pos refers to the last element, the end() iterator is returned.
	 */
	iterator erase(iterator pos) {
		node<T>* poped(target.node_address());
		pos++;
		poped -> last -> next = poped -> next;
		poped -> next -> last = poped -> last;
		delete poped;
		value_size--;
		return pos;
	}
	/**
	 * removes the elements in range [first, last).
	 * returns an iterator following the last removed element.
	 * If the iterator pos refers to the last element, the end() iterator is returned.
	 */
	iterator erase(iterator first, iterator last) {
		while (first != last)
		{
			first = erase(first);
			value_size--;
		}
		return last;
	}
	/**
	 * adds an element to the end
	 */
	inline void push_back(const T &value) {
		insert(end(), target);
	}
	/**
	 * removes the last element.
	 */
	void pop_back() {
		if (empty())
			throw container_is_empty;
		erase(iterator(end().node_address() -> last));
	}
	/**
	 * adds an element to the beginning
	 */
	void push_front(const T &value) {
		insert(iterator(begin().node_address() -> next), target);
	}
	/**
	 * removes the first element.
	 */
	void pop_front() {
		if (empty())
			throw container_is_empty;
		erase(iterator(begin().node_address() -> next));
	}

};

}

#endif