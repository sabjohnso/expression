#ifndef BOOLEAN_HPP_INCLUDED_1391788974648734952
#define BOOLEAN_HPP_INCLUDED_1391788974648734952 1

//
// ... Expression header files header files
//
#include <expression/import.hpp>
#include <expression/var.hpp>
#include <expression/fun.hpp>
#include <expression/de_bruijn.hpp>



namespace Expression::Core
{


  class BooleanModule{
    static constexpr auto x = var<10>;
    static constexpr auto y = var<11>;
  public:
    
    static constexpr auto True  = de_bruijn( fn(x, y, x));
    static constexpr auto False = de_bruijn( fn(x, y, y));
    
  }; // end of class BooleanModule


  constexpr auto True  = BooleanModule::True;
  constexpr auto False = BooleanModule::False;
       
  
} // end of namespace Expression::Core

#endif // !defined BOOLEAN_HPP_INCLUDED_1391788974648734952
