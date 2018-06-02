//
// ... Standard header files
//
#include <sstream>

//
// ... Expression header files
//
#include <expression/app.hpp>
#include <expression/var.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>

/** Test function application 
 */
struct Application_test
{
  Application_test() : accum( 0 ) {
    using std::stringstream;
    using namespace Expression::Core;
    stringstream ss;
    ss<< app( var<1>, var<0> );
    EXPR_TEST( accum, ss.str() == "(%1 %0)" );
  }
  
  operator int() const { return accum; }
  int accum;
}; // end of struct Application_test




int
main( int, char** )
{
  int accum = 0;
  accum += Application_test();
  return accum;
}
