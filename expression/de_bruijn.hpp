#ifndef DE_BRUIJN_HPP_INCLUDED_373525331548291916
#define DE_BRUIJN_HPP_INCLUDED_373525331548291916 1

//
// ... Expression header files
//
#include <expression/import.hpp>
#include <expression/app.hpp>
#include <expression/fun.hpp>
#include <expression/var.hpp>
#include <expression/val.hpp>
#include <expression/occurs.hpp>
#include <expression/rewrite.hpp>


namespace Expression
{
  namespace Core
  {

    /** Rewrite an expression with De Bruijn indexing 
     */
    constexpr
    class DeBruijn
    {
      
    public:
      
      template< typename E >
      constexpr auto
      operator ()( E&& expr ) const & {
	return exec( bool_constant<has_free_variables(type<decay_t<E>>)>{},
		     forward<E>( expr ));
      }
    private:

      
      template< typename E >
      static constexpr auto
      exec( true_type, E&& expr ){
	return expr;
      }

      template< typename E >
      static constexpr auto
      exec( false_type, E&& expr ){
	return maybe_repeat( aux( forward<E>( expr )));
      }
      
      template< typename E >
      static constexpr auto
      exec( E&& expr ){
	return maybe_repeat( aux( forward<E>( expr )));
      }


      /** Internal data exchange type
       *
       * @details This type hold the modified De Bruijn 
       * indexed expression and indicates the binding depth
       * an necessity to repeat the indexing procedure through
       * template parameter arguments.
       */
      template< typename E, size_t depth, bool repeat >
      class Data
      {
      public:
	using expression_type = E;
	constexpr
	Data( const expression_type& input ) : expr( input ){}
      private:
	expression_type expr;
	
	friend constexpr const expression_type&
	expression( const Data& data ){
	  return data.expr;
	}
      }; // end of class Data
      

      
      
      template< typename T >
      static constexpr auto
      aux( const Value<T>& x ){
	return Data<Value<T>,0,false>( x );
      }

      template< typename T, T Index >
      static constexpr auto
      aux( const Variable<T,Index>& expr ){
	return Data<Variable<T,Index>,0,false>( expr );
      }

      template< typename F, typename A >
      static constexpr auto
      aux( const Application<F,A>& expr ){
	return aux_app( aux( fun( expr )), aux( arg( expr )));
      }

      template< typename F, size_t depth_fun, bool repeat_fun,
		typename A, size_t depth_arg, bool repeat_arg  >
      static constexpr auto
      aux_app( const Data<F,depth_fun,repeat_fun>& data_fun,
	       const Data<A,depth_arg,repeat_arg>& data_arg ){
	return Data<Application<F,A>,max(depth_fun,depth_arg),repeat_fun || repeat_arg >(
	  expression( data_fun )( expression( data_arg )));
      }


      
      template< typename T, T Index, typename Body >
      static constexpr auto
      aux( const Abstraction<T,Index,Body>& expr ){
	return aux_fun( expr, aux( body( expr )));
      }

      template< typename T, T Index, typename Body, typename NewBody, size_t Depth, bool Repeat >
      static constexpr auto
      aux_fun( const Abstraction<T,Index,Body>& expr, const Data<NewBody,Depth,Repeat>& data ){
	return aux_fun_index_check( bool_constant<Index == Depth>{}, expr, data );
      }
      

      template< typename T, T Index, typename Body, size_t Depth, typename NewBody, bool Repeat >
      static constexpr auto
      aux_fun_index_check( true_type, const Abstraction<T,Index,Body>& expr, const Data<NewBody,Depth,Repeat>& data ){
	static_assert( Index == Depth );
	return Data<Abstraction<T,Index,NewBody>,Index+1,Repeat>( fun( Variable<T,Index>{}, expression( data )));
      }

      template< typename T, T Index, typename Body, typename NewBody, size_t Depth, bool Repeat >
      static constexpr auto
      aux_fun_index_check( false_type, const Abstraction<T,Index,Body>& expr, const Data<NewBody,Depth,Repeat>& data ){
	static_assert( Index != Depth );
	return aux_fun_occurs_check(
	  bool_constant< occurs_free( integer<T,Depth>, type<NewBody> )>{},
	  expr, data );
      }

      template< typename T, T Index, typename Body, typename NewBody, size_t Depth, bool Repeat >
      static constexpr auto
      aux_fun_occurs_check( true_type, const Abstraction<T,Index,Body>& expr, const Data<NewBody,Depth,Repeat>& data ){
	return aux_fun( expr, Data<NewBody,Depth+1,true>( expression( data )));
      }

      template< typename T, T Index, typename Body, typename NewBody, size_t Depth, bool Repeat >
      static constexpr auto
      aux_fun_occurs_check( false_type, const Abstraction<T,Index,Body>& expr, const Data<NewBody,Depth,Repeat>& data ){
	return aux_fun2( expr, data, 
			 rewrite(expression( data ),
				 Variable<T,Index>{},
				 Variable<T,Depth>{} ));
      }
      

      template< typename T, T Index, typename OldBody,
		typename Body, size_t Depth, bool Repeat,
		typename NewBody >
      static constexpr auto
      aux_fun2( const Abstraction<T,Index,OldBody>&,
		const Data<Body,Depth,Repeat>&,
		const NewBody& body ){
	return Data<Abstraction<T,Depth,NewBody>,Depth+1,Repeat>(
	  Abstraction<T,Depth,NewBody>( body ));
      }

      template< typename E, size_t Depth >
      static constexpr auto
      maybe_repeat( const Data<E,Depth,true>& data ){
	return exec( expression( data ));
      }

      
      template< typename E, size_t Depth >
      static constexpr auto
      maybe_repeat( const Data<E,Depth,false>& data ){
	return expression( data );
      }
      	
      

      
      
    } de_bruijn{};  // end of class DeBruijn
    
  } // end of namespace Core
} // end of namespace Expression



#endif // !defined DE_BRUIJN_HPP_INCLUDED_373525331548291916
