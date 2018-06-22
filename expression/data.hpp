#ifndef DATA_HPP_INCLUDED_2184104099366006761
#define DATA_HPP_INCLUDED_2184104099366006761 1


namespace Expression
{
  namespace Core
  {

    template< typename Left, typename Right >
    class Data : pair<Left,Right> {
    public:
      using left_type = Left;
      using right_type = Right;

      using base = pair<left_type,right_type>;

      using base::base;

     
      template< typename Stream >
      friend Stream& 
      operator <<( Stream& os, const Data& d ){
	os << "data(" << d.first << " = " << d.second << ")"; 
	return os;
      }
      
    }; // end of class data

	 
					    
					    
					    
					    
   
   
    
    
  } // end of namespace Core
} // end of namespace Expression

#endif // !defined DATA_HPP_INCLUDED_2184104099366006761
