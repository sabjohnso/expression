#ifndef COND_HPP_INCLUDED_241661204386061756
#define COND_HPP_INCLUDED_241661204386061756 1

//
// ... Expression header files
//
#include <expression/import.hpp>
#include <expression/guard.hpp>



namespace Expression::Core
{

  template< typename ... >
  class Cond_form;

  template< typename T, typename P, typename F >
  class Cond_form<Guarded<T,P>,F>
  {
  public:

    using guarded_expression_type = Guarded<T,P>;
    using fail_expression_type = F;

    template< typename E1, typename E2 >
    Cond_form( E1&& e1, E2&& e2 )
      : gexpr( forward<E1>( e1 ))
      , fexpr( forward<E2>( e2 ))
    {}
          
  private:
    guarded_expression_type gexpr;
    fail_expression_type fexpr;
    
    
  }; // end of class Cond_form


  template< typename G, typename F >
  constexpr auto
  cond( G&& gexpr, F fexpr ){
    return Cond_form<decay_t<G>, decay_t<F>>(
      forward<G>( gexpr ),
      forward<F>( fexpr ));
    
  }

  template< typename G1, typename G2, typename E, typename ... Es >
  constexpr auto
  cond( G1&& g1, G2&& g2, E&& e, Es&& ... es ){
    return cond(
      forward<G1>( g1 ),
      cond( forward<G2>( g2 ),
	    forward<E>( e ),
	    forward<Es>( es )... ));
  }
} // end of namespace Expression::Core

#endif // !defined COND_HPP_INCLUDED_241661204386061756
