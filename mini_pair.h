/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_PAIR_H
#define __MINI_STL_PAIR_H		// Done.



namespace ministl {

template <typename T1, typename T2>
struct pair {

// Member types
	typedef T1 first_type;
	typedef T2 second_type;

// Member variables
	first_type first;
	second_type second;

// Member functions
	pair() : first(first_type()), second(second_type()) {}

	pair(const first_type& a, const second_type& b) : first(a), second(b) {}

	template <typename U, typename V>
	pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

	pair& operator=(const pair& pr) {
		first = pr.first;
		second = pr.second;
		return *this;
	}

// Relational operators
	bool operator==(const pair& rhs) const {
		return this->first == rhs.first && this->second == rhs.second;
	}

	bool operator<(const pair& rhs) const {
		return (this->first < rhs.first) 
					|| (!(rhs.first < this->first) && this->second < rhs.second);
	}

	bool operator!=(const pair& rhs) const {
		return !(*this == rhs);
	}

	bool operator>(const pair& rhs) const {
		return rhs < *this;
	}

	bool operator<=(const pair& rhs) const {
		return !(*this > rhs);
	}

	bool operator>=(const pair& rhs) const {
		return !(*this < rhs);
	}
};


}// namespace ministl

#endif /* __MINI_STL_PAIR_H */