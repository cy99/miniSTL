/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_VECTOR_H
#define __MINI_STL_VECTOR_H

#include <cstddef>			// for ptrdiff_t and size_t
#include <stdexcept>		// for std::out_of_range
#include "mini_allocator.h"
#include "mini_memory.h"

#ifndef __MINI_NOTHROW
#define __MINI_NOTHROW noexcept
#endif

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
	vector(const allocator_type& alloc = allocator_type()) :
	    start(NULL), finish(NULL), end_of_storage(NULL) {}
	vector(size_type n, const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type()) {
		start = alloc.allocate(n);
		finish = start + n;
		uninitialized_fill_n(start, n, val);
		end_of_storage = finish;
	}
	template <typename InputIterator>
	vector(InputIterator first, InputIterator last,
		const allocator_type& alloc = allocator_type()) {
		size_type n = last - first;
		start = alloc.allocate(n);
		finish = start + n;
		end_of_storage = finish;
		for (size_type i = 0; i < n; i++) {
			*(start + i) = *(first + i);
		}
	}
	vector(const vector& x) {
		allocator_type alloc = x.get_allocator();
		start = alloc.allocate(x.size());
		finish = start + x.size();
		end_of_storage = finish;
		uninitialized_copy(x.begin(), x.end(), start);
	}
	~vector() { get_allocator().destroy(start, size()); }
	vector& operator=(const vector& x) {
		// TODO();
	}


// Iterators :
	iterator begin() const { return start; }
	iterator end() const { return finish; }
	//reverse_iterator rbegin() { return reverse_iterator(end()); }
	//reverse_iterator rend() { return reverse_iterator(begin()); }
	const_iterator cbegin() const { return start; }
	const_iterator cend() const { return finish; }
	//reverse_iterator crbegin() const { return reverse_iterator(cend()); }
	//reverse_iterator crend() const { return reverse_iterator(cbegin()); }


// Capacity :
	size_type size() const { return size_type(end() - begin()); }
	size_type max_size() const { return size_type(-1) - sizeof(value_type); }
	// resize	// TODO();
	size_type capacity() const { return size_type(end_of_storage - start); }
	bool empty() const { return finish == start; }
	// reserve // TODO();

// Element access :
	reference operator[](size_type n) { return *(begin() + n); }
	const_reference operator[](size_type n) const { return *(begin() + n); }
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
	reference front() const { return *begin(); }
	reference back() const { return *(end() - 1); }

// Modifiers :
#if 0
	assign
	push_back
	pop_back
	insert
	erase
	swap
	clear
#endif
// Allocator :
	allocator_type get_allocator() const { return allocator_type(); }



protected:
	pointer start;
	pointer finish;
	pointer end_of_storage;

};

}

#endif /* __MINI_STL_VECTOR_H */
