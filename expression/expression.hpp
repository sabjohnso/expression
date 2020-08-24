#ifndef EXPRESSION_HPP_INCLUDED_452739512301358018
#define EXPRESSION_HPP_INCLUDED_452739512301358018 1

//
// ... Expression header files
//
#include <expression/app.hpp>
#include <expression/de_bruijn.hpp>
#include <expression/fun.hpp>
#include <expression/let.hpp>
#include <expression/rewrite.hpp>
#include <expression/val.hpp>
#include <expression/var.hpp>

namespace Expression
{
  using Core::app;
  using Core::de_bruijn;
  using Core::fn;
  using Core::let;
  using Core::rewrite;
  using Core::val;
  using Core::var;

} // end of namespace Expression
#endif // !defined EXPRESSION_HPP_INCLUDED_452739512301358018
