#ifndef TEST_TOOLS_HPP_INCLUDED_439081492874460852
#define TEST_TOOLS_HPP_INCLUDED_439081492874460852 1


//
// ... Standard header files
//
#include <string>
#include <sstream>


namespace Expression
{
  namespace Testing
  {
    using std::string;
    using std::stringstream;


    template< typename T >
    string
    string_repr( const T& x ){
      stringstream ss;
      ss << x;
      return ss.str();
    }
    
  } // end of namespace Testing
} // end of namespace Expression

#endif // !defined TEST_TOOLS_HPP_INCLUDED_439081492874460852
