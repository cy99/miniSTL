/*
 * Copyrigth (c) 2016 by AT_
 * Re-implementation of mini STL
 * For skilled STL and C++
 */


#ifndef __MINI_STL_TYPE_TRAITS_H
#define __MINI_STL_TYPE_TRAITS_H	// Done.


namespace ministl {

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


#define Type_Traits_Specialization(type) template <>\
class __type_traits<type> {\
public:\
	typedef __true_type 	has_trivial_default_constructor;\
	typedef __true_type 	has_trivial_copy_constructor;\
	typedef __true_type 	has_trivial_assignment_operator;\
	typedef __true_type 	has_trivial_destructor;\
	typedef __true_type 	is_POD_type;\
}

#ifdef Type_Traits_Specialization

Type_Traits_Specialization(char);
Type_Traits_Specialization(signed char);
Type_Traits_Specialization(unsigned char);
Type_Traits_Specialization(short);
Type_Traits_Specialization(unsigned short);
Type_Traits_Specialization(int);
Type_Traits_Specialization(unsigned int);
Type_Traits_Specialization(long);
Type_Traits_Specialization(unsigned long);
Type_Traits_Specialization(float);
Type_Traits_Specialization(double);
Type_Traits_Specialization(long double);

Type_Traits_Specialization(char*);
Type_Traits_Specialization(signed char*);
Type_Traits_Specialization(unsigned char*);
Type_Traits_Specialization(const char*);
Type_Traits_Specialization(const signed char*);
Type_Traits_Specialization(const unsigned char*);



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


// General
template <typename T> struct __Is_integer {
	typedef __false_type _Integral;
};

// Specialization

#define Is_Interger_Specialization(type) template <>\
class __Is_integer<type> {\
public:\
	typedef __true_type _Integral;\
}

Is_Interger_Specialization(bool);
Is_Interger_Specialization(char);
Is_Interger_Specialization(unsigned char);
Is_Interger_Specialization(signed char);
Is_Interger_Specialization(short);
Is_Interger_Specialization(unsigned short);
Is_Interger_Specialization(int);
Is_Interger_Specialization(unsigned int);
Is_Interger_Specialization(long);
Is_Interger_Specialization(unsigned long);

Is_Interger_Specialization(long long);
Is_Interger_Specialization(unsigned long long);


} // namespace ministl

#endif /* __MINI_STL_TYPE_TRAITS_H */

// Done.
