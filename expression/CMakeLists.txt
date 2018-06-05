
configure_file( config.hpp.in config.hpp )
install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  app.hpp
  de_bruijn.hpp
  expr.hpp
  expression.hpp
  fun.hpp
  fwd.hpp
  import.hpp
  normal.hpp
  occurs.hpp
  rewrite.hpp
  utility.hpp
  val.hpp
  var.hpp
  DESTINATION ${EXPRESSION_INSTALL_INCLUDE_DIR})



