/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */


#ifndef __MINI_STL_CONSTRUCT_H
#define __MINI_STL_CONSTRUCT_H	// Done.


#include "mini_type_traits.h"	// for __type_traits<T>
#include "mini_iterator.h"		// for value_type<T>


namespace ministl {
// Aux functions

template <typename ForwardIterator, typename T>
inline void _Destroy_aux_aux(ForwardIterator first, ForwardIterator last,
	__true_type, T*) { /* do nothing */ }

template <typename ForwardIterator, typename T>
inline void _Destroy_aux_aux(ForwardIterator first, ForwardIterator last,
	__false_type, T*) {
	while (first != last) {
        destroy(&*(first++));
	}//{ first->~T(); ++first; }
}


template <typename ForwardIterator, typename T>
inline void _Destroy_aux(ForwardIterator first, ForwardIterator last, T*) {
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	_Destroy_aux_aux(first, last, trivial_destructor(), (T*)0);
}



template <typename T>
inline void _Construct(T* buffer) {
	new((void*)buffer) T();
}

template <typename T1, typename T2>
inline void _Construct(T1* buffer, const T2& value) {
	new((void*)buffer) T1(value);
}

template <typename T>
inline void _Destroy(T* buffer) {
	buffer->~T();
}

template <typename ForwardIterator>
inline void _Destroy(ForwardIterator first, ForwardIterator last) {
	_Destroy_aux(first, last, value_type(first));
}



// ---------------- API -----------------

template <typename T>
inline void construct(T* p) {
	_Construct(p);
}

template <typename T1, typename T2>
inline void construct(T1* p, const T2& val) {
	_Construct(p, val);
}

template <typename T>
inline void destroy(T* p) {
	_Destroy(p);
}

template <typename ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
	_Destroy(first, last);
}

}// namespace ministl

#endif /* __MINI_STL_CONSTRUCT_H */
