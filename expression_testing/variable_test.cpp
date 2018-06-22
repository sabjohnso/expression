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
// ... External library header files
//
#include <type_utility/type_utility.hpp>



//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>
#include <expression_testing/test_tools.hpp>

    using namespace Expression::Core;
    using std::decay_t;
    using std::is_same;
    using std::is_empty;
    using Expression::Testing::string_repr;
    using TypeUtility::type_pure;


/** Test the variable type 
*/
struct Variable_test
{
  Variable_test() : accum( 0 ) {


  

    instance_printing_test();
    type_printing_test();

    
  }
  operator int() const { return accum; }

  void
  static_tests(){   
    EXPR_STATIC_TEST( is_empty<Variable<size_t,0>>::value );
    EXPR_STATIC_TEST( is_same<decay_t<decltype(var<0>)>,Variable<size_t,0>>::value );
    EXPR_STATIC_TEST( var<0> == var<0> );
    EXPR_STATIC_TEST( !( var<0> == var<1> ));
    EXPR_STATIC_TEST( var<0>( var<1> ) == app( var<0>, var<1> ));
  }

  void
  runtime_tests(){
    EXPR_TEST( accum, var<0> == Variable<size_t,0>{} );
    EXPR_TEST( accum, var<0> == var<0> );
    EXPR_TEST( accum, !( var<0> == var<1> ));
  }

  void
  instance_printing_test(){    
    EXPR_TEST(
      accum,
      string_repr( var<0> ) == "%0" );
  }

  void
  type_printing_test(){
    EXPR_TEST( 
      accum, 
      string_repr( type_pure( var<0> )) == "Expression::Core::Variable<unsigned long,0>" );
  }
  int accum;
}; // end of struct Variable_test

int
main( int, char** )
{
  int accum = 0;
  accum += Variable_test();
  return accum;
}
