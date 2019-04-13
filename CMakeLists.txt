#
# ... Build script for expression
#

cmake_minimum_required( VERSION 3.12 )
project( EXPRESSION VERSION 0.1.0 LANGUAGES CXX)

#
# ... Build options
#
option( BUILD_EXPRESSION_TESTING  "Build the expression tests" ON )
option( BUILD_EXPRESSION_DOCUMENTATION "Build the documentation" ON )
option( INSTALL_EXPRESSION "Install the expression library" ON)
option( EXPRESSION_INSTALL_VERSIONED "Version specific installation" ON )

#
# ... Installation path information
#
if(INSTALL_EXPRESSION)
  include(GNUInstallDirs)
  if(EXPRESSION_INSTALL_VERSIONED)
    set(EXPRESSION_SUFFIX ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
    set(EXPRESSION_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDE_DIR}/expression-${EXPRESSION_SUFFIX})
    set(EXPRESSION_INSTALL_CONFDIR ${CMAKE_INSTALL_LIBDIR}/expression-${EXPRESSION_SUFFIX})      
  else()
  endif()
endif()

#
# ... Dependencies
#
find_package( type_utility REQUIRED )
find_package( function_utility REQUIRED )
find_package( operators REQUIRED )

#
# ... Walk source tree
# 
add_subdirectory(expression)

#
# ... Header library target
#
add_library( expression INTERFACE )
add_library( expression::expression ALIAS expression )
target_link_libraries( expression INTERFACE
  type_utility::type_utility
  function_utility::function_utility
  operators::operators )
target_include_directories(expression INTERFACE
  $<BUILD_INTERFACE:${EXPRESSION_SOURCE_DIR}> 
  $<BUILD_INTERFACE:${EXPRESSION_BINARY_DIR}>)





if(INSTALL_EXPRESSION)
  target_include_directories(expression INTERFACE
    $<INSTALL_INTERFACE:${EXPRESSION_INSTALL_INCLUDE_DIR}> )
  
  install( TARGETS expression
    EXPORT expression
    DESTINATION ${EXPRESSION_INSTALL_CONFDIR})

  install(
    EXPORT expression
    DESTINATION ${EXPRESSION_INSTALL_CONFDIR}
    NAMESPACE expression::
    FILE expression.cmake )

  configure_file(expression-config.cmake.in expression-config.cmake)
  install(
    FILES ${EXPRESSION_BINARY_DIR}/expression-config.cmake
    DESTINATION ${EXPRESSION_INSTALL_CONFDIR} )

endif()




#
# ... Testing
#
if( BUILD_EXPRESSION_TESTING )
  enable_testing()
  add_subdirectory( expression_testing )
endif( BUILD_EXPRESSION_TESTING )



# end of build definition for expression
