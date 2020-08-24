#ifndef SIMPLIFY_HPP_INCLUDED_1263315792589695035
#define SIMPLIFY_HPP_INCLUDED_1263315792589695035 1

//
// ... Expression header files
//
#include <expression/de_bruijn.hpp>
#include <expression/normal.hpp>
#include <expression/rewrite.hpp>

namespace Expression
{
  namespace Core
  {

    constexpr class Beta_reduce
    {
    public:
      template<typename E>
      constexpr auto
      operator()(const E& expr) const
      {
        return aux(expr);
      }

    private:
      /** Return the expression unaltered, as the default. */
      template<typename E>
      static constexpr auto
      aux(const E& expr)
      {
        return expr;
      }

      /** Rewrite application of abstraction. */
      template<typename I, I Index, typename Body, typename A>
      static constexpr auto
      aux(const Application<Abstraction<I, Index, Body>, A>& expr)
      {
        return rewrite(
          body(fun(expr)), Variable<I, Index>{}, arg(expr));
      }

      /** Perform beta reduction on the applicand and argument */
      template<typename F, typename A>
      static constexpr auto
      aux(const Application<F, A>& expr)
      {
        return aux(fun(expr))(aux(arg(expr)));
      }

    } beta_reduce{}; // end of class Beta_reduce

    constexpr class Eta_reduce
    {
    public:
      template<typename E>
      constexpr auto
      operator()(const E& expr) const&
      {
        return aux(expr);
      }

    private:
      template<typename E>
      static constexpr auto
      aux(const E& expr)
      {
        return expr;
      }

      template<typename I, I Index, typename F>
      static constexpr auto
      aux(
        const Abstraction<I, Index, Application<F, Variable<I, Index>>>&
          expr)
      {
        return aux(fun(body(expr)));
      }

      template<typename I, I Index, typename Body>
      static constexpr auto
      aux(const Abstraction<I, Index, Body>& expr)
      {
        return fun(Variable<I, Index>{}, aux(body(expr)));
      }

      template<typename F, typename A>
      static constexpr auto
      aux(const Application<F, A>& expr)
      {
        return aux(fun(expr))(aux(arg(expr)));
      }

    } eta_reduce{}; // end of class Eta_reduce

    constexpr class Simplify
    {
    public:
      template<typename E>
      constexpr auto
      operator()(const E& expr)
      {
        return exec(expr);
      }

    private:
    } simplify{};

  } // end of namespace Core
} // end of namespace Expression

#endif // !defined SIMPLIFY_HPP_INCLUDED_1263315792589695035
