
//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... Expression header files
//
#include <expression/expression.hpp>
#include <expression/de_bruijn.hpp>
#include <expression/simplify.hpp>
#include <expression/compile.hpp>


namespace Expression::Testing
{
  namespace  // anonymous  
  {
    using namespace Expression::Core;       
  } // end of anonymous namespace
  
  TEST( let, fun)
  {
    constexpr auto e =
      [a = var<0>,
       x = var<1>,
       y = var<2>,
       z = var<3>]{
      return 
      fn(a, x, y,
	 (let( z = a*x ),
	  y+z)); }();
    
    std::cout << de_bruijn( e) << std::endl;
    std::cout << e << std::endl;
    // auto f = compile_function(de_bruijn( e ));
  }
} // end of namespace Expression::Testing


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
