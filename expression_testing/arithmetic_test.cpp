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

/** Test arithmetic operators in expressions */
struct Arithmetic_test
{
  Arithmetic_test() : accum( 0 ) {
    addition_test();
  }
  operator int() const { return accum; }

  void
  addition_test(){
    using namespace Expression::Core;
   
    using Operators::Addition;
    using std::is_same;
    using std::decay_t;
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
