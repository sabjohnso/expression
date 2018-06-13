//
// ... Expression header files
//
#include <expression/normal.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>


/** Test the predicate for eta normality 
 */
struct Eta_normal_test
{
  Eta_normal_test() : accum( 0 ) {
    using namespace Expression::Core;
    EXPR_STATIC_TEST( ! eta_normal( fn( var<0>, var<1>( var<0> ))));
    EXPR_STATIC_TEST( eta_normal( fn( var<0>, var<0>( var<1> ))));
    EXPR_STATIC_TEST( eta_normal( var<0> ));
    EXPR_STATIC_TEST( eta_normal( fn( var<0>, var<0> )));
    EXPR_STATIC_TEST( eta_normal( var<0>( var<1> ) ));

    EXPR_TEST( accum, ! eta_normal( fn( var<0>, var<1>( var<0> ))));
    EXPR_TEST( accum, eta_normal( fn( var<0>, var<0>( var<1> ))));
    EXPR_TEST( accum, eta_normal( var<0> ));
    EXPR_TEST( accum, eta_normal( fn( var<0>, var<0> )));
    EXPR_TEST( accum, eta_normal( var<0>( var<1> ) ));
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Eta_normal_test


/** Test the predicate for beta normal form 
 */
struct Beta_normal_test
{
  Beta_normal_test() : accum( 0 ) {
    using namespace Expression::Core;
    EXPR_STATIC_TEST( ! beta_normal( fn( var<0>, var<0>)( var< 1 > )));
    EXPR_STATIC_TEST( beta_normal( var<0>( var<1> )));
    EXPR_STATIC_TEST( beta_normal( var<0> ));
    EXPR_STATIC_TEST( beta_normal( fn( var<0>, var<0> )));
    EXPR_STATIC_TEST( beta_normal( val( 'x' )));

    EXPR_TEST( accum, ! beta_normal( fn( var<0>, var<0>)( var< 1 > )));
    EXPR_TEST( accum, beta_normal( var<0>( var<1> )));
    EXPR_TEST( accum, beta_normal( var<0> ));
    EXPR_TEST( accum, beta_normal( fn( var<0>, var<0> )));
    EXPR_TEST( accum, beta_normal( val( 'x' )));
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Beta_normal_test

int
main( int, char** )
{
  int accum = 0;
  accum += Eta_normal_test();
  accum += Beta_normal_test();
  return accum;
}
