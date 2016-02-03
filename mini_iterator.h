/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */


#ifndef __MINI_STL_ITERATOR_H
#define __MINI_STL_ITERATOR_H

#include <cstddef>		// for ptrdiff_t

namespace ministl {

// Iterator Base Class
template <typename Category, typename Value_type, typename Distance = ptrdiff_t,
		typename Pointer = T*, typename Reference = T&>
class iterator_base {
	typedef Category		iterator_category;
	typedef Value_type		value_type;
	typedef Distance		difference_type;
	typedef Pointer			pointer;
	typedef Reference		reference;
};

/* Iterator Category :
 * 
 * InputIterator
 * OutputIterator
 * ForwardIterator
 * BidirectionalIterator
 * RandomAccessIterator
 *
 */

// Tag
	struct input_iterator_tag {};
	struct out_itertor_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};




template <typename T>
class iterator_traits {
public:
	typedef typename T::value_type value_type;
	typedef typename T::iterator_category iterator_category;
	typedef typename T::difference_type difference_type;
	typedef typename T::pointer pointer;
	typedef typename T::reference reference;
};

// Specialization for native pointer
template <typename T>
class iterator_traits<T*> {
public:
	typedef T value_type;
	typedef random_access_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef &T reference;
};
// Specialization for native pointer-to-const
template <typename T>
class iterator_traits<const T*> {
public:
	typedef T value_type;
	typedef random_access_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	typedef const T* pointer;
	typedef const &T reference;
};




template <typename T>
inline typename iterator_traits<T>::iterator_category
iterator_category(const &T) {	// input the iterator and return the category tag.
	typedef typename iterator_traits<T>::iterator_category iterator_category;
	return iterator_category();
}

template <typename T>
inline typename iterator_traits<T>::value_type*
value_type(const T&) {
	return static_cast<typename iterator_traits<T>::value_type*>(0);
}

template <typename T> 
inline typename iterator_traits<T>::difference_type*
distance_type(const &T) {
	return static_cast<typename iterator_traits<T>::difference_type*>(0);
}


// distance
template <typename InputIterator>
typename iterator_traits<InputIterator>::difference_type
__distance (InputIterator first, InputIterator last, random_access_iterator_tag) {
	typedef typename iterator_traits<InputIterator>::difference_type diff_type;
	return static_cast<diff_type>(last - first);
}

template <typename InputIterator>
typename iterator_traits<InputIterator>::difference_type
__distance (InputIterator first, InputIterator last, input_iterator_tag) {
	typename iterator_traits<InputIterator>::difference_type dist = 0;
	while (first++ != last) {++dist;}
	return dist;
}

template <typename InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance (InputIterator first, InputIterator last) {
	return __distance(first, last, iterator_category(first));
}



// advance
template <typename InputIterator, typename Distance>
void __advance(InputIterator& it, Distance n, random_access_iterator_tag) {
	it += n;
}

template <typename InputIterator, typename Distance>
void __advance(InputIterator& it, Distance n, bidirectional_iterator_tag) {
	if (n > 0) { while (n--) { ++it; } }
	else { while (n++) { --it; } }
}

template <typename InputIterator, typename Distance>
void __advance(InputIterator& it, Distance n, input_iterator_tag) {
	while (n--) { ++it; }
}

template <typename InputIterator, typename Distance>
void advance(InputIterator& it, Distance n) {
	return __advance(it, n, iterator_category(it));
}





// ------ reverse iterator -------
template <typename Iterator>
class reverse_iterator {
public:
	reverse_iterator();
	reverse_iterator(iterator_type it) {
		// TODO();
	}
	base() {
		// TODO();
	}
#if 0	// TODO();
operator*
operator+
operator++
operator+=
operator-
operator--
operator-=
operator->
operator[]
#endif	// TODO();
};


}// namespace ministl

#endif /* __MINI_STL_ITERATOR_H */