//
// ... Standard header files
//
#include <type_traits>
#include <sstream>

//
// ... Expression header files
//
#include <expression/var.hpp>


//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>


/** Test the variable type 
*/
struct Variable_test
{
  Variable_test() : accum( 0 ) {
    using namespace Expression::Core;
    using std::decay_t;
    using std::is_same;
    using std::stringstream;
    
    EXPR_STATIC_TEST( is_same<decay_t<decltype(var<0>)>,Variable<size_t,0>>::value );
    EXPR_STATIC_TEST( var<0> == var<0> );
    EXPR_STATIC_TEST( !( var<0> == var<1> ));
    EXPR_STATIC_TEST( var<0>( var<1> ) == app( var<0>, var<1> ));

    EXPR_TEST( accum, var<0> == Variable<size_t,0>{} );
    EXPR_TEST( accum, var<0> == var<0> );
    EXPR_TEST( accum, !( var<0> == var<1> ));
  
    stringstream ss;
    ss << var<0>;
    EXPR_TEST( accum, ss.str() == "%0" );
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Variable_test

int
main( int, char** )
{
  int accum = 0;
  accum += Variable_test();
  return accum;
}
