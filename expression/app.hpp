#ifndef APP_HPP_INCLUDED_260197004374282831
#define APP_HPP_INCLUDED_260197004374282831 1

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

    /** Function appliation 
     */
    template< typename F, typename T >
    class Application : public Expr<Application<F,T>>
    {
    public:
      
      using function_type = F;
      using argument_type = T;

      template< typename G, typename U >
      constexpr
      Application( G&& g, U&& y )
	: fun( forward<G>( g ))
	, arg( forward<U>( y ))
      {}
      
    private:

      function_type fun;
      argument_type arg;


      //
      // ... friends
      //


      template< typename Stream >
      friend Stream&
      operator <<( Stream& os, const Application& app ){
	os << '(' << app.fun << ' ' << app.arg << ')';
	return os;
      }

      friend constexpr bool
      operator ==( const Application& x,  const Application& y ){
	return (x.fun == y.fun) && (x.arg == y.arg);
      }

      friend constexpr function_type
      fun( const Application& app ){
	return app.fun;
      }

      friend constexpr argument_type
      arg( const Application& app ){
	return app.arg;
      }
      
    }; // Application
    

    template< typename F, typename T,  typename R = Application<decay_t<F>, decay_t<T>>>
    constexpr R
    app( F&& f, T&& x ){
      return R( forward<F>( f ), forward<T>( x ));
    }


    template< typename Stream, typename F, typename T >
    Stream&
    operator <<( Stream& os, Type<Application<F,T>> ){
      os << "Expression::Core::Application<" << type<F> << ',' << type<T> << '>';
      return os;
    }

  } // end of namespace Core
} // end of namespace Expression

#endif // !defined APP_HPP_INCLUDED_260197004374282831
