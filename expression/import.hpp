#ifndef IMPORT_HPP_INCLUDED_1976701070124649363
#define IMPORT_HPP_INCLUDED_1976701070124649363 1

//
// ... Standard header files
//
#include <cstddef>
#include <utility>
#include <type_traits>
#include <algorithm>

//
// ... Type Utility header files
//
#include <type_utility/type_utility.hpp>



namespace Expression
{
  namespace Core
  {
    using std::size_t;

    using std::move;
    using std::forward;

    using std::bool_constant;
    using std::true_type;
    using std::false_type;
    using std::decay_t;

    using std::max;


    using TypeUtility::Type;
    using TypeUtility::type;
    using TypeUtility::Integer;
    using TypeUtility::integer;
    using TypeUtility::Integer_set;
    using TypeUtility::integer_set;

    
    
    
  } // end of namespace Core
} // end of namespace Expression


#endif // !defined IMPORT_HPP_INCLUDED_1976701070124649363
