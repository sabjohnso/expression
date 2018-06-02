//
// ... Standard header files
//
#include <sstream>

//
// ... Expression header files
//
#include <expression/fun.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>
#include <expression_testing/test_tools.hpp>

/** Test function definition 
 */
struct Abstraction_test
{
  Abstraction_test() : accum( 0 ) {

    using namespace Expression::Core;
    using namespace Expression::Testing;
    using std::stringstream;
    
    stringstream ss;

    EXPR_TEST( 
      accum, 
      string_repr( fun( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> )))) ==
      "$2:$1:$0:((%2 %0) (%1 %0))" );

    
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Abstraction_test

int
main( int, char** )
{
  int accum = 0;
  accum += Abstraction_test();
  return accum;
}
