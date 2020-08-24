#ifndef VAR_HPP_INCLUDED_774077116977735401
#define VAR_HPP_INCLUDED_774077116977735401 1

//
// ... Expression header files
//
#include <expression/app.hpp>
#include <expression/binding.hpp>
#include <expression/expr.hpp>
#include <expression/fwd.hpp>
#include <expression/import.hpp>

namespace Expression
{
  namespace Core
  {

    /** A Variable in an expression
     */
    template<typename T, T Index>
    class Variable : public Expr<Variable<T, Index>>
    {
    public:
      using index_type = T;
      static constexpr index_type index = Index;

      template<typename E>
      constexpr Binding<T, Index, E>
      operator=(const Expr<E>& expr) const&
      {
        return Binding<T, Index, E>(expr);
      }

      template<typename Stream>
      friend Stream&
      operator<<(Stream& os, Variable<T, Index> const&)
      {
        os << "%" << Index;
        return os;
      }

      friend ostream&
      operator<<(ostream& os, Variable<T, Index> const&)
      {
        os << "%" << Index;
        return os;
      }

    }; // end of class Variable

    template<typename T, T Index1, T Index2>
    constexpr bool operator==(Variable<T, Index1>, Variable<T, Index2>)
    {
      return Index1 == Index2;
    }

    template<size_t Index>
    constexpr Variable<size_t, Index> var{};

    template<typename Stream, typename T, T Index>
    Stream&
    operator<<(Stream& os, Type<Variable<T, Index>> const&)
    {
      os << "Expression::Core::Variable<" << type<T> << "," << Index
         << ">";
      return os;
    }

    template<typename T, T Index>
    ostream&
    operator<<(ostream& os, Type<Variable<T, Index>> const&)
    {
      os << "Expression::Core::Variable<" << type<T> << "," << Index
         << ">";
      return os;
    }

  } // end of namespace Core
} // end of namespace Expression
#endif // !defined VAR_HPP_INCLUDED_774077116977735401
