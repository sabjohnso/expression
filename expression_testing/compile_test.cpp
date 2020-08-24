//
// ... Expression header files
//
#include <expression/expression.hpp>
#include <expression/compile.hpp>


//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>


/** Test compiling expressions */
struct Compile_test
{
  Compile_test() : accum( 0 ) {
    variable_test();
    value_test();
    operator_test();
    function_test();
  }
  
  operator int() const { return accum; }
private:

  void
  variable_test(){
    using namespace Expression::Core;
    constexpr auto f = compile( var<0>  );
    constexpr auto g = compile( var<1>  );
    EXPR_STATIC_TEST( f( 0, 1, 2, 3 ) == 0 );
    EXPR_STATIC_TEST( g( 0, 1, 2, 3 ) == 1 );

    EXPR_TEST(accum, f( 0, 1, 2, 3 ) == 0 );
    EXPR_TEST(accum, g( 0, 1, 2, 3 ) == 1 );

    
  }

  void
  value_test(){
    
  }

  void
  operator_test(){
    using namespace Expression::Core;

    constexpr auto f = compile( var<0>+var<1> );
    EXPR_STATIC_TEST( f( 3, 4 ) == 7 );

    constexpr auto g = compile( var<0>-var<1> );
    EXPR_STATIC_TEST( g( 3, 4 ) == -1 );

    constexpr auto h = compile( var<0>*var<1> );
    EXPR_STATIC_TEST( h( 3, 4 ) == 12 );

    constexpr auto i = compile( var<0>/var<1> );
    EXPR_STATIC_TEST( i( 3, 4 ) == 0 );
    
    constexpr auto axpy = compile( var<0>*var<1>+var<2> );
    EXPR_STATIC_TEST( axpy( 2, 3, 4 ) == 10 );

    constexpr auto sqr = compile( var<0>*var<0> );
    EXPR_STATIC_TEST( sqr( 3 ) == 9 );    
  }



  void
  function_test(){
    using namespace Expression::Core;
    constexpr auto x = var<0>;
    constexpr auto y = var<1>;
    constexpr auto a = var<2>;
    constexpr auto id = compile_function( fn( x, x ));
    
    
    EXPR_STATIC_TEST( id( 'x' ) == 'x' );
    EXPR_STATIC_TEST( compile_function( fn( x, x*x ))( 2 ) == 4 );

    constexpr auto axpy = compile_function( 
      de_bruijn( fn( a, x, y, a*x+y )));
    
    EXPR_STATIC_TEST(axpy( 2, 3, 4 ) == 10);
    
  } //end of function_test

  int accum;
}; // end of struct Compile_test


int
main( int, char** )
{
  int accum = 0;
  accum += Compile_test();
  return accum;
}
