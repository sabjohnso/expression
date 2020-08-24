#ifndef COMPILE_HPP_INCLUDED_1070274173433093908
#define COMPILE_HPP_INCLUDED_1070274173433093908 1

//
// ... Expression header files
//
#include <expression/expr.hpp>
#include <expression/var.hpp>
#include <expression/val.hpp>
#include <expression/app.hpp>
#include <expression/fun.hpp>


namespace Expression::Core
{

    template< typename T >
    constexpr auto
    expr_cast( const T& expr ){
      return static_cast<const Expr<T>&>( expr );
    }

    template< typename T >
    constexpr auto
    expr_cast( const Expr<T>& expr ){
      return expr;
    }

    template< typename I, I Index >
    constexpr auto
    compile( const Variable<I,Index>&){
      return selection( identity, index_sequence<size_t( Index )>());
    }

    template< typename F, typename T, typename U >
    constexpr auto
    compile( const Application<Application<Value<F>,T>,U>& expr ){
      return compose( fun( fun( expr )).get(),
		      fanout( compile( arg( fun( expr ))),
			      compile( arg( expr ))));
    }

    template< typename I, I Index, typename Body >
    constexpr auto
    compile( const Abstraction<I,Index,Body>& expr ){
      return compile( body( expr ));
    }



    template< typename I, I Index, typename Body >
    constexpr auto
    compile_function( const Abstraction<I,Index,Body>& expr ){
      static_assert( is_de_bruijn( type<Abstraction<I,Index,Body>> ));
      return curry<Index+1>( compile( de_bruijn_invert( expr )));
    }
} // end of namespace Expression::Core

#endif // !defined COMPILE_HPP_INCLUDED_1070274173433093908
