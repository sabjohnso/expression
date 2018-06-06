//
// ... Expression header files
//
#include <expression/simplify.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>



/** Test eta reduction */
struct Eta_reduce_test
{
  Eta_reduce_test() : accum( 0 ) {
    using namespace Expression::Core;
    EXPR_STATIC_TEST( eta_reduce( var<0> ) == var<0> );
    EXPR_STATIC_TEST( eta_reduce( val( 'x' )) == val( 'x' ));
    EXPR_STATIC_TEST( eta_reduce( var<0>( var<1> )) == var<0>( var<1> ));
    EXPR_STATIC_TEST( eta_reduce( fun( var<0>, var<1>( var<0> ))) == var<1> );

    EXPR_TEST( accum, eta_reduce( var<0> ) == var<0> );
    EXPR_TEST( accum, eta_reduce( val( 'x' )) == val( 'x' ));
    EXPR_TEST( accum, eta_reduce( var<0>( var<1> )) == var<0>( var<1> ));
    EXPR_TEST( accum, eta_reduce( fun( var<0>, var<1>( var<0> ))) == var<1> );
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Eta_reduce_test


/** Test beta reduction */
struct Beta_reduce_test
{
  Beta_reduce_test() : accum( 0 ) {
    using namespace Expression::Core;
    EXPR_STATIC_TEST( beta_reduce( var<0> ) == var<0> );
    EXPR_STATIC_TEST( beta_reduce( val( 'x' ) == val( 'x' )));
    beta_reduce( fun( var<0>, var<0>)( val( 'x' )));
    
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Beta_reduce_test


/** Simplify test */
struct Simplify_test
{
  Simplify_test() : accum( 0 ) {
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Simplify_test


int
main( int, char** )
{
  int accum = 0;
  accum += Eta_reduce_test();
  accum += Beta_reduce_test();
  accum += Simplify_test();
  return accum;
}
