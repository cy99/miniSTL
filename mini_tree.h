/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_TREE_H
#define __MINI_STL_TREE_H		// Working...

#include <cstddef>		// for ptrdiff_t and size_t

#include "mini_construct.h"
#include "mini_allocator.h"


#include <iostream>		// for debug

using std::cout;
using std::endl;


namespace ministl {


// tree_node for type of T
template <typename T>
struct __tree_node {
public:
	typedef __tree_node<T>* link_type;
	typedef T value_type;

	link_type parent;
	link_type left;
	link_type right;

	value_type value;

public:
	__tree_node(const value_type& val = value_type(),
					link_type p = NULL, link_type l = NULL, link_type r = NULL)
	: value(val), parent(p), left(l), right(r) {}

};


// Data Structure - Tree
template <typename T, typename Alloc = allocator<T> >
class __tree_base {
public:
	
	typedef T value_type;
	typedef __tree_node<value_type> node_type;
	typedef node_type* link_type;
	typedef typename Alloc::template rebind<node_type>::other allocator_type;
	typedef size_t size_type;

protected:
	static link_type __create_node(const value_type& val = value_type()) {
		link_type tmp = alloc.allocate(1);
		construct(tmp, val);
		return tmp;
	}

	static void __destroy(link_type p) {
		destroy(&(p->value));
		alloc.deallocate(p);
	}

	static link_type __create_root(const value_type& val = value_type()) {
		header->parent = __create_node(val);
		header->left = header->right = header->parent;
		return header->parent;
	}


public:
	// initialize header
	__tree_base(const allocator_type& _allocator = allocator_type())
					: node_count(0), alloc(_allocator) {
		header = __create_node();
		root() = NULL;
		leftmost() = header;
		rightmost() = header;
	}

	inline size_type size() const { return node_count; }
	inline link_type& header() const { return header; }
	inline link_type& root() const { return header->parent; }

	// inline link_type& leftmost() const { return header->left; }
	// inline link_type& rightmost() const { return header->right; }

protected:
	link_type header;
	size_type node_count;
	allocator_type alloc;
};




// Iterator for Binary Search Tree.
template <typename T>
class binary_search_tree_iterator {

	typedef bidirectional_iterator_tag iterator_category;

	typedef T value_type;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef binary_search_tree_iterator<T> self;
	typedef __tree_node<T> node_type;
	typedef node_type* link_type;


// Aux functions
protected:
	inline static link_type leftmost(link_type p) const {
		while (p->left) { p = p->left; }
		return p;
	}

	inline static link_type rightmost(link_type p) const {
		while (p->right) { p = p->right; }
		return p;
	}


// Member functions
public:

	inline const_reference operator*() const { return node->value; }
	inline const_pointer operator->() const { return &(operator*()); }
	

	// 先用中文写吧，到时候再删掉
	// 下一个node是其右子树的leftmost的点
	// 若不存在 则找到某个祖先的右子节点不是上溯的点
	inline self& operator++() {
		if (node->right) {
			node = leftmost(node->right);
		} else {
			link_type tmp = node;
			while (tmp->parent->right == tmp) { tmp = tmp->parent; }
			node = tmp->parent;
		}
		return *this;
	}

	inline self operator++(int) {
		self tmp = *this;
		operator++();
		return tmp;
	}

	inline self& operator--() {
		if (node->left) {
			node = rightmost(node->left);
		} else {
			link_type tmp = node;
			while (tmp->parent->left == tmp) { tmp = tmp->parent; }
			node = tmp->parent;
		}
		return *this;
	}

	inline self operator--(int) {
		self tmp = *this;
		operator--();
		return tmp;
	}

	inline bool operator==(const self& rhs) const {
		return this->node == rhs.node;
	}

	inline bool operator!=(const self& rhs) const {
		return !(*this == rhs);
	}

// functions for debug
	void __show_node(link_type p) const {
		cout << p->value << " : ";
		cout << "left=>" << p->left->value << "  ";
		cout << "right=>" << p->right->value;
	}

	static void __show(link_type root) const {
		if (root->left) __show(root->left);
		__show_node(root);
		if (root->right) __show(root->right);
	}

	void show() const {
		cout << "Show the Tree" << endl;
		__show(root);
		cout << "End of Show" << endl;
	}


protected:
	link_type node;
};




// ***********************************************************
// Tree should have the functions as below:
//
// Compare function
// insert_unique, insert_equal
// key_compare, begin, end, empty, size, max_size, swap
// erase, clear
// find, count, lower_bound, upper_bound, equal_range
// operator==, operator<...
//


template <typename T>
struct compare_functor {
	int operator()(const T& a, const T& b) const {
		return a == b ? 0 : (a < b ? -1 : 1);
	}
};

// Binary Search Tree, inheriting from Tree Base.
template <typename T, typename Compare = compare_functor, typename Alloc = allocator<T> >
class binary_search_tree : public __tree_base<T, Alloc> {
public:

	enum RELATION {LESS = -1, EQUAL = 0, GREATER = 1};
	enum WHICH_CHILD {LEFTCHILD = -1, NODESELF = 0, RIGHTCHILD = 1};

	typedef T value_type;
	typedef Alloc allocator_type;
	typedef __tree_node<T> node_type;
	typedef node_type* link_type;

	typedef binary_search_tree_iterator<T> iterator;
	typedef RELATION relation_type;
	typedef WHICH_CHILD child_type;
	
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;


// Aux functions
protected:
	inline relation_type __comp_aux(const value_type& a, const value_type& b,
										__false_type) const {
		return (relation_type)key_compare(a, b);
	}

	inline relation_type __comp_aux(const value_type& a, const value_type& b,
										__true_type) const {
		return a == b ? EQUAL : (a < b ? LESS : GREATER);
	}
	
	inline relation_type __comp(const value_type& a, const value_type& b) const {
		typedef __Is_integer<value_type>::_Integral is_integral;
		return __comp_aux(a, b, is_integral());
	}

	iterator __insert(link_type position, const value_type& val, 
		child_type _which = NODESELF) {
		if (_which == NODESELF) {
			position->value = val;
			return position;
		}

		link_type tmp = __create_node(val);

		if (_which == LEFTCHILD) {
			position->left = tmp;
		} else if (_which == RIGHTCHILD) {
			position->right = tmp;
		}
		tmp->parent = position;

		if (__comp(val, leftmost()->value) == LESS) {
			leftmost() = tmp;
		} else if (__comp(val, rightmost()->value) != LESS) {
			rightmost() = tmp;
		}

		return tmp;
	}

// Member functions
	binary_search_tree(const Compare& _key_comp)
			: __tree_base<T, Alloc>(), key_compare(_key_comp) {}



	inline iterator begin() const { return header->left; }
	inline iterator end() const { return header; }

	
	// 无重插入
	// 从根节点开始跑，遇到小于的就往左跑，否则往右跑
	// 跑到没有，就取前一个
	iterator insert_unique(const value_type& val) {
		link_type p1 = root();
		if (p1 == NULL) {
			return __create_root();
		}

		link_type p2 = header();

		while (p1) {
			p2 = p1;
			p1 = __comp(val, p1->value) == LESS ? p1->left : p1->right;	
		}

		relation_type rel = __comp(val, p2->value);
		child_type _which;

		if (rel == LESS) {
			_which = LEFTCHILD;
		} else if (rel == GREATER) {
			_which = RIGHTCHILD;
		} else {
			_which = NODESELF;
		}
		
		return __insert(p2, val, _which);
	}

	// 有重插入
	// 相等时插入到等值结点的右边
	iterator insert_euqal(const value_type& val) {
		link_type p1 = root();
		if (p1 == NULL) {
			return __create_root();
		}

		link_type p2 = header();

		while (p1) {
			p2 = p1;
			p1 = __comp(val, p1->value) == LESS ? p1->left : p1->right;	
		}

		relation_type rel = __comp(val, p2->value);
		child_type _which;

		if (rel == LESS) {
			_which = LEFTCHILD;
		} else {
			_which = RIGHTCHILD;
		}

		return __insert(p2, val, _which);
	}

protected:
	Compare key_compare;
};





}// namespace ministl

#endif /* __MINI_STL_TREE_H */