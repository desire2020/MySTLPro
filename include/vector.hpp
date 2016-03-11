#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector {
private:
	long long value_capa, value_size;
	T* data;
public:
	/**
	 * TODO
	 * a type for actions of the elements of a vector, and you should write
	 *   a class named const_iterator with same interfaces.
	 */
	/**
	 * you can see RandomAccessIterator at CppReference for help.
	 */
	class const_iterator;
	class iterator {
	private:
		long long index;
		vector<T>* context;
	public:
		friend class vector<T> :: const_iterator;
		iterator(long long p = 0, const vector<T>* given_context = NULL) : index(p)
		{
			context = (vector<T>*)(given_context);
		}
		iterator(const vector<T> :: const_iterator& source) : index(source.index), context(source.context) {}
		
		iterator operator+(const int &n) {
			return (iterator(index + n, context));
		}
		iterator operator-(const int &n) {
			return (iterator(index - n, context));
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) {
			if (context != rhs.context)
				throw invaild_iterator;
			return (index - rhs.index);
		}
		iterator operator+=(const int &n) {
			index += n;
			return (*this);
		}
		iterator operator-=(const int &n) {
			index -= n;
			return (*this);
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			iterator orig(*this);
			index++;
			return orig;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
			index++;
			return (*this);
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			iterator orig(*this);
			index--;
			return orig;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
			index--;
			return (*this);
		}
		/**
		 * TODO *it
		 */
		T& operator*() const {
			return (*context)[index];
		}
		
		inline long long idx() const {
			return index;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) {
			return (&(*(*this))) == (&(*(rhs)));
		}
		bool operator==(const const_iterator &rhs) {
			return (&(*(*this))) == (&(*(rhs)));
		}
	};
	/**
	 * TODO
	 * has same function as iterator, just for a const object.
	 */
	class const_iterator {
	private:
		long long index;
		vector<T>* context;
	public:
		friend class vector<T> :: iterator;
		const_iterator(long long p = 0, const vector<T>* given_context = NULL) : index(p)
		{
			context = (vector<T>*)(given_context);
		}
		const_iterator(const vector<T> :: iterator& source) : index(source.index), context(source.context) {}
		
		const_iterator operator+(const int &n) {
			return (iterator(index + n, context));
		}
		const_iterator operator-(const int &n) {
			return (iterator(index - n, context));
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invaild_iterator.
		int operator-(const const_iterator &rhs) {
			if (context != rhs.context)
				throw invaild_iterator;
			return (index - rhs.index);
		}
		const_iterator operator+=(const int &n) {
			index += n;
			return (*this);
		}
		const_iterator operator-=(const int &n) {
			index -= n;
			return (*this);
		}
		/**
		 * TODO iter++
		 */
		const_iterator operator++(int) {
			const_iterator orig(*this);
			index++;
			return orig;
		}
		/**
		 * TODO ++iter
		 */
		const_iterator& operator++() {
			index++;
			return (*this);
		}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) {
			iterator orig(*this);
			index--;
			return orig;
		}
		/**
		 * TODO --iter
		 */
		const_iterator& operator--() {
			index--;
			return (*this);
		}
		/**
		 * TODO *it
		 */
		const T& operator*() const {
			return (*context)[index];
		}
		inline long long idx() const {
			return index;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) {
			return (&(*(*this))) == (&(*(rhs)));
		}
		bool operator==(const const_iterator &rhs) {
			return (&(*(*this))) == (&(*(rhs)));
		}2
	};
	/**
	 * TODO Constructs
	 * Atleast three: default constructor, copy constructor and a constructor for std::vector
	 */
	vector() {
		value_capa = 1;
		value_size = 0;
		data = new T[value_capa];
	}
	vector(const vector<T> &other) : value_capa(other.value_capa), value_size(other.value_size) {
		delete[] data;
		data = new T[value_capa];
		for (int i = 0; i < value_size; i++)
		{
			data[i] = target.data[i];
		}
	}
	/**
	 * TODO Destructor
	 */
	~vector() {
		delete[] data;
	}
	/**
	 * TODO Assignment operator
	 */
	vector<T>& operator=(const vector<T> &other) : value_capa(other.value_capa), value_size(other.value_size) {
		delete[] data;
		data = new T[value_capa];
		for (int i = 0; i < value_size; i++)
		{
			data[i] = target.data[i];
		}
		return (*this);
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 */
	T & at(const size_t &pos) {
		if (pos >= value_size || pos < 0)
			throw index_out_of_bound;
		return data[pos];
	}
	const T & at(const size_t &pos) const {
		if (pos >= value_size || pos < 0)
			throw index_out_of_bound;
		return data[pos];
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 * !!! Pay attentions
	 *   In STL this operator does not check the boundary but I want you to do.
	 */
	T & operator[](const size_t &pos) {
		if (pos >= value_size || pos < 0)
			throw index_out_of_bound;
		return data[pos];
	}
	const T & operator[](const size_t &pos) const {
		if (pos >= value_size || pos < 0)
			throw index_out_of_bound;
		return data[pos];
	}
	/**
	 * access the first element.
	 * throw container_is_empty if size == 0
	 */
	const T & front() const {
		if (value_size == 0)
			throw container_is_empty;
		return data[0];
	}
	/**
	 * access the last element.
	 * throw container_is_empty if size == 0
	 */
	const T & back() const {
		if (value_size == 0)
			throw container_is_empty;
		return data[value_size - 1];
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
		return iterator(0, this);
	}
	const_iterator cbegin() const {
		return const_iterator(0, this);
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {
		return iterator(value_size, this);
	}
	const_iterator cend() const {
		return const_iterator(value_size, this);
	}
	/**
	 * checks whether the container is empty
	 */
	inline bool empty() const {
		return value_size == 0;
	}
	inline bool full() const {
		return value_capa == value_size;
	}
	/**
	 * returns the number of elements
	 */
	inline size_t size() const {
		return value_size;
	}
	/**
	 * returns the number of elements that can be held in currently allocated storage.
	 */
	inline size_t capacity() const {
		return value_capa;
	}
	/**
	 * clears the contents
	 */
	void clear() {
		delete[] data;
		vector();
	}
	/**
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value.
	 */
	iterator insert(iterator pos, const T &value) {
		iterator it;
		T tmpa(pos), tmpb(pos);
		for (it = target; it != end(); it++)
		{
			tmpa = *it;
			*it = tmpb;
			tmpb = tmpa;
		}
		push_back(tmpb);
		return target;
	}
	/**
	 * inserts value at index ind.
	 * after inserting, this->at(ind) == value is true
	 * returns an iterator pointing to the inserted value.
	 * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
	 */
	inline iterator insert(const size_t &ind, const T &value) {
		return insert(iterator(ind, this), value);
	}
	/**
	 * removes the element at pos.
	 * return an iterator pointing to the following element.
	 * If the iterator pos refers the last element, the end() iterator is returned.
	 */
	iterator erase(iterator pos) {
		iterator isp;
		for (iterator it = pos; it != end(); it++)
		{
			isp = it;
			isp++;
			if (isp == end()) break;
			(*it) = *isp;
		}
		value_size--;
		return pos;
	}
	/**
	 * removes the element with index ind.
	 * return an iterator pointing to the following element.
	 * throw index_out_of_bound if ind >= size
	 */
	iterator erase(const size_t &ind) {
		return erase(iterator(ind, this));
	}
	/**
	 * adds an element to the end.
	 */
	void space_doubles()
	{
		value_capa <<= 1;
		T* new_place = new T[value_capa];
		for (int i = 0; i < value_size - 1; i++)
		{
			new_place[i] = data[i];
		};
		delete[] data;
		data = new_place;
	}
	void push_back(const T &value) {
		value_size++;
		if (value_size > value_capa)
			space_doubles();
		data[value_size - 1] = value;
	}
	/**
	 * remove the last element from the end.
	 */
	void pop_back() {
		value_size--;
	}
	void reserve(long long new_capacity)
	{
		if (new_capacity < value_capa)
			throw std :: out_of_range("Vector space underestimated!");
		value_capa = new_capacity;
		T* new_place = new T[value_capa];
		for (int i = 0; i < value_size; i++)
		{
			new_place[i] = data[i];
		};
		delete[] data;
		data = new_place;
	}
};


}

#endif
