#ifndef NORMAL_HPP_INCLUDED_1263288072109330184
#define NORMAL_HPP_INCLUDED_1263288072109330184 1

//
// ... Expression header files
//
#include <expression/app.hpp>
#include <expression/val.hpp>
#include <expression/var.hpp>
#include <expression/fun.hpp>


namespace Expression
{
  namespace Core
  {

    
    template< typename T >
    constexpr bool
    eta_normal( T&& ){ return true; }

    template< typename T, T Index, typename F>
    constexpr bool
    eta_normal( Abstraction<T,Index,Application<F,Variable<T,Index>>> ){ return false; }

    template< typename T, T Index, typename Body >
    constexpr bool
    eta_normal( const Abstraction<T,Index,Body>& fun ){ return eta_normal( body( fun )); }

    template< typename F, typename A >
    constexpr bool
    eta_normal( const Application<F,A>& app ){
      return eta_normal( fun( app )) && eta_normal( arg( app )); }




    
    template< typename T >
    constexpr bool
    beta_normal( T&& ){ return true; }

    template< typename T, T Index, typename Body >
    constexpr bool
    beta_normal( const Abstraction<T,Index,Body>& fun ){
      return beta_normal( body( fun ));
    }

    template< typename T, T Index, typename Body, typename  Arg >
    constexpr bool
    beta_normal( Application<Abstraction<T,Index,Body>,Arg> ){ return false; }

    template< typename F, typename A >
    constexpr bool
    beta_normal( const Application<F,A>& app ){
      return beta_normal( fun( app )) && beta_normal( arg( app ));
    }
  
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined NORMAL_HPP_INCLUDED_1263288072109330184
