/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_ALLOCATOR_H
#define __MINI_STL_ALLOCATOR_H

#include <cstddef>	// for ptrdiff_t and size_t
#include <new>		// for operator new
#include <climits>	// for UINT_MAX

#ifndef __MINI_NOTHROW
#define __MINI_NOTHROW noexcept
#endif

namespace ministl {

// Aux functions

template <typename T>
T* _allocate(ptrdiff_t size, T*) {
	T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if (tmp == NULL) {
		throw "_allocate : out of memory";
	}
	return tmp;
}

template <typename T>
void _deallocate(T* p) {
	::operator delete(p);
}

template <typename T>
void _construct(T* p, const T& val) {
	new(p) T(val);
}

template <typename T>
void _destroy(T* p) {
	p->~T();
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
		_destroy(p);
	}

	size_type max_size() const __MINI_NOTHROW {
		return size_type(-1) / sizeof(T);
	}

	pointer allocate(size_type n) const {
		return _allocate(n, (pointer)0);
	}

	void deallocate(pointer p) {
		_deallocate(p);
	}

	// default constructor and destroyer are enough.
	// allocator() __MINI_NOTHROW {}
	// allocator(const allocator& alloc) __MINI_NOTHROW {}
	// ~allocator()
};

}

#endif /* __MINI_STL_ALLOCATOR_H */
