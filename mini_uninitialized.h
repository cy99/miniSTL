/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */


#ifndef __MINI_STL_UNINITIALIZED_H
#define __MINI_STL_UNINITIALIZED_H	// Done.

#include "mini_iterator.h"		// for value_type()
#include "mini_construct.h"		// for construct() and destructor()
#include "mini_algo.h"			// for fill_n()


namespace ministl {

// Aux functions for uninitialized_fill_n
template <typename ForwardIter, typename Size, typename T>
inline ForwardIter __uninitialized_fill_n_aux(ForwardIter first, 
	Size n, const T& val, __true_type) {
	return fill_n(first, n, val);
}

template <typename ForwardIter, typename Size, typename T>
inline ForwardIter __uninitialized_fill_n_aux(ForwardIter first,
	Size n, const T& val, __false_type) {
	while(n--) { construct(&*(first++), val); }
	return first;
}

template <typename ForwardIter, typename Size, typename T, typename IterType>
inline ForwardIter __uninitialized_fill_n(ForwardIter first, 
	Size n, const T& val, IterType*) {
	typedef typename __type_traits<IterType>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first, n, val, is_POD());
}




// Aux functions for uninitialized_fill
template <typename ForwardIter, typename T, typename IterType>
inline void __uninitialized_fill(ForwardIter first,
	ForwardIter last, const T& val, IterType*) {
	typedef typename __type_traits<IterType>::is_POD_type is_POD;
	return __uninitialized_fill_aux(first, last, val, is_POD());
}

template <typename ForwardIter, typename T>
inline void __uninitialized_fill_aux(ForwardIter first,
	ForwardIter last, const T& val, __true_type) {
	fill(first, last, val);
}

template <typename ForwardIter, typename T>
inline void __uninitialized_fill_aux(ForwardIter first,
	ForwardIter last, const T& val, __false_type) {
	while (first != last) { construct(&*(first++), val); }
}




// Aux functions for uninitialized_copy
template <typename InputIter, typename ForwardIter>
inline ForwardIter __uninitialized_copy_aux(InputIter first, 
	InputIter last, ForwardIter dest, __true_type) {
	return copy(first, last, dest);
}

template <typename InputIter, typename ForwardIter>
inline ForwardIter __uninitialized_copy_aux(InputIter first, 
	InputIter last, ForwardIter dest, __false_type) {
	while (first != last) { construct(&*(dest++), *(first++)); }
	return dest;
}

template <typename InputIter, typename ForwardIter, typename IterType>
inline ForwardIter __uninitialized_copy(InputIter first, 
	InputIter last, ForwardIter dest, IterType*) {
	typedef typename __type_traits<IterType>::is_POD_type is_POD;
	return __uninitialized_copy_aux(first, last, dest, is_POD());
}








// ------------------- API -------------------
// all functions below should abide by "commit or rollback"

template <typename ForwardIter, typename Size, typename T>
inline ForwardIter uninitialized_fill_n(ForwardIter first, 
	Size n, const T& val) {
	return __uninitialized_fill_n(first, n, val, value_type(first));
}

template <typename ForwardIter, typename T>
inline void uninitialized_fill(ForwardIter first,
	ForwardIter last, const T& val) {
	__uninitialized_fill(first, last, val, value_type(first));
}


template <typename InputIter, typename ForwardIter>
inline ForwardIter uninitialized_copy(InputIter first, 
	InputIter last, ForwardIter dest) {
	return __uninitialized_copy(first, last, dest, value_type(first));
}



}// namespace ministl

#endif /* __MINI_STL_UNINITIALIZED_H */