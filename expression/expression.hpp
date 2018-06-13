#ifndef EXPRESSION_HPP_INCLUDED_452739512301358018
#define EXPRESSION_HPP_INCLUDED_452739512301358018 1

//
// ... Expression header files
//
#include <expression/fun.hpp>
#include <expression/app.hpp>
#include <expression/val.hpp>
#include <expression/var.hpp>
#include <expression/let.hpp>
#include <expression/rewrite.hpp>
#include <expression/de_bruijn.hpp>


namespace Expression
{
  using Core::val;
  using Core::var;
  using Core::app;
  using Core::fn;
  using Core::de_bruijn;
  using Core::rewrite;
  using Core::let;
  
} // end of namespace Expression
#endif // !defined EXPRESSION_HPP_INCLUDED_452739512301358018
