#ifndef ALTERNATIVE_HPP_INCLUDED_2281704363430484964
#define ALTERNATIVE_HPP_INCLUDED_2281704363430484964 1

//
// ... Expression header files
//
#include <expression/import.hpp>
#include <expression/expr.hpp>



namespace Expression
{
  namespace Core
  {


    /**
     * @brief Alternative expressions
     *
     * @details This class represents a list of alternative
     * expressions terminated with nullptr
     */
    template< typename First, typename Second >
    class Alternative : pair<First, Second> {
    public:
      using first_type = First;
      using second_type = Second;
      using base = pair<first_type,second_type>;

      using base::base;
      
    private:

      
      template< typename Stream >
      friend Stream& 
      operator <<( Stream& os, const Alternative& alts ){
	os << alts.first << "|" << alts.second;
	return os;
      }


      
      template< typename T > 
      friend constexpr auto
      operator |( const Alternative& alts, const Expr<T>& expr ){
	using tail = decltype( alts.second | expr );
	return Alternative<first_type,tail>(
	  alts.first,
	  alts.second | expr );
      }


      template< typename T >
      friend constexpr auto
      operator |( const Expr<T>& expr, const Alternative& alts ){
	return Alternative<T,Alternative>( expr, alts );
      }


      template< typename T1, typename T2 >
      friend constexpr auto
      operator |( const Alternative& alts, const Alternative<T1,T2>& more_alts ){
	return alts.first | ( alts.second | more_alts );
	

      }



      friend constexpr bool
      operator ==( const Alternative& x, const Alternative& y ){
	return (x.first == y.first) && (x.second == y.second);
      }

      template<  typename T1, typename T2 >
      friend constexpr bool
      operator ==( const Alternative& , const Alternative<T1,T2>& ){
	return false;
      }

      
      template<  typename T1, typename T2 >
      friend constexpr bool
      operator ==( const Alternative<T1,T2>&, const Alternative& ){
	return false;
      }


      template< typename U >
      friend constexpr bool
      operator !=( const Alternative& x, const U& y ){
	return !( x == y );
      }

      



      
    }; // end of class Alternative



    


    template< typename Only >
    class Alternative<Only,nullptr_t> : pair<Only,nullptr_t> {
    public:
      
      using only_type = Only;
      using base = pair<only_type,nullptr_t>;

      constexpr
      Alternative( const Alternative& input ) : base( input  ){}

      constexpr
      Alternative( Alternative&& input ) : base( move( input )){}

      constexpr
      Alternative( const only_type& input ) : base( input, nullptr ){}
      
      constexpr
      Alternative( only_type&& input ) : base( move( input ), nullptr ){}
      
    private:


      template< typename Stream >
      friend Stream& 
      operator <<( Stream& os, const Alternative&  alt ){
	os << alt.first;
	return os;
      }


      
      template< typename T > 
      friend constexpr auto
      operator |( const Alternative& alts, const Expr<T>& expr ){
	using tail_type = Alternative<T,nullptr_t>;
	return Alternative<only_type,tail_type>( alts.first, tail_type( expr ));
      }


      
      template< typename T >
      friend constexpr auto
      operator |( const Expr<T>& expr, const Alternative& alts ){
	return Alternative<T,Alternative>( expr, alts );
      }

      template< typename T1, typename T2 >
      friend constexpr auto
      operator |( const Alternative& alt, const Alternative<T1,T2>& alts ){
	return alt.first | alts ;
      }



      friend constexpr bool
      operator ==( const Alternative& x, const Alternative& y ){
	return x.first == y.first;
      }

      friend constexpr bool
      operator ==(  nullptr_t, const Alternative& ){ return false; }

      template< typename T1, typename T2 >
      friend constexpr bool
      operator ==( const Alternative<T1,T2>& y, const Alternative& x ){ return false; }


      template< typename U >
      friend constexpr bool
      operator !=( const Alternative& x, const U& y ){
	return !( x == y );
      }
      
    }; // end of class Alternative


    template< typename T >
    constexpr auto
    alt( const Expr<T>& expr ){ return Alternative<T,nullptr_t>( expr ); }

    template< typename T, typename T1, typename T2 >
    constexpr auto
    alt( const Expr<T>& expr, const Alternative<T1,T2>& alts ){
      return Alternative<T,Alternative<T1,T2>>( expr, alts );
    }
    
      

    template< typename T1, typename T2, typename ... Ts >
    constexpr auto
    alt( const Expr<T1>& x, const Expr<T2>& y, const Expr<Ts>& ... zs ){
      return alt( x, alt( y, zs ... ));
    }




    
    
    
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined ALTERNATIVE_HPP_INCLUDED_2281704363430484964
