#ifndef VALUE_HPP_INCLUDED_588284922219344181
#define VALUE_HPP_INCLUDED_588284922219344181 1

//
// ... Expression
//
#include <expression/app.hpp>
#include <expression/expr.hpp>
#include <expression/fwd.hpp>
#include <expression/import.hpp>

namespace Expression
{
  namespace Core
  {

    template<typename T>
    class Value : public Expr<Value<T>>
    {
    public:
      using value_type = T;

      template<typename U>
      constexpr Value(U&& input)
        : value(forward<U>(input))
      {}

      constexpr value_type
      get() const&
      {
        return value;
      }

      constexpr const value_type&
      operator*() const&
      {
        return value;
      }

      constexpr value_type&&
      operator*() &&
      {
        return value;
      }

    private:
      value_type value;

      constexpr operator const value_type&() const&
      {
        return value;
      }

      constexpr
      operator value_type&&() &&
      {
        return move(value);
      }

      //
      // ... friends
      //

      friend constexpr bool
      operator==(const Value& x, const Value& y)
      {
        return x.value == y.value;
      }

      template<typename U>
      friend constexpr bool
      operator==(const Value& x, const U& y)
      {
        return false;
      }

      template<typename U>
      friend constexpr bool
      operator!=(const Value& x, const U& y)
      {
        return !(x == y);
      }

      template<typename Stream>
      friend Stream&
      operator<<(Stream& os, const Value& x)
      {
        os << x.value;
        return os;
      }

    }; // end of class Value

    template<typename T, typename R = Value<decay_t<T>>>
    constexpr R
    val(T&& x)
    {
      return Value<decay_t<T>>(forward<T>(x));
    }

    template<typename Stream, typename T>
    Stream&
    operator<<(Stream& os, Type<Value<T>> const&)
    {
      os << "Expression::Core::Value<" << type<T> << ">";
      return os;
    }

    template<typename T>
    ostream&
    operator<<(ostream& os, Type<Value<T>> const&)
    {
      os << "Expression::Core::Value<" << type<T> << ">";
      return os;
    }

  } // end of namespace Core
} // end of namespace Expression

#endif // !defined VALUE_HPP_INCLUDED_588284922219344181
