#ifndef FWD_HPP_INCLUDED_2043871476434126497
#define FWD_HPP_INCLUDED_2043871476434126497 1

//
// ... Expression header files
//
#include <expression/import.hpp>


namespace Expression
{
  namespace Core
  {

    template< typename F, typename T >
    class Application;

    template< typename F, typename T, typename R = Application<decay_t<F>, decay_t<T>>>
    constexpr R
    app( F&& f, T&& x );

    template< typename I, I Index >
    class Variable;


    template< typename T >
    class Value;

    template< typename T, typename R = Value<decay_t<T>>>
    constexpr R
    val( T&& x );
    

    
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined FWD_HPP_INCLUDED_2043871476434126497
