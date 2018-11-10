configure_file( config.hpp.in config.hpp )
install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  alternative.hpp
  app.hpp
  binding.hpp
  compile.hpp
  cond.hpp
  data.hpp
  de_bruijn.hpp
  expression.hpp
  expr.hpp
  fun.hpp
  fwd.hpp
  import.hpp
  let.hpp
  normal.hpp
  occurs.hpp
  rewrite.hpp
  simplify.hpp
  utility.hpp
  val.hpp
  var.hpp
  DESTINATION ${EXPRESSION_INSTALL_INCLUDE_DIR}/expression )

configure_file( expression-config.cmake.in expression-config.cmake )
install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/expression-config.cmake
  DESTINATION ${EXPRESSION_INSTALL_LIBRARY_DIR})
