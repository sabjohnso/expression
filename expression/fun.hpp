#ifndef FUN_HPP_INCLUDED_1354189082437924042
#define FUN_HPP_INCLUDED_1354189082437924042 1
//
// ... Expression header files
//
#include <expression/app.hpp>
#include <expression/expr.hpp>
#include <expression/import.hpp>
#include <expression/var.hpp>

namespace Expression
{
  namespace Core
  {

    /** Function definition
     */
    template<typename T, T Index, typename Body>
    class Abstraction : public Expr<Abstraction<T, Index, Body>>
    {
    public:
      using index_type = T;
      static constexpr index_type index = Index;
      using body_type = Body;

      constexpr Abstraction(const body_type& expr)
        : body(expr)
      {}

    private:
      body_type body;

      template<typename Stream>
      friend Stream&
      operator<<(Stream& os, const Abstraction& fun)
      {
        os << '$' << index << ':' << fun.body;
        return os;
      }

      friend constexpr const body_type&
      body(const Abstraction& fun)
      {
        return fun.body;
      }

      friend constexpr bool
      operator==(const Abstraction& f, const Abstraction& g)
      {
        return f.body == g.body;
      }

      template<typename U>
      friend constexpr bool
      operator==(const Abstraction& f, const U& g)
      {
        return false;
      }

      template<typename U>
      friend constexpr bool
      operator!=(const Abstraction& f, const U& g)
      {
        return !(f == g);
      }

    }; // end of class Abstraction

    template<typename T, T Index, typename Body>
    constexpr auto
    fn(Variable<T, Index>, Body&& body)
    {
      return Abstraction<T, Index, decay_t<Body>>(forward<Body>(body));
    }

    template<
      typename T,
      T Index,
      typename U,
      typename V,
      typename... Ws>
    constexpr auto
    fn(Variable<T, Index>, const U& x, const V& y, const Ws&... zs)
    {
      return fn(Variable<T, Index>{}, fn(x, y, zs...));
    }

    template<typename Stream, typename I, I Index, typename Body>
    Stream&
    operator<<(Stream& os, Type<Abstraction<I, Index, Body>>)
    {
      os << "Expression::Core::Abstraction<" << type<I> << ',' << Index
         << ',' << type<Body> << '>';
      return os;
    }

  } // end of namespace Core
} // end of namespace Expression

#endif // !defined FUN_HPP_INCLUDED_1354189082437924042
