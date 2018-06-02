//
// ... Expression header files
//
#include <expression/occurs.hpp>


//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>


/** Test the predicate for any occurance of a variable */
struct Occurance_test
{
  Occurance_test() : accum( 0 ) {

    using namespace Expression::Core;
    
    EXPR_STATIC_TEST( ! occurs( var<0>, val( 3.0 )));
    EXPR_STATIC_TEST( occurs( var<0>, var<0> ));
    EXPR_STATIC_TEST( ! occurs( var<0>, var<1> ));
    EXPR_STATIC_TEST( occurs( var<0>, fun( var<0>, var<0> )));
    EXPR_STATIC_TEST( ! occurs( var<0>, fun( var<0>, var<1> )));
    EXPR_STATIC_TEST( occurs( var<0>, var<0>( var<1> )));
    EXPR_STATIC_TEST( occurs( var<0>, var<1>( var<0> )));
    EXPR_STATIC_TEST( occurs( var<0>, var<0>( var<0> )));
    EXPR_STATIC_TEST( ! occurs( var<0>, var<1>( var<2> )));

    EXPR_TEST( accum,  ! occurs( var<0>, val( 3.0 )));
    EXPR_TEST( accum,  occurs( var<0>, var<0> ));
    EXPR_TEST( accum,  ! occurs( var<0>, var<1> ));
    EXPR_TEST( accum,  occurs( var<0>, fun( var<0>, var<0> )));
    EXPR_TEST( accum,  ! occurs( var<0>, fun( var<0>, var<1> )));
    EXPR_TEST( accum,  occurs( var<0>, var<0>( var<1> )));
    EXPR_TEST( accum,  occurs( var<0>, var<1>( var<0> )));
    EXPR_TEST( accum,  occurs( var<0>, var<0>( var<0> )));
    EXPR_TEST( accum,  ! occurs( var<0>, var<1>( var<2> )));
    
  }
  
  operator int() const { return accum; }
  
  int accum;
}; // end of struct Occurance_test




/** Test the predicate for free occurance of a variable */
struct Free_occurance_test
{

  Free_occurance_test() : accum( 0 ) {
    using namespace Expression::Core;

    EXPR_STATIC_TEST( ! occurs_free( var<0>, val( 'x' )));
    EXPR_STATIC_TEST( occurs_free( var<0>, var<0>  ));
    EXPR_STATIC_TEST( ! occurs_free( var<0>, var<1>  ));
    EXPR_STATIC_TEST( occurs_free( var<0>, var<0>( var<0> )));
    EXPR_STATIC_TEST( occurs_free( var<0>, var<0>( var<1> )));
    EXPR_STATIC_TEST( occurs_free( var<0>, var<1>( var<0> )));
    EXPR_STATIC_TEST( ! occurs_free( var<0>, var<1>( var<2>  )));
    EXPR_STATIC_TEST( ! occurs_free( var<0>, fun( var<0>, var<0> )));
    EXPR_STATIC_TEST( ! occurs_free( var<0>, fun( var<0>, var<1> )));
    EXPR_STATIC_TEST( occurs_free( var<0>, fun( var<1>, var<0> )));
    EXPR_STATIC_TEST( ! occurs_free( var<0>, fun( var<1>, var<2> )));


    EXPR_TEST( accum, ! occurs_free( var<0>, val( 'x' )));
    EXPR_TEST( accum, occurs_free( var<0>, var<0>  ));
    EXPR_TEST( accum, ! occurs_free( var<0>, var<1>  ));
    EXPR_TEST( accum, occurs_free( var<0>, var<0>( var<0> )));
    EXPR_TEST( accum, occurs_free( var<0>, var<0>( var<1> )));
    EXPR_TEST( accum, occurs_free( var<0>, var<1>( var<0> )));
    EXPR_TEST( accum, ! occurs_free( var<0>, var<1>( var<2>  )));
    EXPR_TEST( accum, ! occurs_free( var<0>, fun( var<0>, var<0> )));
    EXPR_TEST( accum, ! occurs_free( var<0>, fun( var<0>, var<1> )));
    EXPR_TEST( accum, occurs_free( var<0>, fun( var<1>, var<0> )));
    EXPR_TEST( accum, ! occurs_free( var<0>, fun( var<1>, var<2> )));

    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Free_occurance_test



/** Test the predicate for bound occurance of a variable */
struct Bound_occurance_test
{
  Bound_occurance_test() : accum( 0 ) {
    
    using namespace Expression::Core;

    EXPR_STATIC_TEST( ! occurs_bound( var<0>, val( 8 ) ));
    EXPR_STATIC_TEST( ! occurs_bound( var<0>, var<0> ));
    EXPR_STATIC_TEST( ! occurs_bound( var<0>, var<0>( var<0> )));
    EXPR_STATIC_TEST( ! occurs_bound( var<0>, var<0>( var<1> )));
    EXPR_STATIC_TEST( ! occurs_bound( var<0>, var<1>( var<0> )));
    EXPR_STATIC_TEST( occurs_bound( var<0>, fun( var<0>, var<0> )));
    EXPR_STATIC_TEST( occurs_bound( var<0>, fun( var<0>, var<0>( var<0> ))));
    EXPR_STATIC_TEST( occurs_bound( var<0>, fun( var<0>, var<1>( var<0> ))));
    EXPR_STATIC_TEST( occurs_bound( var<0>, fun( var<0>, var<0>( var<1> ))));
    EXPR_STATIC_TEST( ! occurs_bound( var<0>, fun( var<0>, var<1> )));


    EXPR_TEST( accum, ! occurs_bound( var<0>, val( 8 ) ));
    EXPR_TEST( accum, ! occurs_bound( var<0>, var<0> ));
    EXPR_TEST( accum, ! occurs_bound( var<0>, var<0>( var<0> )));
    EXPR_TEST( accum, ! occurs_bound( var<0>, var<0>( var<1> )));
    EXPR_TEST( accum, ! occurs_bound( var<0>, var<1>( var<0> )));
    EXPR_TEST( accum, occurs_bound( var<0>, fun( var<0>, var<0> )));
    EXPR_TEST( accum, occurs_bound( var<0>, fun( var<0>, var<0>( var<0> ))));
    EXPR_TEST( accum, occurs_bound( var<0>, fun( var<0>, var<1>( var<0> ))));
    EXPR_TEST( accum, occurs_bound( var<0>, fun( var<0>, var<0>( var<1> ))));
    EXPR_TEST( accum, ! occurs_bound( var<0>, fun( var<0>, var<1> )));

  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Bound_occurance_test

int
main( int, char** )
{
  int accum = 0;
  accum += Occurance_test();
  accum += Free_occurance_test();
  accum += Bound_occurance_test();
  return accum;
}
