#ifndef LET_HPP_INCLUDED_1149024591623518265
#define LET_HPP_INCLUDED_1149024591623518265 1

//
// ... Expression header files
//
#include <expression/import.hpp>
#include <expression/fwd.hpp>
#include <expression/binding.hpp>




namespace Expression
{
  namespace Core
  {

    template< typename ... >
    class Let_form;
    

    template< typename I, I Index, typename E >
    class Let_form<Binding<I,Index,E>>{
    public:
      using index_type = I;
      static constexpr index_type index = Index;
      using expression_type = E;
      using binding_type = Binding<index_type,index,expression_type>;

      template< typename U >
      constexpr
      Let_form( U&& input ) : binding( forward<U>( input )){}

      template< typename Body >
      constexpr auto 
      operator,( Body&& body ) && {
	return fn( Variable<I,Index>{},
		   move( body ))( expr( move( binding )));
      }
      

    private:
      
      constexpr 
      operator binding_type&& () && { return move( binding ); }
      
      constexpr 
      operator binding_type const & () const & { return move( binding ); }

      binding_type binding;
    };


    template< 
      typename I, I Index0,  I Index1,
      typename  E0, typename E1,
      typename ... Bindings 
      >
    class Let_form<
      Binding<I,Index0,E0>,
      Binding<I,Index1,E1>,
      Bindings ...>
      : tuple<Binding<I,Index0,E0>,
	      Binding<I,Index1,E1>,
	      Bindings ... >
    {
    public:

      using base =  tuple<Binding<I,Index0,E0>,
			  Binding<I,Index1,E1>,
			  Bindings ... >;

      
      template< typename T, typename U, typename ... Vs >
      constexpr
      Let_form( T&& x, U&& y, Vs&& ... zs )
	: base( forward<T>( x ), forward<U>( y ), forward<Vs>( zs ) ...)
      {}

      // template< typename T >
      // constexpr auto
      // operator,( Expr<T>&& expr ) && {
      // 	return fn( Variable<I,Index0>{},
      // 		   (inner_binding( generate_indices<E0,E1,Bindings ...>()), move( expr )))(
      // 		     expr( move( get<0>( *this ))));
      // }

      template< typename T >
      constexpr auto
      operator,( const Expr<T>& e ) const& {
	return fn( Variable<I,Index0>{},
		   (inner_binding( generate_indices<E0,E1,Bindings ...>()), e ))(
		     expr( get<0>( *this )));
      }
      
    private:

      template< size_t index, size_t ... indices >
      constexpr auto
      inner_binding( index_sequence<index,indices ...> ) && {
	return Let_form<Binding<I,Index1,E1>, Bindings ... >(
	  move( get<indices>( *this )) ... );
      }

      template< size_t index, size_t ... indices >
      constexpr auto
      inner_binding(index_sequence<index,indices ...>) const & {
	return Let_form<Binding<I,Index1,E1>, Bindings ... >(
	  get<indices>( *this ) ... );
      }
    }; // end of class Let_form

    
    template< typename I, I Index, typename E, typename ... Bindings >
    constexpr auto
    let( Binding<I,Index,E>&& binding, Bindings&& ... bindings){
      return Let_form<Binding<I,Index,E>,Bindings ...>(
	move( binding ), move( bindings ) ... );
    }

    template< typename I, I Index, typename E, typename ... Bindings >
    constexpr auto
    let( const Binding<I,Index,E>& binding, const Bindings& ... bindings){
      return Let_form<Binding<I,Index,E>,Bindings ...>( binding, bindings ... );
    }
    
    
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined LET_HPP_INCLUDED_1149024591623518265
