/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_TREE_H
#define __MINI_STL_TREE_H		// Working...

namespace ministl {

#if 1

#include <iostream>

using std::cout;
using std::endl;

struct Node {
// This is the node class.
    Node *left;
    Node *right;
    int value;

    Node() : left(0), right(0), value(0) {}
    Node(const int& _data) : left(0), right(0), value(_data){}

    void show() {
        cout << "Node " << value << " : ";
        if (left) cout << "left->" << left->value << "  ";
        if (right) cout << "right->" << right->value << "  ";
        cout << endl;
    }
};




class BST {
// This is the class of the binary search tree.
public:
	// Aux function

	template <typename T> const T& max(const T& a, const T& b) {
		return a > b ? a : b;
	}

	void __show(Node* root) {
	    if (!root) return;
	    __show(root->left);
	    root->show();
	    __show(root->right);
	}

	size_t __depth(Node* root) {
		if (!root) return 0;
		return 1 + max(__depth(root->left), __depth(root->right));
	}

	size_t __size(Node* root) {
		if (!root) return 0;
		return __size(root->left) + __size(root->right) + 1;
	}

	void __insert(Node*& root, const int& num) {
		Node* p1 = root, *p2 = NULL;

        while (p1) {
            p2 = p1;
            p1 = num < p1->value ? p1->left : p1->right;
        }

        (p2 ? (num < p2->value ? p2->left : p2->right) : root) = new Node(num);
	}

	Node* most_right(Node* pt) {
		while (pt->right) { pt = pt->right; }
		return pt;
	}

	Node* most_left(Node* pt) {
		while (pt->left) { pt = pt->left; }
		return pt;
	}

	Node* __erase_aux(Node* pt) {
		// pt is what I want to delete.
		// It will return the root of the new child tree.
		if (pt->left && pt->right) {
			if (__depth(pt->left) > __depth(pt->right)) {
				Node* p1 = pt->left, *p2 = pt;
				while (p1->right) {
					p2 = p1;
					p1 = p1->right;
				}
				(p2 == pt ? p2->left : p2->right) = p1->left;
				p1->left = pt->left;
				p1->right = pt->right;
				return p1;
			} else {
				Node* p1 = pt->right, *p2 = pt;
				while (p1->left) {
					p2 = p1;
					p1 = p1->left;
				}
				(p2 == pt ? p2->right : p2->left) = p1->right;
				p1->right = pt->right;
				p1->left = pt->left;
				return p1;
			}
		} else if (pt->left) {
			return pt->left;
		} else if (pt->right) {
			return pt->right;
		} else {
			return NULL;
		}
	}


#endif // BST



}// namespace ministl

#endif /* __MINI_STL_TREE_H */