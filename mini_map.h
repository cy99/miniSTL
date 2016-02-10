/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_MAP_H
#define __MINI_STL_MAP_H		// Done.

#include "mini_tree.h"			// for binary search tree
#include "mini_functional.h"	// for binary_function functor
#include "mini_pair.h"			// for pair<key, value>
#include "mini_allocator.h"		// for allocator
#include "mini_iterator.h"		// for reverse_iterator_base<T>

namespace ministl {


template <typename Key, typename Value, typename Compare = less<Key>, 
	typename Alloc = allocator<ministl::pair<Key, Value> > >
class map {
public:
	

	typedef Key    key_type;
	typedef Value    data_type;
	typedef ministl::pair<const Key, Value>    value_type;
	typedef Compare    key_compare;
	typedef Alloc    allocator_type;


	//------------ Functor --------------------
	class value_compare 
	: public binary_function<value_type, value_type, bool> {

		friend class map<Key, Value, Compare, Alloc>;

	protected:
		Compare comp;
		value_compare(Compare _comp) : comp(_comp) {}
	public:
		bool operator()(const value_type& a, const value_type& b) const {
			return comp(a.first, b.first);
		}
	};

private:
	typedef binary_search_tree<value_type, value_compare, allocator_type> rep_type;
	typedef map<key_type, data_type, key_compare, allocator_type> self;

public:
	typedef typename allocator_type::reference    reference;
	typedef typename allocator_type::const_reference    const_reference;
	typedef typename allocator_type::pointer    pointer;
	typedef typename allocator_type::const_pointer    const_pointer;

	typedef typename rep_type::iterator    iterator;
	typedef typename rep_type::const_iterator    const_iterator;


	typedef typename rep_type::reverse_iterator    reverse_iterator;
	typedef typename rep_type::const_reverse_iterator    const_reverse_iterator;
	// typedef reverse_iterator_base<iterator>    reverse_iterator;
	// typedef reverse_iterator_base<const_iterator>    const_reverse_iterator;

	typedef typename iterator_traits<iterator>::difference_type    difference_type;
	typedef size_t    size_type;


public:
// Main function
	map() : t(Compare()) {}

	explicit map(const Compare& _comp) : t(_comp) {}

	template <typename InputIterator>
	map(InputIterator first, InputIterator last, 
				const Compare& _comp = Compare()) : t(_comp) {
		t.insert_unique(first, last);
	}

	map(const self& x) : t(x.t) {}

	self& operator=(const self& x) {
		t = x.t;
		return *this;
	}


// Aux function
private:
	inline value_type __wrap(const key_type& _key) const {
		return value_type(_key, data_type());
	}


public:
// Member functions
	key_compare key_comp() const { return t.key_comp(); }
	value_compare value_comp() const { return value_compare(t.key_comp()); }

	iterator begin() { return t.begin(); }
	iterator end() { return t.end(); }
	const_iterator begin() const { return t.begin(); }
	const_iterator end() const { return t.end(); }

	reverse_iterator rbegin() { return t.rbegin(); }
	reverse_iterator rend() { return t.rend(); }
	const_reverse_iterator rbegin() const { return t.rbegin(); }
	const_reverse_iterator rend() const { return t.rend(); }

	inline bool empty() const { return t.empty(); }
	inline size_type size() const { return t.size(); }
	inline size_type max_size() const { return t.max_size(); }
	void swap(self& x) { t.swap(x.t); }

	data_type& operator[](const key_type& _key) {
		return (*(insert(__wrap(_key)).first)).second;
	}

	// Insert and Erase
	ministl::pair<iterator,bool> insert(const value_type& val) {
		return t.insert_unique(val);
	}

	iterator insert(iterator position, const value_type& val) {
		return t.insert_unique(position, val);
	}

	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last) {
		t.insert_unique(first, last);
	}

	iterator erase(iterator position) {
		return t.erase(position);
	}

	size_type erase (const key_type& _key) {
		return t.erase(__wrap(_key));
	}

	iterator erase(iterator first, iterator last) {
		return t.erase(first, last);
	}

	void clear() { t.clear(); }


public:
// Map functions
	iterator find(const key_type& x) { return t.find(__wrap(x)); }
	const_iterator find(const key_type& x) const { return t.find(__wrap(x)); }
	size_type count(const key_type& x) const { return t.count(__wrap(x)); }
	iterator lower_bound(const key_type& x) { return t.lower_bound(__wrap(x)); }
	const_iterator lower_bound(const key_type& x) const { return t.lower_bound(__wrap(x)); }
	iterator upper_bound(const key_type& x) { return t.upper_bound(__wrap(x)); }
	const_iterator upper_bound(const key_type& x) const { return t.upper_bound(__wrap(x)); }
	ministl::pair<iterator, iterator> equal_range(const key_type& x) {
		return t.equal_range(__wrap(x));
	}
	ministl::pair<const_iterator, const_iterator>
					equal_range(const key_type& x) const {
		return t.equal_range(__wrap(x));
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

#endif /* __MINI_STL_MAP_H */