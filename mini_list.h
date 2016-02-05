/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_LIST_H
#define __MINI_STL_LIST_H		// Working...

#include <cstddef>
#include "mini_allocator.h"
#include "mini_memory.h"
#include "mini_iterator.h"



namespace ministl {


template <typename T>
struct __list_node {
	__list_node<T>* prev;
	__list_node<T>* next;
	T data;

	__list_node(const T& val = T()) : prev(NULL), next(NULL), data(val) {}
};


template <typename T, typename Alloc = allocator<T> >
class list {

public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef __list_node<T> node_type;
	typedef typename Alloc::template rebind<node_type>::other allocator_type;


// List Iterator Class
protected:
	class __list_iterator {
	public:
		typedef bidirectional_iterator_tag iterator_category;

		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef __list_iterator self;

	// Construct
	public:
		__list_iterator(node_type* pt = NULL) : node(pt) {}

	// Member function
	public:

		inline reference operator*() const {
			return node->data;
		}

		inline pointer operator->() const {
			return &(operator*());
		}

		inline bool operator==(const self& x) const {
			return x.node == node;
		}

		inline bool operator!=(const self& x) const {
			return !(*this == x);
		}

		inline self& operator++() {
			node = node->next;
			return *this;
		}

		inline self& operator--() {
			node = node->prev;
			return *this;
		}

		inline self operator++(int) {
			self tmp = *this;
			node = node->next;
			return tmp;
		}

		inline self operator--(int) {
			self tmp = *this;
			node = node->prev;
			return tmp;
		}

	public:
		node_type* node;
	};




public:

	typedef __list_iterator iterator;
	typedef const __list_iterator const_iterator;

	typedef reverse_iterator_base<iterator> reverse_iterator;
	typedef reverse_iterator_base<const_iterator> const_reverse_iterator;



// Aux function
protected:
	inline node_type* __create_node(const_reference val = value_type()) {
		node_type* tmp = alloc.allocate(1);
		ministl::construct(tmp, val);
		return tmp;
	}

	// create a node which is the head node as well as the tail node meanwhile.
	inline iterator __initialized_head() {
		node_type* tmp = __create_node();
		tmp->prev = tmp->next = tmp;
		return iterator(tmp);
	}

	inline void __destroy_node(node_type* x) const {
		ministl::destroy(x);
	}

	template <typename U> static void __swap(U& a, U& b) {
		U tmp(a); a = b; b = tmp;
	}

// Member Functions
public:
	allocator_type get_allocator() const { return alloc; }

	list(const allocator_type& _alloc = allocator_type())
					: head(__initialized_head()), alloc(_alloc) {}

	list(size_type n, const value_type& val = value_type(),
					const allocator_type& _alloc = allocator_type())
					: head(__initialized_head()), alloc(_alloc) {
		insert(head, n, val);
	}

	template <typename InputIterator>
	list(InputIterator first, InputIterator last,
					const allocator_type& _alloc = allocator_type())
					: head(__initialized_head()), alloc(_alloc) {
		insert(first, last, head);
	}

	list(const list& x) : head(__initialized_head()), alloc(x.alloc) {
		insert(x.begin(), x.end(), head);
	}

	~list() {
		clear();
		__destroy_node(head.node);
	}

	list<T>& operator=(const list<T>& x) {
		alloc = x.alloc;
		assign(x.begin(), x.end());
		return *this;
	}



// Iterators and Capacity
public:
	inline iterator begin() const { return head; }
	inline iterator end() const { iterator tmp = head; return --tmp; }
	inline reverse_iterator rbegin() const { return reverse_iterator(end()); }
	inline reverse_iterator rend() const { return reverse_iterator(begin()); }

	inline bool empty() const { return end() == begin(); }
	size_type size() const {
		iterator tmp_end = end(), tmp_begin = begin();
		size_type tmp_len = 0;
		while (tmp_begin != tmp_end) {
			++tmp_begin;
			++tmp_len;
		}
		return tmp_len;
	}
	size_type max_size() const { return size_type(-1) / sizeof(value_type); }


// Element access and Modifiers
public:
	inline reference front() const { return *begin(); }
	inline reference back() const { iterator tmp = end(); return *(--tmp); }


	void assign(size_type n, const value_type& val) {
		clear();
		insert(head, n, val);
	}

	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last) {
		clear();
		insert(first, last, head);
	}

	void push_front(const value_type& val) { insert(begin(), val); }

	void pop_front() { erase(begin()); }

	void push_back(const value_type& val) { insert(end(), val); }

	void pop_back() { iterator tmp = end(); erase(--tmp); }

	iterator insert(iterator position, const_reference val) {
		node_type* tmp = __create_node(val);

		node_type* current = position.node;
		current->prev->next = tmp;
		tmp->prev = current->prev;
		tmp->next = current;
		current->prev = tmp;
		iterator ret = iterator(tmp);
		if (position == head) { head = ret; }
		return ret;
	}

	void insert(iterator position, size_type n, const_reference val) {
		while (n--) { insert(position, val); }
	}

	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last, iterator position) {
		while (first != last) { insert(position, *(first++)); }
	}

	iterator erase(iterator position) {
		node_type* current = position.node;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		node_type* ret = current->next;
		if (position == head) { head = ret; }
		__destroy_node(current);
		return ret;
	}

	iterator erase(iterator first, iterator last) {
		while (first != last) { first = erase(first); }
		return first;
	}

	void swap(list& x) {
		__swap(head, x);
		__swap(alloc, x.alloc);
	}

	void resize(size_type n, value_type val = value_type()) {
		size_type _len = size();
		if (_len >= n) {
			iterator tmp = begin();
			while (n--) { ++tmp; }
			erase(tmp, end());
		} else {
			insert(end(), n - _len, val);
		}
	}

	void clear() {
		erase(begin(), end());
	}


// Operations
	void splice() {
		// TODO();
	}

	void remove(const value_type& val) {
		remove_if(
			[ &val ] (const value_type& _val) -> bool { return _val == val; }
		);
	}

	template <typename Predicate>
	void remove_if(Predicate pred) {
		iterator cur = begin(), last = end();
		while (cur != last) {
			if (pred(*cur)) {
				cur = erase(cur);
			} else {
				++cur;
			}
		}
	}

	void unique() {
		// TODO();
	}

	void merge() {
		// TODO();
	}

	void sort() {
		// TODO();
	}

	void reverse() {
		node_type *p1 = head.node;
		node_type *p2 = p1->prev;
		node_type *tmp_end = p2;
		while (p1 != tmp_end) {
			p2 = p1;
			p1 = p1->next;
			__swap(p2->next, p2->prev);
		}
		__swap(p1->next, p1->prev);
		head.node = p1->next;
	}


protected:
	iterator head;
	allocator_type alloc;
};

}// namespace ministl

#endif /* __MINI_STL_LIST_H */
