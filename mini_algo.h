/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */


#ifndef __MINI_STL_ALGO_H
#define __MINI_STL_ALGO_H

#include "mini_functional.h"	// for less<T> and greater<T>

namespace ministl {

template <typename ForwardIterator, typename T>
inline void fill(ForwardIterator first, ForwardIterator last, const T& val) {
	// Temporary Implementation
	while (first != last) { *(first++) = val; }
	// TODO();	// Expect a new Effective Implementation
}

template <typename OutputIterator, typename Size, typename T>
inline OutputIterator fill_n(OutputIterator first, Size n, const T& val) {
	// Temporary Implementation
	while (n--) { *(first++) = val; }
	return first;
	// TODO();	// Expect a new Effective Implementation
}

template <typename InputIterator, typename OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest) {
	// Temporary Implementation
	while(first != last) { *(dest++) = *(first++); }
	return dest;
	// TODO(); // Expect a new Effective Implementation
}

template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2 copy_backward(BidirectionalIter1 first,
						BidirectionalIter1 last, BidirectionalIter2 dest) {
	while (last != first) { *(--dest) = *(--last); }	// dest is a tail.
	return dest;
}

template <typename T> void swap(T& a, T& b) {
	T tmp(a); a = b; b = tmp;
}


// you should make sure that they have the same size before using equal().
template <typename InputIterator1, typename InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2) {
	while (first1 != last1) {
		if (!(*first1 == *first2)) { return false; }
		++first1; ++first2;
	}
	return true;
}

template <typename InputIterator1, 
					typename InputIterator2, typename BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred) {
	while (first1 != last1) {
		if (!pred(*first1, *first2)) { return false; }
		++first1; ++first2;
	}
	return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2) {
	while (first1 != last1) {
		if (first2 == last2 || *first2 < *first1) { return false; }
		else if (*first1 < *first2) { return true; }
		++first1; ++first2;
	}
	return first2 != last2;
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, Compare comp) {
	while (first1 != last1) {
		if (first2 == last2 || comp(*first2, *first1)) { return false; }
		else if (*first1 < *first2) { return true; }
		++first1; ++first2;
	}
	return first2 != last2;
}

template <typename ForwardIterator1, typename ForwardIterator2>
void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
	ministl::swap(*a, *b);
}

template <typename BidirectionalIterator>
void reverse(BidirectionalIterator first, BidirectionalIterator last) {
	while ((first != last) && (first != --last)) {
		ministl::iter_swap(first, last);
		++first;
	}
}

template <typename InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T& val) {
	while (first != last) {
		if (*first == val) return first;
		++first;
	}
	return last;
}





// ---------------------- Aux function -------------------------

template <typename RandomAccessIterator, 
				typename Distance, typename T, typename Compare = ministl::less<T> >
static void __push_heap_aux(RandomAccessIterator first, Distance holeIndex, 
				Distance topIndex, T val, const Compare& comp = Compare()) {

	Distance parentIndex = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(*(first + parentIndex), val)) {
		*(first + holeIndex) = *(first + parentIndex);
		holeIndex = parentIndex;
		parentIndex = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;

}


template <typename RandomAccessIterator, 
				typename Distance, typename T, typename Compare = ministl::less<T> >
static inline void __push_heap(RandomAccessIterator first, RandomAccessIterator last, 
				Distance*, T*, const Compare& comp = Compare()) {
	__push_heap_aux(first, Distance((last - first) - 1), 
								Distance(0), T(*(last - 1)), comp);
}


template <typename RandomAccessIterator, 
				typename Distance, typename T, typename Compare = ministl::less<T> >
static void __adjust_heap(RandomAccessIterator first, Distance holeIndex, 
			Distance len, T val, const Compare& comp = Compare()) {

	Distance topIndex = holeIndex;
	Distance secondChild = 2 * (holeIndex + 1);
	while (secondChild < len) {
		if (comp(*(first + secondChild), *(first + (secondChild - 1)))) {
			--secondChild;
		}
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}

	if (secondChild == len) {
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}

	__push_heap_aux(first, holeIndex, topIndex, val, comp);
}


template <typename RandomAccessIterator, 
				typename T, typename Distance, typename Compare = ministl::less<T> >
static inline void __pop_heap_aux(RandomAccessIterator first, 
			RandomAccessIterator last, RandomAccessIterator result, 
			T val, Distance*, const Compare& comp = Compare()) {
	*result = *first;
	__adjust_heap(first, Distance(0), Distance(last - first), val, comp);
}


template <typename RandomAccessIterator, 
				typename T, typename Compare = ministl::less<T> >
static inline void __pop_heap(RandomAccessIterator first, 
			RandomAccessIterator last, T*, const Compare& comp = Compare()) {
	__pop_heap_aux(first, last - 1, last - 1, 
				T(*(last - 1)), distance_type(first), comp);
}


template <typename RandomAccessIterator, 
				typename T, typename Distance, typename Compare = ministl::less<T> >
static void __make_heap(RandomAccessIterator first, RandomAccessIterator last, 
				T*, Distance*, const Compare& comp = Compare()) {

	Distance len = last - first;
	if (len < 2) return;
	Distance holeIndex = (len - 2) / 2;

	while (true) {
		__adjust_heap(first, holeIndex, len, T(*(first + holeIndex)), comp);
		if (holeIndex == 0) return;
		--holeIndex;
	}
}





// ----------------------- Heap -------------------------
// push_heap
template <typename RandomAccessIterator>
void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
	// The new element is already put at the end 
	//     of the container before calling this function.
	__push_heap(first, last, distance_type(first), value_type(first));
}

template <typename RandomAccessIterator, typename Compare>
void push_heap(RandomAccessIterator first, 
			RandomAccessIterator last, Compare comp) {
	// The new element is already put at the end 
	//     of the container before calling this function.
	__push_heap(first, last, distance_type(first), value_type(first), comp);
}


// pop_heap
template <typename RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
	// The top element is already popped and the last 
	//     element should be put away.
	__pop_heap(first, last, value_type(first));
}

template <typename RandomAccessIterator, typename Compare>
void pop_heap(RandomAccessIterator first, 
					RandomAccessIterator last, Compare comp) {
	// The top element is already popped and the last 
	//     element should be put away.
	__pop_heap(first, last, value_type(first), comp);
}


// sort_heap
template <typename RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
	while (last > first + 1) { pop_heap(first, last--); }
}

template <typename RandomAccessIterator, typename Compare>
void sort_heap(RandomAccessIterator first, 
					RandomAccessIterator last, Compare comp) {
	while (last > first + 1) { pop_heap(first, last--, comp); }
}


// make_heap
template <typename RandomAccessIterator>
void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
	__make_heap(first, last, value_type(first), distance_type(first));
}

template <typename RandomAccessIterator, typename Compare>
void make_heap(RandomAccessIterator first, 
					RandomAccessIterator last, Compare comp) {
	__make_heap(first, last, value_type(first), distance_type(first), comp);
}



}// namespace ministl

#endif /* __MINI_STL_ALGO_H */
