#ifndef OCCURS_HPP_INCLUDED_1601795310995521658
#define OCCURS_HPP_INCLUDED_1601795310995521658 1

//
// ... Expression header files
//
#include <expression/app.hpp>
#include <expression/fun.hpp>
#include <expression/import.hpp>
#include <expression/val.hpp>
#include <expression/var.hpp>

namespace Expression
{
  namespace Core
  {
    constexpr class Occurs
    {

    public:
      template<typename T, T Index, typename E>
      constexpr bool
      operator()(Variable<T, Index>, E&&) const&
      {
        return aux(integer<T, Index>, type<decay_t<E>>);
      }

      template<typename T, T Index, typename E>
      constexpr bool operator()(Integer<T, Index>, Type<E>) const&
      {
        return aux(integer<T, Index>, type<E>);
      }

    private:
      template<typename T, T Index>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Variable<T, Index>>)
      {
        return true;
      }

      template<typename T, T Index, T OtherIndex, typename Body>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Abstraction<T, OtherIndex, Body>>)
      {
        return aux(integer<T, Index>, type<Body>);
      }

      template<typename T, T Index, typename F, typename A>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Application<F, A>>)
      {
        return aux(integer<T, Index>, type<F>) ||
               aux(integer<T, Index>, type<A>);
      }

      template<typename T, T Index, typename E>
      static constexpr bool aux(Integer<T, Index>, Type<E>)
      {
        return false;
      }
    } occurs{};

    constexpr class Occurs_bound
    {
    public:
      template<typename T, T Index, typename E>
      constexpr bool
      operator()(Variable<T, Index>, E&&) const&
      {
        return aux(integer<T, Index>, type<decay_t<E>>);
      }

      template<typename T, T Index, typename E>
      constexpr bool operator()(Integer<T, Index>, Type<E>) const&
      {
        return aux(integer<T, Index>, type<E>);
      }

    private:
      template<typename T, T Index, typename Body>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Abstraction<T, Index, Body>>)
      {
        return occurs(integer<T, Index>, type<Body>);
      }

      template<typename T, T Index, T OtherIndex, typename Body>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Abstraction<T, OtherIndex, Body>>)
      {
        return aux(integer<T, Index>, type<Body>);
      }

      template<typename T, T Index, typename F, typename A>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Application<F, A>>)
      {
        return aux(integer<T, Index>, type<F>) ||
               aux(integer<T, Index>, type<A>);
      }

      template<typename T, T Index, typename E>
      static constexpr bool aux(Integer<T, Index>, Type<E>)
      {
        return false;
      }

    } occurs_bound{};

    constexpr class Occurrs_free
    {
    public:
      template<typename T, T Index, typename E>
      constexpr bool
      operator()(Variable<T, Index>, E&&) const&
      {
        return aux(integer<T, Index>, type<decay_t<E>>);
      }

      template<typename T, T Index, typename E>
      constexpr bool operator()(Integer<T, Index>, Type<E>) const&
      {
        return aux(integer<T, Index>, type<E>);
      }

    private:
      template<typename T, T Index>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Variable<T, Index>>)
      {
        return true;
      }

      template<typename T, T Index, typename Body>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Abstraction<T, Index, Body>>)
      {
        return false;
      }

      template<typename T, T Index, T OtherIndex, typename Body>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Abstraction<T, OtherIndex, Body>>)
      {
        static_assert(Index != OtherIndex, "Expected differnt values");
        return aux(integer<T, Index>, type<Body>);
      }

      template<typename T, T Index, typename F, typename A>
      static constexpr bool aux(
        Integer<T, Index>,
        Type<Application<F, A>>)
      {
        return aux(integer<T, Index>, type<F>) ||
               aux(integer<T, Index>, type<A>);
      }

      template<typename T, T Index, typename E>
      static constexpr bool aux(Integer<T, Index>, Type<E>)
      {
        return false;
      }

    } occurs_free{};

    constexpr class Has_free_variables
    {
    public:
      template<typename E>
      constexpr bool
      operator()(E&&) const&
      {
        return aux(type<decay_t<E>>);
      }

      template<typename E>
      constexpr bool operator()(Type<E>) const&
      {
        return aux(type<E>);
      }

    private:
      //
      // ... before any binding is found
      //

      template<typename T>
      static constexpr bool aux(Type<Value<T>>)
      {
        return false;
      }

      template<typename T, T Index>
      static constexpr bool aux(Type<Variable<T, Index>>)
      {
        return true;
      }

      template<typename F, typename A>
      static constexpr bool aux(Type<Application<F, A>>)
      {
        return aux(type<F>) || aux(type<A>);
      }

      template<typename T, T Index, typename Body>
      static constexpr bool aux(Type<Abstraction<T, Index, Body>>)
      {
        return aux(integer_set<T, Index>, type<Body>);
      }

      //
      // ... With set of bound indices
      //

      template<typename T, T... BoundIndices, typename U>
      static constexpr bool aux(
        Integer_set<T, BoundIndices...>,
        Type<Value<U>>)
      {
        return false;
      }

      template<typename T, T... BoundIndices, T Index>
      static constexpr bool
      aux(
        Integer_set<T, BoundIndices...> bound_set,
        Type<Variable<T, Index>>)
      {
        return !ismember(bound_set, integer<T, Index>);
      }

      template<typename T, T... BoundIndices, typename F, typename A>
      static constexpr bool
      aux(
        Integer_set<T, BoundIndices...> bound_set,
        Type<Application<F, A>>)
      {
        return aux(bound_set, type<F>) || aux(bound_set, type<A>);
      }

      template<typename T, T... BoundIndices, T Index, typename Body>
      static constexpr bool
      aux(
        Integer_set<T, BoundIndices...> bound_set,
        Type<Abstraction<T, Index, Body>>)
      {
        return aux(
          integer_set_add(bound_set, integer<T, Index>), type<Body>);
      }

    } has_free_variables{};

  } // end of namespace Core
} // end of namespace Expression

#endif // !defined OCCURS_HPP_INCLUDED_1601795310995521658
