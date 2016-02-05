/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_QUEUE_H
#define __MINI_STL_QUEUE_H		// Done.

#include <cstddef>	// for size_t
#include "mini_list.h"		// for default container list<T>
#include "mini_vector.h"	// for vector container vector<T>

namespace ministl {

template <typename T, typename Container = list<T> >
class queue {
public:
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;
	typedef queue<T, Container> self;

public:
	explicit queue(const container_type& ctnr = container_type()) : c(ctnr) {}

public:
	inline bool empty() const { return c.empty(); }
	inline size_type size() const { return c.size(); }
	inline value_type& back() const { return c.back(); }
	inline value_type& front() const { return c.front(); }
	inline void push(const value_type& val) { c.push_back(val); }
	inline void pop() { c.pop_front(); }


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

#endif /* __MINI_STL_QUEUE_H */