#ifndef VALUE_HPP_INCLUDED_588284922219344181
#define VALUE_HPP_INCLUDED_588284922219344181 1

//
// ... Expression
//
#include <expression/import.hpp>
#include <expression/expr.hpp>
#include <expression/app.hpp>


namespace Expression
{
  namespace Core
  {

    template< typename T >
    class Value : public Expr<Value<T>>
    {
    public:
      using value_type = T;

      template< typename U >
      constexpr
      Value( U&& input ) : value( forward<U>( input )) {}



      constexpr
      const value_type&
      operator *() const & { return value; }


      constexpr
      value_type&&
      operator *() && { return value; }

      

    private:

      value_type value;

      constexpr
      operator const value_type& () const & { return value; }

      constexpr
      operator value_type&& () && { return move( value ); }
      
      

      //
      // ... friends
      //

      friend constexpr bool
      operator ==( const Value& x, const Value& y ){
	return x.value == y.value;
      }

      template< typename U >
      friend constexpr bool
      operator ==( const Value& x, const Value<U>& y ){
	return false;
      }

      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, const Value& x ){
	os << x.value;
	return os;
      }
      
      
    }; // end of class Value


    template< typename T >
    constexpr auto
    val( T&& x ){
      return Value<decay_t<T>>( forward<T>( x ));
    }
    
    
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined VALUE_HPP_INCLUDED_588284922219344181
