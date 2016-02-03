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
	// TODO();	// New Effective Implementation
}

template <typename OutputIterator, typename Size, typename T>
inline OutputIterator fill_n(OutputIterator first, Size n, const T& val) {
	// Temporary Implementation
	while (n--) { *(first++) = val; }
	return first;
	// TODO();	// New Effective Implementation
}

template <typename InputIterator, typename OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest) {
	// Temporary Implementation
	while(first != last) { *(dest++) = *(first++); }
	return dest;
	// TODO(); // New Effective Implementation
}



}// namespace ministl

#endif /* __MINI_STL_ALGO_H */