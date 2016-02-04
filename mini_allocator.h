/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_ALLOCATOR_H
#define __MINI_STL_ALLOCATOR_H	// Done.

// Default Allocator

#include <cstddef>		// for ptrdiff_t and size_t
#include <new>			// for operator new, operator delete and bad_alloc
#include <climits>		// for UINT_MAX
#include "mini_construct.h"		// for construct() and destroy()

#ifndef __MINI_NOTHROW
#define __MINI_NOTHROW noexcept
#endif

namespace ministl {

// Aux functions

template <typename T>
inline static T* _allocate(ptrdiff_t size, T*) {
	T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if (tmp == NULL) { throw std::bad_alloc(); } // "_allocate : out of memory"
	return tmp;
}

template <typename T>
inline static void _deallocate(T* p) {
	::operator delete(p);	// original implementation
}

template <typename T>
inline static void _construct(T* p, const T& val) {
	construct(p, val);
	// new(p) T(val);	// original implementation
}

template <typename T>
inline static void _destroy(T* p, size_t n) {
    if (n != 0) destroy(p, p + n);
	// while (n--) { (p + i)->~T(); }	// original implementation
}



template <typename T>
class allocator {

// Member types
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	template <typename Type>
	struct rebind { typedef allocator<Type> other; };

// Member functions
public:
	void construct(pointer p, const_reference val) {
		_construct(p, val);
	}

	void destroy(pointer p, size_type n) {
		_destroy(p, n);
	}

	size_type max_size() const __MINI_NOTHROW {
		return size_type(-1) / sizeof(T);
	}

	pointer allocate(size_type n) const {
		return _allocate(n, (pointer)0);
	}

	void deallocate(pointer p, size_type n) {
		_deallocate(p);		// what the use of argument 'n' is ?
	}

	pointer address(reference x) const {
		return (pointer)&x;
	}

	const_pointer address(const_reference x) const {
		return (const_pointer)&x;
	}

	// default constructor and destructor are enough.
	// allocator() __MINI_NOTHROW {}
	// allocator(const allocator& alloc) __MINI_NOTHROW {}
	// ~allocator()
};

}// namespace ministl

#endif /* __MINI_STL_ALLOCATOR_H */
