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
#include "mini_algo.h"		// for equal() and lexicographical_compare()
#include "mini_iterator.h"	// for reverse_iterator_base<T>
#include "mini_algo.h"		// for swap()
#include "mini_pair.h"		// for pair<A, B>

#include <new>			// for new

#include <iostream>		// for debug

using std::cout;
using std::endl;


namespace ministl {


// Functor
template <typename T>
struct compare_functor {
	bool operator()(const T& a, const T& b) const {
		return a < b;
	}
};

template <typename T, typename Compare = compare_functor<T>, 
			typename Alloc = allocator<T> > class binary_search_tree;



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
	: parent(p), left(l), right(r), value(val) {}

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
	link_type __create_node(const value_type& val = value_type()) {
		link_type tmp = alloc.allocate(1);
		ministl::construct(tmp, val);
		++node_count;
		return tmp;
	}

	void __destroy_node(link_type p) {
		ministl::destroy(&(p->value));
		alloc.deallocate(p);
		--node_count;
	}

	link_type __create_root(const value_type& val = value_type()) {
		header->parent = __create_node(val);
		leftmost() = rightmost() = header->parent;
		root()->parent = header;
		return root();
	}

	void __destroy_root() {
		__destroy_node(root());
		root() = NULL;
		leftmost() = rightmost() = header;
	}

	void __destroy_header() {
		++node_count;
		__destroy_node(header);
		header = NULL;
	}


public:
	// initialize header
	__tree_base(const allocator_type& _allocator = allocator_type())
					: alloc(_allocator) {
		header = __create_node();
		root() = NULL;
		leftmost() = header;
		rightmost() = header;
		node_count = 0;
	}

	~__tree_base() {
		__destroy_header();
	}

	inline size_type size() const { return node_count; }
	inline link_type& root() const { return header->parent; }
	inline bool empty() const { return header->parent == NULL; }


	inline link_type& leftmost() const { return header->left; }
	inline link_type& rightmost() const { return header->right; }



// ----------------------------------------------------------------------
// functions for debug
	void __show_node(link_type p) const {
		cout << p->value << " : ";
		if (p->left) cout << "left=>" << p->left->value << "  ";
		if (p->right) cout << "right=>" << p->right->value;
	}

	void __show(link_type root) const {
		if (!root) return;
		if (root->left) __show(root->left);
		__show_node(root); cout << endl;
		if (root->right) __show(root->right);
	}

	void show() const {
		cout << "Show the Tree" << endl;
		__show(root());
		cout << "End of Show" << endl;
	}
// ----------------------------------------------------------------------



protected:
	link_type header;
	size_type node_count;
	allocator_type alloc;
};



// Iterator for Binary Search Tree.
template <typename T, typename Ref = T&, typename Ptr = T*>
class binary_search_tree_iterator {

public:

	friend binary_search_tree<T>;

	typedef bidirectional_iterator_tag iterator_category;

	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef binary_search_tree_iterator<T, T&, T*> iterator;
	typedef binary_search_tree_iterator<T, const T&, const T*> const_iterator;
	typedef binary_search_tree_iterator<T, Ref, Ptr> self;
	typedef __tree_node<T> node_type;
	typedef node_type* link_type;

	friend const_iterator;
	friend iterator;


protected:
// Aux Functions
inline link_type __leftmost(link_type p) const {
	while (p->left) { p = p->left; }
	return p;
}

inline link_type __rightmost(link_type p) const {
	while (p->right) { p = p->right; }
	return p;
}


// Member functions
public:

	binary_search_tree_iterator(link_type p = NULL) : node(p) {}

	binary_search_tree_iterator(const iterator& x) : node(x.node) {}
	binary_search_tree_iterator(const const_iterator& x) : node(x.node) {}

	inline reference operator*() const { return node->value; }
	inline pointer operator->() const { return &(operator*()); }


	// 先用中文写吧，到时候再删掉
	// 下一个node是其右子树的__leftmost的点
	// 若不存在 则找到某个祖先的右子节点不是上溯的点
	inline self& operator++() {
		if (node->right) {
			node = __leftmost(node->right);
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
			node = __rightmost(node->left);
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




// Binary Search Tree, inheriting from Tree Base.
template <typename T, typename Compare, typename Alloc>
class binary_search_tree : public __tree_base<T, Alloc> {
public:

	enum RELATION {GREATER = -1, EQUAL = 0, LESS = 1};
	enum WHICH_CHILD {LEFTCHILD = -1, NODESELF = 0, RIGHTCHILD = 1};

	typedef T value_type;
	typedef Alloc allocator_type;
	typedef __tree_node<T> node_type;
	typedef node_type* link_type;
	typedef binary_search_tree<T, Compare, Alloc> self;

	typedef typename binary_search_tree_iterator<T>::iterator iterator;
	typedef typename binary_search_tree_iterator<T>::const_iterator const_iterator;
	typedef reverse_iterator_base<iterator> reverse_iterator;
	typedef reverse_iterator_base<const_iterator> const_reverse_iterator;

	typedef RELATION relation_type;
	typedef WHICH_CHILD child_type;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;


// Aux functions
protected:
	inline relation_type __comp_aux(const value_type& a, const value_type& b,
										__false_type) const {
		return key_compare(a, b) ? LESS : (key_compare(b, a) ? GREATER : EQUAL);
	}

	inline relation_type __comp_aux(const value_type& a, const value_type& b,
										__true_type) const {
		return a == b ? EQUAL : (a < b ? LESS : GREATER);
	}

	inline relation_type __comp(const value_type& a, const value_type& b) const {
		typedef typename __Is_integer<value_type>::_Integral is_integral;
		return __comp_aux(a, b, is_integral());
	}

	iterator __insert(link_type position, const value_type& val,
		child_type _which = NODESELF) {
		if (_which == NODESELF) {
			position->value = val;
			return position;
		}

		link_type tmp = this->__create_node(val);

		if (_which == LEFTCHILD) {
			position->left = tmp;
		} else if (_which == RIGHTCHILD) {
			position->right = tmp;
		}
		tmp->parent = position;

		if (__comp(val, this->leftmost()->value) == LESS) {
			this->leftmost() = tmp;
		} else if (__comp(val, this->rightmost()->value) != LESS) {
			this->rightmost() = tmp;
		}

		return tmp;
	}

	// Aux Functions
	inline link_type __leftmost(link_type p) const {
		while (p->left) { p = p->left; }
		return p;
	}

	inline link_type __rightmost(link_type p) const {
		while (p->right) { p = p->right; }
		return p;
	}

	// 返回新的树的root
	// 首先确定搞它左儿子还是右儿子 size奇数擦除左边 偶数右边
	// 擦除root点后用其左子树的rightmost或者其右子树的leftmost来代替
	// 注意到rightmost没有右子树 & leftmost没有左子树
	// 所以只需将其另一棵子树连接在其parent上就ok了
	// 注意特殊情况 当root的左子树的rightmost就是其左儿子 就需要分类讨论
	//
	link_type __erase_aux(link_type root) {
		child_type _which = NODESELF;

		if (root->left && root->right) {
			_which = this->size() / 2 == 0 ? RIGHTCHILD : LEFTCHILD;
		} else if (root->left) {
			_which = LEFTCHILD;
		} else if (root->right) {
			_which = RIGHTCHILD;
		}

		link_type new_root;		// the root of new tree

		if (_which == LEFTCHILD) {

			new_root = __rightmost(root->left);

			if (new_root == root->left) {	// corner case
				new_root->right = root->right;
				if (new_root->right) new_root->right->parent = new_root;
			} else {
				new_root->parent->right = new_root->left;
				if (new_root->left) new_root->left->parent = new_root->parent;

				new_root->left = root->left;
				if (root->left) root->left->parent = new_root;

				new_root->right = root->right;
				if (root->right) root->right->parent = new_root;
			}

		} else if (_which == RIGHTCHILD) {

			new_root = __leftmost(root->right);

			if (new_root == root->right) {	// corner case
				new_root->left = root->left;
				if (new_root->left) new_root->left->parent = new_root;
			} else {
				new_root->parent->left = new_root->right;
				if (new_root->right) new_root->right->parent = new_root->parent;

				new_root->right = root->right;
				if (root->right) root->right->parent = new_root;

				new_root->left = root->left;
				if (root->left) root->left->parent = new_root;
			}

		} else {
			new_root = NULL;
		}

		this->__destroy_node(root);
		return new_root;
	}

	// 擦除某结点 首先要处理和它相关的结点
	// 首先记录下被删结点的parent 然后处理以被删结点为root的子树
	// 变成一棵新的树后重新连上parent上 注意是左儿子还是右儿子
	void __erase(link_type p) {
		link_type _parent = p->parent;
		
		link_type new_root = __erase_aux(p);

		if (p == this->root()) {
			_parent->parent = new_root;	
		} else {
			(_parent->left == p? _parent->left : _parent->right) = new_root;
		}

		if (new_root) new_root->parent = _parent;
	}

	link_type __lower_bound(const value_type& val) const {
		link_type p1 = this->root();
		link_type p2 = this->header;
		while (p1) {
			if (__comp(p1->value, val) != LESS) {
				p2 = p1; p1 = p1->left;
			} else {
				p1 = p1->right;
			}
		}
		return p2;
	}

	link_type __upper_bound(const value_type& val) const {
		link_type p1 = this->root();
		link_type p2 = this->header;
		while (p1) {
			if (__comp(val, p1->value) == LESS) {
				p2 = p1; p1 = p1->left;
			} else {
				p1 = p1->right;
			}
		}
		return p2;
	}

	ministl::pair<iterator, iterator> __equal_range(const value_type& val) const {
		return ministl::pair<iterator, iterator>(
			__lower_bound(val), __upper_bound(val)
		);
	}


public:
// Member functions
	binary_search_tree(const Compare& _key_comp = Compare())
				: __tree_base<T, Alloc>(), key_compare(_key_comp) {}

	binary_search_tree(const self& x) 
			: key_compare(x.key_compare) {
		insert_equal(x.begin(), x.end());
	}


	~binary_search_tree() { clear(); }

	iterator begin() { return iterator(this->leftmost()); }
	iterator end() { return iterator(this->header); }
	const_iterator begin() const { return this->leftmost(); }
	const_iterator end() const { return this->header; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator(begin());
	}


	inline bool operator==(const self& rhs) const {
		return this->size() == rhs.size() ?
				ministl::equal(begin(), end(), rhs.begin()) : false;
	}

	inline bool operator<(const self& rhs) const {
		return ministl::lexicographical_compare(
						begin(), end(), rhs.begin(), rhs.end(), key_compare);
	}

	self& operator=(const self& x) {
		insert_unique(x.begin(), x.end());
		return *this;
	}

	iterator find(const value_type& val) const {
		link_type p = this->root();
		while (p) {
			relation_type rel = __comp(val, p->value);
			if (rel == EQUAL) { return iterator(p); }
			p = rel == LESS ? p->left : p->right;
		}
		return end();
	}

	void clear() {
		if (this->root() == NULL) return;

		size_type _Size = this->size();
		link_type* _stack = new link_type[_Size + 1];	// stack bottom
		link_type* _top = _stack;	// stack top

		*(_top++) = this->root();
		while (_top != _stack) {
			link_type tmp = *(--_top);	// pick out the element at the top
			if (tmp->right) *(_top++) = tmp->right;
			if (tmp->left) *(_top++) = tmp->left;

			this->__destroy_node(tmp);
		}

		delete[] _stack;

		this->root() = NULL;
		this->leftmost() = this->rightmost() = this->header;
	}

	Compare key_comp() const { return key_compare(); }
	void swap(self& x) {
		ministl::swap(this->header, x.header);
		ministl::swap(this->node_count, x.node_count);
	}

	size_type count(const value_type& val) const {
		iterator tmp = find(val);
		if (tmp == end()) return 0;
		size_type sum = 1;
		if (__comp(*(++tmp), val) == EQUAL) { ++sum; }
		return sum;
	}

	iterator lower_bound(const value_type& val) {
		return __lower_bound(val);
	}

	const_iterator lower_bound(const value_type& val) const {
		return __lower_bound(val);
	}

	iterator upper_bound(const value_type& val) {
		return __upper_bound(val);
	}

	const_iterator upper_bound(const value_type& val) const {
		return __upper_bound(val);
	}

	ministl::pair<iterator, iterator> equal_range(const value_type& val) {
		return __equal_range(val);
	}

	ministl::pair<const_iterator, const_iterator> 
						equal_range(const value_type& val) const {
		return __equal_range(val);
	}

	allocator_type get_allocator() const { return this->alloc; }

// ------- Insert --------

	// 无重插入
	// 从根节点开始跑，遇到小于的就往左跑，否则往右跑
	// 跑到没有，就取前一个
	ministl::pair<iterator, bool> insert_unique(const value_type& val) {
		link_type p1 = this->root();
		if (p1 == NULL) {
			return ministl::pair<iterator, bool>(
				iterator(this->__create_root(val)), true
			);
		}

		link_type p2 = this->header;

		while (p1) {
			p2 = p1;
			relation_type _rel = __comp(val, p1->value);
			if (_rel == LESS) p1 = p1->left;
			else if (_rel == GREATER) p1 = p1->right;
			else return ministl::pair<iterator, bool>(iterator(NULL), false);
			// p1 = __comp(val, p1->value) == LESS ? p1->left : p1->right;
		}

		child_type _which = 
			(__comp(val, p2->value) == LESS ? LEFTCHILD : RIGHTCHILD);

		return ministl::pair<iterator, bool>(
			__insert(p2, val, _which), true
		);
	}

	
	iterator insert_unique(iterator position, const value_type& val) {
		// TODO();
		return insert_unique(val).first;	// perfunctory
	}

	template <typename InputIterator>
	void insert_unique(InputIterator first, InputIterator last) {
		while (first != last) { insert_unique(*(first++)); }
	}

	// 有重插入
	// 相等时插入到等值结点的右边
	iterator insert_equal(const value_type& val) {
		link_type p1 = this->root();
		if (p1 == NULL) {
			return this->__create_root(val);
		}

		link_type p2 = this->header;

		while (p1) {
			p2 = p1;
			p1 = __comp(val, p1->value) == LESS ? p1->left : p1->right;
		}

		relation_type rel = __comp(val, p2->value);
		child_type _which = (rel == LESS ? LEFTCHILD : RIGHTCHILD);

		return __insert(p2, val, _which);
	}

	template <typename InputIterator>
	void insert_equal(InputIterator first, InputIterator last) {
		while (first != last) { insert_equal(*(first++)); }
	}

// ------- Erase --------

	iterator erase(iterator position) {
		iterator tmp = position;
		++tmp;
		
		if (position == this->leftmost()) {
			this->leftmost() = tmp.node;
		}

		if (position == this->rightmost()) {
			this->rightmost() = tmp.node;
		}
		
		__erase(position.node);
		
		return tmp;
	}

	size_type erase(const value_type& val) {
		iterator position = this->find(val);
		if (position == end()) return this->size();
		erase(position);
		return this->size();
	}

	iterator erase(iterator first, iterator last) {
		while (first != last) {
			first = erase(first);
		}
		return first;
	}



protected:
	Compare key_compare;
};





}// namespace ministl

#endif /* __MINI_STL_TREE_H */
