/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_STACK_H
#define __MINI_STL_STACK_H		// Done.

#include <cstddef>	// for size_t
#include "mini_list.h"		// for default container list<T>
#include "mini_vector.h"	// for vector container vector<T>

namespace ministl {

template <typename T, typename Container = list<T> >
class stack {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef size_t size_type;
	
	typedef Container container_type;
	typedef stack<T, Container> self;

public:
	explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {}

public:
	inline bool empty() const { return c.empty(); }
	inline size_type size() const { return c.size(); }
	inline reference top() { return c.back(); }
	inline const_reference top() const { return c.back(); }
	inline void push(const value_type& val) { c.push_back(val); }
	inline void pop() { c.pop_back(); }


protected:
	container_type c;

public:
	inline bool operator==(const self& rhs) const { return c == rhs.c; }
	inline bool operator<(const self& rhs) const { return c < rhs.c; }

	inline bool operator!=(const self& rhs) const { return !(*this == rhs); }
	inline bool operator>(const self& rhs) const { return rhs < *this; }
	inline bool operator<=(const self& rhs) const { return !(*this > rhs); }
	inline bool operator>=(const self& rhs) const { return !(*this < rhs); }

};// stack class


}// namespace ministl

#endif /* __MINI_STL_STACK_H */