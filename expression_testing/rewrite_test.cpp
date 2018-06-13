//
// ... Expression header files
//
#include <expression/rewrite.hpp>


//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>

/** Test expression rewriting */
struct Rewrite_test
{
  Rewrite_test() : accum( 0 ) {
    using namespace Expression::Core;
    EXPR_STATIC_TEST( rewrite( var<0>, var<0>, var<1>) == var<1> );
    EXPR_STATIC_TEST( rewrite( var<0>, var<1>, var<2>) == var<0> );
    EXPR_STATIC_TEST( rewrite( var<0>( var<1> ), var<0>, var<2>) ==
		      var<2>( var<1> ));
    EXPR_STATIC_TEST( rewrite( var<0>( var<1> ), var<1>, var<2>) ==
		      var<0>( var<2> ));
    EXPR_STATIC_TEST( rewrite( var<0>( var<0> ), var<0>, var<2>) ==
		      var<2>( var<2> ));

    EXPR_STATIC_TEST( rewrite( fn( var<0>, var<0> ), var<0>, var<2> ) ==
		      fn( var<0>, var<0> ));

    EXPR_STATIC_TEST( rewrite( fn( var<0>, var<1> ), var<1>, var<2> ) ==
		      fn( var<0>, var<2> ));
    
		      
    
      
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Rewrite_test

int
main( int, char** )
{
  int accum = 0;
  accum += Rewrite_test();
  return accum;
}
