//
// ... Expression header files
//
#include <expression/expression.hpp>
#include <expression/data.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>

/** Test the data declaration class */
struct Data_test
{
  Data_test() : accum( 0 )
  {
    using namespace Expression::Core;
    
    std::cout << Data<Variable<size_t,0>, Variable<size_t,1>>(var<0>, var<1>)
	      << std::endl;
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Data_test


int
main( int, char** )
{
  int accum = 0;
  accum += Data_test();
  return accum;
}
