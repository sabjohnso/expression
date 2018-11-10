//
// ... Expression header files
//
#include <expression/cond.hpp>
#include <expression/expression.hpp>


namespace 
{

  using namespace Expression::Core;
  /** Test the cond form */
  struct Cond_tester
  {
    Cond_tester() : accum( 0 ) {
      // constexpr auto t = var<100>;
      // constexpr auto p = var<101>;
      // constexpr auto f = var<102>;
	
      // cond( t >> p, f );



      
      // constexpr auto t1 = var<103>;
      // constexpr auto e1 = var<104>;
      // constexpr auto t2 = var<105>;
      // constexpr auto e2 = var<106>;
      // constexpr auto e3 = var<107>;
	
      // cond( t1 >> e1,
      // 	    t2 >> e2,
      // 	    e3 );
	
    }
    operator int() const { return accum; }
    int accum;
  }; // end of struct Cond_tester
  
} // end of anonymous namespace 



int
main( int, char** )
{
  int accum = 0;
  accum += Cond_tester{};
  return accum;
}
