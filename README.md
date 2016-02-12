# miniSTL
Re-implementation of part of the stl in standard C++98.

---

Note : 
* Deque is not implemented for the time being.
* Stack and queue are container adaptors implemented by class list by default.
* Parts of operations in class list are to do.
* The binary search tree is the underlying data structure in map(multimap) and set(multiset), which would be upgraded to the AVL tree or the RBtree. (In spite of no  property of balance, the BST is efficient as the RBtree when it deals with the problems with not a very large-scale data.)
* Please use the "ministl" instead of "std" as the namespace. (Perhaps there would be some conflicts.)

--by AT_ on 2016.02.12

