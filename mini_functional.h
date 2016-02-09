/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_FUNCTIONAL_H
#define __MINI_STL_FUNCTIONAL_H		// Working...

namespace ministl {

template <typename Arg1, typename Arg2, typename Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};


template <typename T>
struct less : binary_function<T, T, bool> {
	inline bool operator()(const T& x, const T& y) const { return x < y; }
};

}// namespace ministl

#endif /* __MINI_STL_FUNCTIONAL_H */


