//
// ... Expression header files
//
#include <expression/boolean.hpp>
#include <expression/compile.hpp>

//
// ... Testing header files
//
#include <expression_testing/test_macros.hpp>

namespace 
{
  using namespace Expression::Core;
  /** Test the church encoded booleans */
  class Boolean
  {
  public:
    
    Boolean() : accum( 0 ) {
      std::cout << True << std::endl;
      std::cout << False << std::endl;

      EXPR_STATIC_TEST( (compile( True )( 3, 4 )) == 4 );
      EXPR_STATIC_TEST( (compile( False )( 10, 2 )) == 10);
      
    }
    operator int() const { return accum; }
    
  private:
    int accum;
  }; // end of struct Boolean
  
} // end of anonymous namespace 


int
main( int, char** )
{
  int accum = 0;
  accum += Boolean();
  return accum;
}



