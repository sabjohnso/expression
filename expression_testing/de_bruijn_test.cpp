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

    reindex_test();
    predicate_test();
    index_inversion_test();
    
  }
  operator int() const { return accum; }
private:

  void
  reindex_test(){
    
    using namespace Expression::Core;

    EXPR_STATIC_TEST( de_bruijn( var<0> ) == var<0> );
    EXPR_STATIC_TEST( de_bruijn( var<1>( var<0> )) == var<1>( var<0> ));
    EXPR_STATIC_TEST( de_bruijn( fn( var<0>, var<0> )) == fn( var<0>, var<0> ));
    EXPR_STATIC_TEST( de_bruijn( fn( var<1>, var<1> )) == fn( var<0>, var<0> ));
    EXPR_STATIC_TEST( de_bruijn( fn( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> )))) ==
		      fn( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> ))));

    EXPR_STATIC_TEST( 
      de_bruijn( fn( var<0>, var<1>, var<2>, var<0>( var<2>, var<1>( var<2> ))))
      ==  fn( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> ))));


    EXPR_TEST( accum, de_bruijn( var<0> ) == var<0> );
    EXPR_TEST( accum, de_bruijn( var<1>( var<0> )) == var<1>( var<0> ));
    EXPR_TEST( accum, de_bruijn( fn( var<0>, var<0> )) == fn( var<0>, var<0> ));
    EXPR_TEST( accum, de_bruijn( fn( var<1>, var<1> )) == fn( var<0>, var<0> ));
    EXPR_TEST( accum, de_bruijn( fn( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> )))) ==
		      fn( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> ))));

    EXPR_TEST( accum, 
      de_bruijn( fn( var<0>, var<1>, var<2>,
		      var<0>( var<2>, var<1>( var<2> )))) == 
      fn( var<2>, var<1>, var<0>,
	   var<2>( var<0>, var<1>( var<0> ))));

  }
    
  void
  predicate_test(){
    
    using namespace Expression::Core;
    
    EXPR_STATIC_TEST( is_de_bruijn( fn( var<0>, var<0> )));
    EXPR_STATIC_TEST( is_de_bruijn( fn( var<1>, var<0>, var<1> )));
    EXPR_STATIC_TEST( ! is_de_bruijn( fn( var<0>, var<1>, var<0> )));
    
  }

  void
  index_inversion_test(){

    using namespace Expression::Core;
    
    EXPR_STATIC_TEST( de_bruijn_invert( fn( var<0>, var<0> )) == fn( var<0>, var<0> ));
    EXPR_STATIC_TEST( de_bruijn_invert( fn( var<1>, var<0>, var<1> )) ==
		      fn( var<0>, var<1>, var<0> ));
    
    EXPR_STATIC_TEST( 
      de_bruijn_invert( fn( var<2>, var<1>, var<0>, var<2>( var<0>, var<1>( var<0> )))) ==
      fn( var<0>, var<1>, var<2>, var<0>( var<2>, var<1>( var<2> ))));
    
  }
  int accum;
}; // end of struct DeBruijn_test

int
main( int, char** )
{
  int accum = 0;
  accum += DeBruijn_test();
  return accum;
}
