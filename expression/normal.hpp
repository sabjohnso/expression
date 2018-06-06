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

    /** A class providing a predicate for eta-normality */
    constexpr
    class Eta_normal
    {
    public:


      /** Return true for eta normal expressions */
      template< typename E >
      constexpr bool
      operator ()( const E& ) const & {
	return aux( type<decay_t<E>> );
      }

      /** Return true for type proxies to eta normal expressions, otherwise false. */
      template< typename E >
      constexpr bool
      operator ()( Type<E> ) const & {
	return aux( type<E> );
      }

    private:


      /** Return true, as the default */
      template< typename E >
      static constexpr bool
      aux( Type<E>  ){ return true; }

      /** Return false for abstractions with the application as the body and the bound
       *  variable as its argument.
       */
      template< typename I, I Index, typename F >
      static constexpr bool
      aux( Type<Abstraction<I,Index,Application<F,Variable<I,Index>>>> ){ return false; }

      /** Otherwise, an abstraction is eta normal if its body is. */
      template< typename I, I Index, typename Body >
      static constexpr bool
      aux( Type<Abstraction<I,Index,Body>> ){ return aux( type<Body> ); } 

      /** Application is eta normal of the applicand and argument are eta normal */
      template< typename F, typename A >
      static constexpr bool
      aux( Type<Application<F,A>> ){
	return aux( type<F> ) && aux( type<A> );
      }
      
    } eta_normal{};



    /** A class providing a predicate for beta normal form of an expression 
     *
     * @details This class implements a function call operator that returns
     * true for an expression that is in beta normal form and false otherwise.
     * The beta-normality of an expression is determined entirely by its type,
     * this class can operate on expressions or type proxies to expressions.
     */
    constexpr
    class Beta_normal
    {
    public:

      /** Return the result of beta-normality for an expression */
      template< typename E >
      constexpr bool
      operator ()( const E& expr ) const & { return aux( type<decay_t<E>> ); }

      /** Return the result of beta-normality for an expression type */
      template< typename E >
      constexpr bool
      operator ()( Type<E> ) const & { return aux( type<E> ); }

      
    private:

      /** As the default, return true */
      template< typename E >
      static constexpr bool
      aux( Type<E> ){ return true; }

      /** Abstraction is beta normal if its body is beta normal*/
      template< typename I, I Index, typename Body >
      static constexpr bool
      aux( Type<Abstraction<I,Index,Body>> ){ return aux( type<Body> ); }

      /** Application is not beta normal when the applicand is an abstraction */
      template< typename I, I Index, typename Body, typename Arg >
      static constexpr bool
      aux( Type<Application<Abstraction<I,Index,Body>,Arg>> ){ return false; }

      /** Application when the applicand is not an abstraction is normal when the 
       * applicand and argument are beta normal */
      template< typename F, typename A >
      static constexpr bool
      aux( Type<Application<F,A>> ){
	return aux( type<A> ) && aux( type<A> );
      }
      
    } beta_normal{};


  
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined NORMAL_HPP_INCLUDED_1263288072109330184
