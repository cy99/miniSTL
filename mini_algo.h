/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */


#ifndef __MINI_STL_ALGO_H
#define __MINI_STL_ALGO_H

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

template <typename T>
void push_heap() {}


}// namespace ministl

#endif /* __MINI_STL_ALGO_H */
