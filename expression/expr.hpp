#ifndef EXPR_HPP_INCLUDED_678766455533177280
#define EXPR_HPP_INCLUDED_678766455533177280 1

//
// ... Expression header files
//
#include <expression/fwd.hpp>
#include <expression/import.hpp>

namespace Expression
{
  namespace Core
  {

    /** A CRTP base class for  */
    template<typename T>
    class Expr
    {
    public:
      constexpr operator const T&() const&
      {
        return static_cast<const T&>(*this);
      }
      constexpr
      operator T&&() &&
      {
        return static_cast<T&&>(*this);
      }

      /** Function call operator
       */
      template<typename U>
      constexpr auto
      operator()(U&& x) const&
      {
        return app(static_cast<const T&>(*this), forward<U>(x));
      }

      /** Function call operator
       */
      template<typename U>
      constexpr auto
      operator()(U&& x) &&
      {
        return app(static_cast<T&&>(*this), forward<U>(x));
      }

      template<typename U, typename V, typename... Ws>
      constexpr auto
      operator()(U&& x, V&& y, Ws&&... zs) const&
      {
        return (*this)(forward<U>(x))(
          forward<V>(y), forward<Ws>(zs)...);
      }

      template<typename U, typename V, typename... Ws>
      constexpr auto
      operator()(U&& x, V&& y, Ws&&... zs) &&
      {
        return (*this)(forward<U>(x))(
          forward<V>(y), forward<Ws>(zs)...);
      }

      template<typename U>
      friend constexpr auto
      operator+(const Expr& x, const Expr<U>& y)
      {
        return val(add)(
          static_cast<const T&>(x), static_cast<const U&>(y));
      }

      template<typename U>
      friend constexpr auto
      operator-(const Expr& x, const Expr<U>& y)
      {
        return val(subtract)(
          static_cast<const T&>(x), static_cast<const U&>(y));
      }

      template<typename U>
      friend constexpr auto
      operator*(const Expr& x, const Expr<U>& y)
      {
        return val(multiply)(
          static_cast<const T&>(x), static_cast<const U&>(y));
      }

      template<typename U>
      friend constexpr auto
      operator/(const Expr& x, const Expr<U>& y)
      {
        return val(divide)(
          static_cast<const T&>(x), static_cast<const U&>(y));
      }

      template<typename U>
      friend constexpr auto
      operator|(const Expr& x, const Expr<U>& y)
      {
        return Alternative<T, Alternative<U, nullptr_t>>(
          static_cast<const T&>(x), static_cast<const U&>(y));
      }

      // template< typename U>
      // friend constexpr auto
      // operator >> ( const Expr& x, const Expr<U>& y ){
      // 	return Guarded<T,U>(
      // 	  static_cast<const T&>( x ),
      // 	  static_cast<const U&>( y ));

      // }

    }; // end of class Expression

  } // end of namespace Core
} // end of namespace Expression

namespace std
{
  template<typename U>
  string
  to_string(const Expression::Core::Expr<U>& e)
  {
    stringstream ss;
    ss << e;
    return ss.str();
  }
} // end of namespace std

#endif // !defined EXPR_HPP_INCLUDED_678766455533177280
