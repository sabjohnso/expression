#ifndef VAR_HPP_INCLUDED_774077116977735401
#define VAR_HPP_INCLUDED_774077116977735401 1

//
// ... Expression header files
//
#include <expression/import.hpp>
#include <expression/fwd.hpp>
#include <expression/expr.hpp>
#include <expression/app.hpp>

namespace Expression
{
  namespace Core
  {

    /** A Variable in an expression 
     */
    template< typename T, T Index >
    class Variable : public Expr<Variable<T,Index>>
    {
    public:
     
      using index_type = T;
      static constexpr index_type index = Index;

      
      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, Variable ){
	os << '%' << index;
	return os;
      }
      
    }; // end of class Variable


    template< typename T, T Index1, T Index2 >
    constexpr bool
    operator ==( Variable<T,Index1>, Variable<T,Index2> ){
      return Index1 == Index2;
    }
   

    template< size_t Index >
    constexpr Variable<size_t,Index> var{};
    
  } // end of namespace Core  
} // end of namespace Expression
#endif // !defined VAR_HPP_INCLUDED_774077116977735401

