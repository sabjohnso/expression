//
// ... Expression header files
//
#include <expression/import.hpp>
#include <expression/expr.hpp>
#include <expression/guard.hpp>
#include <expression/var.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>


namespace 
{


  using namespace Expression::Core;

  /** Test guarded expressions */
  class Guarded_expression_tester
  {
    
  public:
    Guarded_expression_tester() : accum( 0 ) {
      // EXPR_TEST( accum, std::to_string( var<0> >> var<1> ) == "%0 >> %1" );
    }
    operator int() const { return accum; }
  private:
    int accum;
  }; // end of struct Guared_expression_tester
} // end of anonymous namespace 




int
main( int, char** )
{
  int accum = 0;
  accum += Guarded_expression_tester();
  return accum;
}
