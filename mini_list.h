/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_LIST_H
#define __MINI_STL_LIST_H		// Done.

#include <cstddef>



namespace ministl {


template <typename T>
struct __list_node {
	__list_node<T>* prev;
	__list_node<T>* next;
	T data;

	__list_node(const T& val = T()) : prev(NULL), next(NULL), data(val) {}
};


template <typename T>
class __list_iterator {
public:
	typedef bidirectional_iterator_tag iterator_category;
	
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	
	typedef __list_node<T> node_type;
	typedef __list_iterator<T> self;

// Construct
public:
	__list_iterator(node_type* pt) : node(pt) {}

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
		tmp.node = tmp.node->next;
		return tmp;
	}

	inline self operator--(int) {
		self tmp = *this;
		tmp.node = tmp.node->prev;
		return tmp;
	}


protected:
	node_type* node;
};


template <typename T, typename Alloc = allocator<__list_node<T> > >
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
	typedef Alloc allocator_type;

	typedef __list_iterator<T> iterator;
	typedef __list_iterator<const T> const_iterator;

	typedef reverse_iterator_base<iterator> reverse_iterator;
	typedef reverse_iterator_base<const_iterator> const_reverse_iterator;



// Aux function
public:
	inline node_type __create_node(const_reference val) {
		node_type* tmp = alloc.allocate(1);
		construct(tmp, val);
		return tmp;
	}



public:
	allocator_type get_allocator() const { return alloc; }

	list(const allocator_type& _alloc = allocator_type())
					: head(NULL), alloc(_alloc) {}

	list(size_type n, const value_type& val = value_type(),
					const allocator_type& _alloc = allocator_type())
					: head(NULL), alloc(_alloc) {
		insert(head, n, val);
	}

	template <typename InputIterator>
	list(InputIterator first, InputIterator last,
			const allocator_type& _alloc = allocator_type()) : alloc(_alloc) {
		insert(first, last, head);
	}

	list(const list& x) : head(x.head), alloc(x.alloc) {}


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
	inline reference back() const { return *end(); }

	void assign() {
		// TODO();
	}

	void push_front() {
		// TODO();
	}

	void pop_front() {
		// TODO();
	}

	void push_back() {
		// TODO();
	}

	void pop_back() {
		// TODO();
	}

	iterator insert(iterator position, const_reference val) {
		node_type* tmp = __create_node(val);
		node_type* current = position.node;
		current->prev->next = tmp;
		tmp->prev = current->prev;
		tmp->next = current;
		current->prev = tmp;
		return iterator(tmp);
	}

	void insert(iterator position, size_type n, const_reference val) {
		while (n--) { insert(position, val); }
	}

	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last, iterator position) {
		while (first != last) { insert(position, *(first++)); }
	}

	void erase() {
		// TODO();
	}

	void swap() {
		// TODO();
	}

	void resize() {
		// TODO();
	}

	void clear() {
		// TODO();
	}


// Operations
	void splice() {
		// TODO();
	}

	void remove() {
		// TODO();
	}

	void remove_if() {
		// TODO();
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
		// TODO();
	}


protected:
	iterator head;
	allocator_type alloc;
};

}// namespace ministl

#endif /* __MINI_STL_LIST_H */