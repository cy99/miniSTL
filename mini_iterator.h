/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */


#ifndef __MINI_STL_ITERATOR_H
#define __MINI_STL_ITERATOR_H

namespace ministl {

template <typename T>
inline T* value_type(const T*) {
	return (T*)0;
}

}// namespace ministl

#endif /* __MINI_STL_ITERATOR_H */