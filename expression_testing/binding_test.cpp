//
// ... Expression header files
//
#include <expression/expression.hpp>


//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>


/** Binding_test */
struct Binding_test
{
  Binding_test() : accum( 0 ) {
    using namespace Expression::Core;
    constexpr auto x = var<0> = var<1> + var<2>;

    std::cout << x << std::endl;
    
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Binding_test

int
main( int, char** )
{
  int accum = 0;
  accum += Binding_test();
  return accum;
}
