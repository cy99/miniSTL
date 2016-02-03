/* 
 * Copyrigth (c) 2016 by AT_ 
 * Re-implementation of mini STL
 * For skilled STL and C++
 */

#ifndef __MINI_STL_MEMORY_H
#define __MINI_STL_MEMORY_H		// Done.

#include "mini_construct.h"
#include "mini_uninitialized.h"
 
namespace ministl {

#if 0
#include <memory>
using std::uninitialized_fill_n;
using std::uninitialized_copy;
#endif

#if 0
/* use the <memory> for the time being */

// set the value in n position and return the end position
iterator uninitialized_fill_n(iterator start, size_type n, value_type val) {

}

// copy the segment between start and finish to the begin and return the end position
iterator uninitialized_copy(iterator start, iterator finish, iterator begin);
#endif

}



#endif /* __MINI_STL_MEMORY_H */