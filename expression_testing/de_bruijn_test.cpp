//
// ... Expression header files
//
#include <expression/de_bruijn.hpp>


//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>

/** Test De Bruijn indexing 
 */
struct DeBruijn_test
{
  DeBruijn_test() : accum( 0 ) {
    using namespace Expression::Core;
    EXPR_STATIC_TEST( de_bruijn( var<0> ) == var<0> );
    EXPR_STATIC_TEST( de_bruijn( var<1>( var<0> )) == var<1>( var<0> ));
    EXPR_STATIC_TEST( de_bruijn( fun( var<0>, var<0> )) == fun( var<0>, var<0> ));
    EXPR_STATIC_TEST( de_bruijn( fun( var<1>, var<1> )) == fun( var<0>, var<0> ));
    EXPR_STATIC_TEST( de_bruijn( fun( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> )))) ==
		      fun( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> ))));

    EXPR_STATIC_TEST( 
      de_bruijn( fun( var<0>, var<1>, var<2>, var<0>( var<2>, var<1>( var<2> ))))
      ==  fun( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> ))));


    EXPR_TEST( accum, de_bruijn( var<0> ) == var<0> );
    EXPR_TEST( accum, de_bruijn( var<1>( var<0> )) == var<1>( var<0> ));
    EXPR_TEST( accum, de_bruijn( fun( var<0>, var<0> )) == fun( var<0>, var<0> ));
    EXPR_TEST( accum, de_bruijn( fun( var<1>, var<1> )) == fun( var<0>, var<0> ));
    EXPR_TEST( accum, de_bruijn( fun( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> )))) ==
		      fun( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> ))));

    EXPR_TEST( accum, 
      de_bruijn( fun( var<0>, var<1>, var<2>,
		      var<0>( var<2>, var<1>( var<2> )))) == 
      fun( var<2>, var<1>, var<0>,
	   var<2>( var<0>, var<1>( var<0> ))));

  }
  operator int() const { return accum; }
  int accum;
}; // end of struct DeBruijn_test

int
main( int, char** )
{
  int accum = 0;
  accum += DeBruijn_test();
  return accum;
}
