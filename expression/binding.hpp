#ifndef BINDING_HPP_INCLUDED_446477296149350721
#define BINDING_HPP_INCLUDED_446477296149350721 1

//
// ... Expression header files
//
#include <expression/import.hpp>
#include <expression/fwd.hpp>
#include <expression/expr.hpp>



namespace Expression
{
  namespace Core
  {

    template< typename I, I Index, typename E >
    class Binding
    {
    public:
      using index_type = I;
      static constexpr index_type index = Index;
      using expression_type = E;

      template< typename U >
      constexpr
      Binding( U&& input )
	: expr( forward<U>( input ))
      {}

     
      
    private:

      constexpr
      operator const expression_type& () const & {
	return expr;
      }

      constexpr
      operator expression_type&& () && {
	return move( expr );
      }
      
      expression_type expr;

      template< typename Stream >
      friend Stream&
      operator<<( Stream& os, const Binding& binding ){
	os << Variable<I,Index>() << " = " << binding.expr;
	return os;
      }


      constexpr
      friend auto
      expr( Binding&& binding ){
	return move( binding.expr );
      }

      constexpr
      friend auto
      expr( const Binding& binding ){
	return binding.expr;
      }
    }; // end of class Binding


    
    
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined BINDING_HPP_INCLUDED_446477296149350721
