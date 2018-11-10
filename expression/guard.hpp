#ifndef GUARD_HPP_INCLUDED_283643148324239353
#define GUARD_HPP_INCLUDED_283643148324239353 1

//
// ... Expression header files
//
#include <expression/import.hpp>


namespace Expression::Core
{

  template< typename T, typename E >
  class Guarded
  {
  public:
    using test_type = T;
    using expression_type = E;

    template< typename U, typename V >
    constexpr
    Guarded( U&& t, V&& e )
      : test( forward<U>( t ))
      , expr( forward<V>( e )){}

  private:
    test_type test;
    expression_type expr;

    template< typename Stream >
    friend Stream&
    operator <<( Stream& os, Guarded gexpr ){
      os << gexpr.test << " >> " << gexpr.expr;
      return os;
    }
  };


  
} // end of namespace Expression::Core


namespace std
{
  template< typename T, typename E >
  string
  to_string( const Expression::Core::Guarded<T,E>& gexpr ){
    stringstream ss;
    ss << gexpr;
    return ss.str();
  }
  
} // end of namespace std

#endif // !defined GUARD_HPP_INCLUDED_283643148324239353
