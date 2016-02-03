/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_VECTOR_H
#define __MINI_STL_VECTOR_H

#include <cstddef>			// for ptrdiff_t and size_t
#include <stdexcept>		// for std::out_of_range
#include "mini_allocator.h"	// for default allocator
#include "mini_memory.h"	// for construct() and destroy()
#include "mini_algo.h"		// for fill() and fill_n()

#ifndef __MINI_NOTHROW
#define __MINI_NOTHROW noexcept
#endif

#define EXPAND_MULTIPLE 2	// Perhaps 1.5 is more effective.


namespace ministl {

template <typename T, typename Alloc = allocator<T> >
class vector {

// Member types
public:

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef Alloc allocator_type;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	// typedef reverse_iterator<iterator> reverse_iterator;
	// typedef reverse_iterator<const_iterator> const_reverse_iterator;



// Member functions
public:

// Base :
	vector(const allocator_type& _allocator = allocator_type()) :
	    	start(NULL), finish(NULL), end_of_storage(NULL), alloc(_allocator) {}

	vector(size_type n, const value_type& val = value_type(),
						const allocator_type& _allocator = allocator_type()) {
		alloc = _allocator;
		start = alloc.allocate(n);
		finish = uninitialized_fill_n(start, n, val);
		end_of_storage = finish;
	}



	template <typename InputIterator>
	vector(InputIterator first, InputIterator last,
						const allocator_type& _allocator = allocator_type()) :
						start(NULL), finish(NULL), end_of_storage(NULL) {

		alloc = _allocator;
		while (first != last) { push_back(*(first++)); }
		#if 0
		start = alloc.allocate(last - first);
		finish = uninitialized_copy(first, last, start);
		end_of_storage = finish;
		#endif // only random iterator
	}

	vector(const vector& x) {
		alloc = x.get_allocator();
		start = alloc.allocate(x.size());
		finish = uninitialized_copy(x.begin(), x.end(), start);
		end_of_storage = finish;
	}

	~vector() {		
		alloc.destroy(start, size());
		alloc.deallocate(start, capacity());
	}

	vector& operator=(const vector& x) {
		if (&x == this) return *this;

		size_type x_size = x.size();
		if (x_size > capacity()) {			
			iterator tmp = alloc.allocate(x_size);
			alloc.destroy(start, size());
			alloc.deallocate(start, capacity());
			start = tmp;
			finish = uninitialized_copy(x.begin(), x.end(), start);
			end_of_storage = finish;
		} else {
			destroy(start, finish);
			finish = uninitialized_copy(x.begin(), x.end(), start);
		}
		return *this;
	}


// Iterators :
	inline iterator begin() const { return start; }
	inline iterator end() const { return finish; }
	//reverse_iterator rbegin() { return reverse_iterator(end()); }
	//reverse_iterator rend() { return reverse_iterator(begin()); }
	inline const_iterator cbegin() const { return start; }
	inline const_iterator cend() const { return finish; }
	//reverse_iterator crbegin() const { return reverse_iterator(cend()); }
	//reverse_iterator crend() const { return reverse_iterator(cbegin()); }


// Capacity :
	inline size_type size() const { return size_type(end() - begin()); }
	size_type max_size() const { return size_type(-1) - sizeof(value_type); }

	void reserve (size_type n) {
		if (n > capacity()) {
			iterator tmp_start = alloc.allocate(n);
			iterator tmp_finish = uninitialized_copy(start, finish, tmp_start);

			alloc.destroy(start, size());
			alloc.deallocate(start, capacity());

			start = tmp_start;
			finish = tmp_finish;
			end_of_storage = start + n;
		}
	}

	void resize (size_type n, value_type val = value_type()) {
		if (n < size()) {
			destroy(start + n, finish);
			finish = start + n;
		} else if (n > capacity()) {
			reserve(n);
			uninitialized_fill(finish, end_of_storage, val);
			finish = end_of_storage;
		}
	}

	inline size_type capacity() const { return size_type(end_of_storage - start); }
	inline bool empty() const { return finish == start; }


// Element access :
	inline reference operator[](size_type n) { return *(begin() + n); }
	inline const_reference operator[](size_type n) const { return *(begin() + n); }
	reference at(size_type n) {
		if (n >= size()) {
			throw std::out_of_range("Out_of_range Error in vector::at().");
		}
		return this[n];
	}
	const_reference at(size_type n) const {
		if (n >= size()) {
			throw std::out_of_range("Out_of_range Error in vector::at().");
		}
		return this[n];
	}
	inline reference front() const { return *begin(); }
	inline reference back() const { return *(end() - 1); }


// Modifiers :
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last) {
		iterator cur = start;
		while (first != last && cur != finish) { *(cur++) = *(first++); }
		while (first != last) { push_back(*(first++)); }
		if (cur != finish) {
			destroy(cur, finish);
			finish = cur;
		}
	}

	void assign(size_type n, const value_type& val) {
		if (n > capacity()) {
			destroy(start, finish);
			
			alloc.deallocate(start, capacity);
			start = alloc.allocate(n);

			finish = uninitialized_fill_n(start, n, val);
			end_of_storage = finish;
		} else if (n > size()) {
			fill_n(start, size(), val);
			finish = uninitialized_fill_n(finish, n - size(), val);
		}
	}

	void insert (iterator position, size_type n, const value_type& val) {
		size_type available_size = end_of_storage - finish;
		if (n > available_size) {			

			size_type expand_size = size() + n;
			iterator tmp_start = alloc.allocate(expand_size);

			iterator tmp_position = uninitialized_copy(start, position, tmp_start);
			iterator tmp_finish = uninitialized_fill_n(tmp_position, n, val);
			tmp_finish = uninitialized_copy(position, finish, tmp_finish);

			alloc.destroy(start, size());
			alloc.deallocate(start, capacity());

			finish = tmp_finish;
			start = tmp_start;
			end_of_storage = start + expand_size;
		} else {
			finish = uninitialized_copy(finish - n, finish, finish);
			copy_backward(position, finish - n - 1, finish - n);
			fill_n(position, n, val);
		}
	}

	iterator insert(iterator position, const value_type& val) {
		if (finish == end_of_storage) {			

			size_type expand_size = EXPAND_MULTIPLE * capacity();
			if (expand_size == 0) { expand_size = 1; }
			iterator tmp_start = alloc.allocate(expand_size);

			iterator tmp_position = uninitialized_copy(start, position, tmp_start);
			alloc.construct(tmp_position, val);
			iterator tmp_finish = uninitialized_copy(position, finish, tmp_position + 1);

			alloc.destroy(start, size());
			alloc.deallocate(start, capacity());

			finish = tmp_finish;
			start = tmp_start;
			end_of_storage = start + expand_size;

			return tmp_position;
		} else {
			construct(finish, *(finish - 1));
			++finish;
			copy_backward(position, finish - 2, finish - 1);
			*position = val;
			return position;
		}
	}

	template <typename InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last) {
		size_type available_size = end_of_storage - finish;
		while (first != last) {
			position = insert(position, *(first++));
			++position;
		}
	}

	void push_back(const value_type& val) {
		if (finish == end_of_storage) {
			insert(finish, val);
		} else {
			construct(finish, val);
			++finish;
		}
	}

	void pop_back() { destroy(--finish); }

	iterator erase(iterator position) {
		copy(position + 1, finish, position);
		--finish;
		destroy(finish);
		return position;
	}

	iterator erase(iterator first, iterator last) {
		size_type n = last - first;
		copy(last, finish, first);
		finish -= n;
		destroy(finish, finish + n);
		return first;
	}


// Allocator :
	inline allocator_type get_allocator() const { return alloc; }



protected:
	allocator_type alloc;
	pointer start;
	pointer finish;
	pointer end_of_storage;



};

}// namespace ministl

#endif /* __MINI_STL_VECTOR_H */
