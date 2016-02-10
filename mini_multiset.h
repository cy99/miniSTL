/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_MULTISET_H
#define __MINI_STL_MULTISET_H		// Done.

#include "mini_functional.h"	// for functor less<T>
#include "mini_allocator.h"		// for allocator<T>
#include "mini_tree.h"			// for binary search tree
#include "mini_iterator.h"		// for reverse_iterator_base<T> and iterator_traits<T>
#include "mini_pair.h"			// for pair<>


namespace ministl {

template <typename T, typename Compare = less<T>, typename Alloc = allocator<T> >
class multiset {
public:
	typedef multiset<T, Compare, Alloc> self;
	typedef binary_search_tree<T, Compare, Alloc>    rep_type;

	typedef T    key_type;
	typedef T    value_type;
	typedef Compare    key_compare;
	typedef Compare    value_compare;
	typedef Alloc    allocator_type;

	typedef typename allocator_type::const_reference    reference;
	typedef typename allocator_type::const_reference    const_reference;
	typedef typename allocator_type::const_pointer    pointer;
	typedef typename allocator_type::const_pointer    const_pointer;

	typedef typename rep_type::const_iterator    iterator;
	typedef typename rep_type::const_iterator    const_iterator;

	typedef reverse_iterator_base<iterator>    reverse_iterator;
	typedef reverse_iterator_base<const_iterator>    const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type    difference_type;
	typedef size_t    size_type;


public:
// Main function
	multiset() : t(Compare()) {}

	explicit multiset(const Compare& _comp) : t(_comp) {}

	template <typename InputIterator>
	multiset(InputIterator first, InputIterator last, 
				const Compare& _comp = Compare()) : t(_comp) {
		t.insert_equal(first, last);
	}

	multiset(const self& x) : t(x.t) {}

	~multiset() {}

	self& operator=(const self& x) {
		t = x.t;
		return *this;
	}

public:
// Member functions
	key_compare key_comp() const { return t.key_comp(); }
	value_compare value_comp() const { return t.key_comp(); }
	inline iterator begin() const { return t.begin(); }
	inline iterator end() const { return t.end(); }
	reverse_iterator rbegin() const { return t.rbegin(); }
	reverse_iterator rend() const { return t.rend(); }
	inline bool empty() const { return t.empty(); }
	inline size_type size() const { return t.size(); }
	inline size_type max_size() const { return t.max_size(); }
	void swap(self& x) { t.swap(x.t); }

	// Insert and Erase
	iterator insert(const value_type& val) {
		return t.insert_equal(val);
	}

	iterator insert(iterator position, const value_type& val) {
		typedef typename rep_type::iterator rep_iterator;
		return t.insert_equal((rep_iterator&)position, val);
	}

	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last) {
		t.insert_equal(first, last);
	}

	iterator erase(iterator position) {
		typedef typename rep_type::iterator rep_iterator;
		return t.erase((rep_iterator&)position);
	}

	size_type erase (const key_type& x) {
		return t.erase(x);
	}

	iterator erase(iterator first, iterator last) {
		typedef typename rep_type::iterator rep_iterator;
		return t.erase((rep_iterator&)first, (rep_iterator&)last);
	}

	void clear() { t.clear(); }

public:
// multiSet functions
	iterator find(const key_type& x) const { return t.find(x); }
	size_type count(const key_type& x) const { return t.count(x); }
	iterator lower_bound(const key_type& x) const { return t.lower_bound(x); }
	iterator upper_bound(const key_type& x) const { return t.upper_bound(x); }
	pair<iterator, iterator> equal_range(const key_type& x) const {
		return t.equal_range(x);
	}
	allocator_type get_allocator() const { return t.get_allocator(); }

// Relational functions overload
	inline bool operator==(const self& rhs) const {
		return this->t == rhs.t;
	}

	inline bool operator<(const self& rhs) const {
		return this->t < rhs.t;
	}


	inline bool operator!=(const self& rhs) const {
		return !(*this, rhs);
	}
	inline bool operator>(const self& rhs) const {
		return rhs < *this;
	}
	inline bool operator<=(const self& rhs) const {
		return !(*this > rhs);
	}
	inline bool operator>=(const self& rhs) const {
		return !(*this < rhs);
	}


protected:
	rep_type t;
};



}// namespace ministl

#endif /* __MINI_STL_MULTISET_H */