macro( expression_add_simple_test  name )
  add_executable( ${name}_test ${name}_test.cpp )
  add_test( ${name} ${name}_test )
endmacro( expression_add_simple_test name )


expression_add_simple_test( variable )
expression_add_simple_test( application )
expression_add_simple_test( abstraction )
expression_add_simple_test( value )
expression_add_simple_test( occurance )
expression_add_simple_test( normal )
expression_add_simple_test( rewrite )
expression_add_simple_test( de_bruijn )
expression_add_simple_test( simplify )
expression_add_simple_test( arithmetic )
expression_add_simple_test( binding )
expression_add_simple_test( let )
expression_add_simple_test( alternative )
expression_add_simple_test( data )
expression_add_simple_test( compile )




