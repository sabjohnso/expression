include(FetchGTest)

macro( expression_add_test  name )
  add_executable( ${name}_test ${name}_test.cpp )
  target_link_libraries( ${name}_test PRIVATE expression::expression )
  add_test( ${name} ${name}_test )
endmacro( expression_add_test  name )

expression_add_test( variable )
expression_add_test( application )
expression_add_test( abstraction )
expression_add_test( value )
expression_add_test( occurance )
expression_add_test( normal )
expression_add_test( rewrite )
expression_add_test( de_bruijn )
expression_add_test( simplify )
expression_add_test( arithmetic )
expression_add_test( binding )

expression_add_test( alternative )
expression_add_test( data )
expression_add_test( compile )
expression_add_test( boolean )
expression_add_test( guard )
expression_add_test( cond )


add_executable(conditional_test conditional.cpp)
target_link_libraries(conditional_test
  PRIVATE google::gtest_main expression::expression)
add_test(conditional conditional_test)

add_executable(let_test let_test.cpp)
target_link_libraries(let_test
  PRIVATE google::gtest_main expression::expression)
add_test(let let_test)
  
