//
// ...  Expression header files
//
#include <expression/val.hpp>


//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>
#include <expression_testing/test_tools.hpp>


/** Test values */
struct Value_test
{
  Value_test() : accum( 0 ) {
    using namespace Expression::Core;
    using namespace Expression::Testing;
    EXPR_STATIC_TEST( std::is_same<decltype(val( 3 )),Value<int>>::value );
    EXPR_TEST( accum, string_repr( val( 3 )) == "3" );

  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Value_test


int
main( int, char** )
{
  int accum = 0;
  return accum;
}
