#ifndef REWRITE_HPP_INCLUDED_408436789851406188
#define REWRITE_HPP_INCLUDED_408436789851406188 1

//
// ... Expression header files
//
#include <expression/import.hpp>
#include <expression/app.hpp>
#include <expression/fun.hpp>
#include <expression/var.hpp>
#include <expression/val.hpp>



namespace Expression
{
  namespace Core
  {

    constexpr
    class Rewrite
    {
    public:
      template< typename E, typename I, I Index, typename Rep >
      constexpr auto
      operator ()( const E& expr, const Variable<I,Index> pat, const Rep& rep ) const& {
	return aux( expr, pat, rep);
      }

    private:

      template< typename I, I Index, typename Rep >
      static constexpr auto
      aux( const Variable<I,Index>&, const Variable<I,Index>&, const Rep& rep ){ return rep; }


      template< typename E, typename Pat, typename Rep >
      static constexpr auto
      aux( const E& expr, const Pat&, const Rep& ){ return expr; }



      template< typename I, I Index, typename Body, typename Pat, typename Rep >
      static constexpr auto
      aux( const Abstraction<I,Index,Body>& expr, const Pat& pat, const Rep& rep ){
	return fn( Variable<I,Index>{}, 
		    aux( body( expr ), pat, rep ));
      }

      template< typename I, I Index, typename Body, typename Rep >
      static constexpr auto
      aux( const Abstraction<I,Index,Body>& expr, const Variable<I,Index>&, const Rep& ){
	return expr;
      }

      template< typename F, typename A, typename Pat, typename Rep >
      static constexpr auto
      aux( const Application<F,A>& expr, const Pat& pat, const Rep& rep ){
	return aux( fun( expr ), pat, rep )(
	  aux( arg( expr ), pat, rep ));
      }

      
      
    } rewrite{};


    
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined REWRITE_HPP_INCLUDED_408436789851406188
