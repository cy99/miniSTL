/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_PRIORITY_QUEUE_H
#define __MINI_STL_PRIORITY_QUEUE_H		// Done.

#include "mini_vector.h"		// for container
#include "mini_algo.h"			// for *_heap() functions

namespace ministl {

template <typename T, typename Container = vector<T>, 
			typename Compare = less<typename Container::value_type> >
class priority_queue {

public:
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type size_type;
	typedef typename Container::reference reference;
	typedef typename Container::const_reference const_reference;

public:
	explicit priority_queue(const Compare& _comp = Compare(), 
				const Container& _ctnr = Container()) : c(_ctnr), comp(_comp) {
		ministl::make_heap(c.begin(), c.end(), comp);
	}

	template <typename InputIterator>
	priority_queue(InputIterator first, InputIterator last, 
			const Compare& _comp = Compare(), const Container& _ctnr = Container()) 
			: c(_ctnr), comp(_comp) {
		c.insert(c.end(), first, last);
		ministl::make_heap(c.begin(), c.end(), comp);
	}

public:
	bool empty() const { return c.empty(); }
	size_type size() const { return c.size(); }
	reference top() const { return c.front(); }
	void push(const value_type& val) {
		c.push_back(val); 
		push_heap(c.begin(), c.end(), comp);
	}
	void pop() {
		pop_heap(c.begin(), c.end(), comp);
		c.pop_back();
	}

protected:
	Container c;
	Compare comp;

};

}// namespace ministl

#endif /* __MINI_STL_PRIORITY_QUEUE_H */