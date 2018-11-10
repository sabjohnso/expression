//
// ... Expression header files
//
#include <expression/expression.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>


/** Test the let form */
struct Let_test
{

  Let_test() : accum( 0 ) {
    using namespace Expression::Core;
    constexpr auto x   = var<0>;
    constexpr auto y   = var<1>;
    constexpr auto a   = var<3>;
    constexpr auto b   = var<4>;
    constexpr auto sqr = var<5>;
    constexpr auto twc = var<6>;
    

    constexpr auto e1 =
      fn( x, (let( y = x+a ),
	      y+b));
    
    constexpr auto e2 =
      (let( twc = fn( x, x+x ),
    	    sqr = fn( x, x*x )),
       fn( x, twc( sqr( x ))));

    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;
    
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Let_test

int
main( int, char** )
{
  int accum = 0;
  accum += Let_test();
  return accum;
}
