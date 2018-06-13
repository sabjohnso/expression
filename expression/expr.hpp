#ifndef EXPR_HPP_INCLUDED_678766455533177280
#define EXPR_HPP_INCLUDED_678766455533177280 1

//
// ... Expression header files
//
#include <expression/fwd.hpp>



namespace Expression
{
  namespace Core
  {
    
    /** A CRTP base class for  */
    template< typename T >
    class Expr{
    public:

      constexpr operator const T& () const& { return static_cast<const T&>( *this ); }
      constexpr operator T&& () && { return static_cast<T&&>( *this ); }

      /** Function call operator
       */
      template< typename U >
      constexpr auto
      operator ()( U&& x ) const & {
	return app( static_cast<const T&>( *this ), forward<U>( x ));
      }

      /** Function call operator
       */
      template< typename U >
      constexpr auto
      operator ()( U&& x ) && { return app( static_cast<T&&>( *this ), forward<U>( x )); }



      template< typename U, typename V, typename ... Ws >
      constexpr auto
      operator ()( U&& x, V&& y, Ws&& ... zs ) const & {
	return (*this)( forward<U>( x ))(
	  forward<V>( y ),
	  forward<Ws>( zs ) ... );
      }

      template< typename U, typename V, typename ... Ws >
      constexpr auto
      operator ()( U&& x, V&& y, Ws&& ... zs ) && {
	return (*this)( forward<U>( x ))(
	  forward<V>( y ),
	  forward<Ws>( zs ) ... );
      }


      template< typename U >
      friend constexpr auto
      operator +( const Expr& x, const Expr<U>& y ){
	return val( add )( x, y );
      }

      template< typename U >
      friend constexpr auto
      operator -( const Expr& x, const Expr<U>& y ){
	return val( add )( x, y );
      }

      template< typename U >
      friend constexpr auto
      operator *( const Expr& x, const Expr<U>& y ){
	return val( multiply )( x, y );
      }

      template< typename U >
      friend constexpr auto
      operator /( const Expr& x, const Expr<U>& y ){
	return val( divide )( x, y );
      }

      
      
    }; // end of class Expression
	


    
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined EXPR_HPP_INCLUDED_678766455533177280
