//
// ... Standard header files
//
#include <iostream>


//
// ... Expression header files
//
#include <expression/expression.hpp>


//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>

/** UNDOCUMENTED TEST */
struct Arithmetic_test
{
  Arithmetic_test() : accum( 0 ) {
    addition_test();
  }
  operator int() const { return accum; }

  void
  addition_test(){
    using namespace Expression;
    constexpr auto x = var<1>;
    constexpr auto y = var<2>;
    std::cout << fn( x, y, x+y ) << std::endl;
  }
private:
  
  int accum;
}; // end of struct Arithmetic_test


int
main( int, char** )
{
  int accum = 0;
  accum += Arithmetic_test();
  return accum;
}
