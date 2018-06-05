#ifndef EXPRESSION_HPP_INCLUDED_452739512301358018
#define EXPRESSION_HPP_INCLUDED_452739512301358018 1

//
// ... Expression header files
//
#include <expression/fun.hpp>
#include <expression/app.hpp>
#include <expression/val.hpp>
#include <expression/var.hpp>
#include <expression/rewrite.hpp>
#include <expression/debruijn.hpp>


namespace Expression
{
  using Core::val;
  using Core::var;
  using Core::app;
  using Core::fun;
  using Core::de_bruijn;
  using Core::rewrite;
  
} // end of namespace Expression
#endif // !defined EXPRESSION_HPP_INCLUDED_452739512301358018
