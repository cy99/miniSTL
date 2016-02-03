/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */


#ifndef __MINI_STL_TYPE_TRAITS_H
#define __MINI_STL_TYPE_TRAITS_H	// Done.


struct __true_type {};		// tag
struct __false_type {};		// tag



// General
template <typename T>
class __type_traits {
public:
	typedef __true_type		why_this_member_must_be_here;	// why?

	typedef __false_type 	has_trivial_default_constructor;
	typedef __false_type 	has_trivial_copy_constructor;
	typedef __false_type 	has_trivial_assignment_operator;
	typedef __false_type 	has_trivial_destructor;
	typedef __false_type 	is_POD_type;
};


#define Specialization(type) \
template <>\
class __type_traits<(type)> {\
public:\
	typedef __true_type 	has_trivial_default_constructor;\
	typedef __true_type 	has_trivial_copy_constructor;\
	typedef __true_type 	has_trivial_assignment_operator;\
	typedef __true_type 	has_trivial_destructor;\
	typedef __true_type 	is_POD_type;\
}\

#ifdef Specialization(type)

Specialization(char);
Specialization(signed char);
Specialization(unsigned char);
Specialization(short);
Specialization(unsigned short);
Specialization(int);
Specialization(unsigned int);
Specialization(long);
Specialization(unsigned long);
Specialization(float);
Specialization(double);
Specialization(long double);


#else

// -------------- Deserted ---------------


// Specialization
template <>
class __type_traits<char> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<signed char> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<unsigned char> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<short> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<unsigned short> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<int> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<unsigned int> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<long> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<unsigned long> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<float> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<double> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

template <>
class __type_traits<long double> {
public:
	typedef __true_type 	has_trivial_default_constructor;
	typedef __true_type 	has_trivial_copy_constructor;
	typedef __true_type 	has_trivial_assignment_operator;
	typedef __true_type 	has_trivial_destructor;
	typedef __true_type 	is_POD_type;
};

#endif	// Macro takes the place of these.

#endif /* __MINI_STL_TYPE_TRAITS_H */

// Done.