#ifndef OCCURS_HPP_INCLUDED_1601795310995521658
#define OCCURS_HPP_INCLUDED_1601795310995521658 1

//
// ... Expression header files
//
#include <expression/app.hpp>
#include <expression/fun.hpp>
#include <expression/var.hpp>
#include <expression/val.hpp>


namespace Expression
{
  namespace Core
  {

    template< typename T, T Index >
    constexpr bool
    occurs( Variable<T,Index>, Variable<T,Index> ){ return true; }

    template< typename T, T Index, T OtherIndex >
    constexpr bool
    occurs( Variable<T,Index>, Variable<T,OtherIndex> ){ return false; }

    template< typename T, T Index, typename U >
    constexpr bool
    occurs( Variable<T,Index>, Value<U> ){
      return false;
    }

    template< typename T, T Index, typename Body >
    constexpr bool
    occurs( Variable<T,Index>, const Abstraction<T,Index,Body>& fun ){
      return occurs( Variable<T,Index>{}, body( fun ));
    }

    template< typename T, T Index, typename F, typename A >
    constexpr bool
    occurs( Variable<T,Index>, const Application<F,A>& app ){
      return occurs( Variable<T,Index>{}, fun( app )) ||
	occurs( Variable<T,Index>{}, arg( app ));
    }




    


    template< typename T, T Index >
    constexpr bool
    occurs_bound( Variable<T,Index>, Variable<T,Index> ){ return false; }

    template< typename T, T Index, T OtherIndex >
    constexpr bool
    occurs_bound( Variable<T,Index>, Variable<T,OtherIndex> ){ return false; }

    template< typename T, T Index, typename U >
    constexpr bool
    occurs_bound( Variable<T,Index>, Value<U> ){
      return false;
    }

    template< typename T, T Index, typename Body >
    constexpr bool
    occurs_bound( Variable<T,Index>, const Abstraction<T,Index,Body>& fun ){
      return occurs( Variable<T,Index>{}, body( fun ));
    }
    
    template< typename T, T Index, T OtherIndex, typename Body >
    constexpr bool
    occurs_bound( Variable<T,Index>, const Abstraction<T,OtherIndex,Body>& fun ){
      return occurs_bound( Variable<T,Index>{}, body( fun ));
    }

    template< typename T, T Index, typename F, typename A >
    constexpr bool
    occurs_bound( Variable<T,Index>, const Application<F,A>& app ){
      return occurs_bound( Variable<T,Index>{}, fun( app )) ||
	occurs_bound( Variable<T,Index>{}, arg( app ));
    }








    template< typename T, T Index >
    constexpr bool
    occurs_free( Variable<T,Index>, Variable<T,Index> ){ return true; }

    template< typename T, T Index, T OtherIndex >
    constexpr bool
    occurs_free( Variable<T,Index>, Variable<T,OtherIndex> ){ return false; }

    template< typename T, T Index, typename U >
    constexpr bool
    occurs_free( Variable<T,Index>, Value<U> ){ return false; }

    template< typename T, T Index, typename Body >
    constexpr bool
    occurs_free( Variable<T,Index>, const Abstraction<T,Index,Body>& fun ){ return false; }
    
    template< typename T, T Index, T OtherIndex, typename Body >
    constexpr bool
    occurs_free( Variable<T,Index>, const Abstraction<T,OtherIndex,Body>& fun ){
      return occurs_free( Variable<T,Index>{}, body( fun ));
    }

    
    template< typename T, T Index, typename F, typename A >
    constexpr bool
    occurs_free( Variable<T,Index>, const Application<F,A>& app ){
      return occurs_free( Variable<T,Index>{}, fun( app )) ||
	occurs_free( Variable<T,Index>{}, arg( app ));
    }
    


    
  } // end of namespace Core
} // end of namespace Expression


#endif // !defined OCCURS_HPP_INCLUDED_1601795310995521658
