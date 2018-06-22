//
// ... Expession header files
//
#include <expression/alternative.hpp>
#include <expression/expression.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>



/** Test the alternative expresion class 
 */
struct Alternative_test
{
  Alternative_test() : accum( 0 ) {

    using namespace Expression::Core;
    EXPR_STATIC_TEST(
      (var<0> | var<1>) == alt( var<0>, var<1> ));

    using namespace Expression::Core;
    EXPR_STATIC_TEST( 
      (var<0> | var<1> | var<2> ) == alt( var<0>, var<1>, var<2> ));

    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Alternative_test


int
main( int, char** )
{
  int accum = 0;
  accum += Alternative_test();
  return accum;
}
