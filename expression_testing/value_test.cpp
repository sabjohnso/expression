//
// ...  Expression header files
//
#include <expression/val.hpp>

//
// ... External library header files
//
#include <type_utility/type_utility.hpp>



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
    using TypeUtility::type_pure;

    EXPR_STATIC_TEST( std::is_same<decltype(val( 3 )),Value<int>>::value );
    EXPR_TEST( accum, string_repr( val( 3 )) == "3" );
    EXPR_TEST( accum, string_repr( type_pure( val( 3 ))) == "Expression::Core::Value<int>" );
    
  }
  
  operator int() const { return accum; }
  
  int accum;
}; // end of struct Value_test


int
main( int, char** )
{
  int accum = 0;
  accum += Value_test();
  return accum;
}
