#
# ... Build script for expression
#

cmake_minimum_required( VERSION 3.1 )

project( EXPRESSION )

#
# ... Version information
#
set( EXPRESSION_MAJOR  0 )
set( EXPRESSION_MINOR  1 )
set( EXPRESSION_UPDATE 0 )

set( EXPRESSION_SUFFIX -${EXPRESSION_MAJOR}.${EXPRESSION_MINOR})

set( EXPRESSION_VERSION expression-${EXPRESSION_SUFFIX} )
set( EXPRESSION_VERSION_UPDATE ${EXPRESSION_VERSION}.{EXPRESSION_UPDATE} )


#
# ... Build options
#
option( BUILD_EXPRESSION_TESTING  "Build the expression tests" ON )
option( BUILD_EXPRESSION_DOCUMENTATION "Build the documentation" ON )
option( EXPRESSION_INSTALL_VERSIONED "Version specific installation" ON )

#
# ... Installation path information
#
set( EXPRESSION_INSTALL_INCLUDE_DIR include
  CACHE PATH "Path for installation of header files")

set( EXPRESSION_INSTALL_LIBRARY_DIR lib/expression
  CACHE PATH "Path for installation of header files")

if( EXPRESSION_INSTALL_VERSIONED )
  string( APPEND EXPRESSION_INSTALL_INCLUDE_DIR /expression${EXPRESSION_SUFFIX} )
  string( APPEND EXPRESSION_INSTALL_LIBRARY_DIR ${EXPRESSION_SUFFIX})
endif()


#
# ... Dependencies
#
find_package( type_utility REQUIRED )
find_package( function_utility REQUIRED )
find_package( operators REQUIRED )





#
# ... Header library target
#
add_library( expression INTERFACE )
target_link_libraries( expression PUBLIC type_utility function_utility operators)

target_include_directories(expression INTERFACE $<INSTALL_INTERFACE:${EXPRESSION_INSTALL_INCLUDE_DIR}>)
target_include_directories(expression INTERFACE $<BUILD_INTERFACE:${EXPRESSION_SOURCE_DIR}>)
target_include_directories(expression INTERFACE $<BUILD_INTERFACE:${EXPRESSION_BINARY_DIR}>) 

install( TARGETS expression
  EXPORT expression
  DESTINATION ${EXPRESSION_INSTALL_LIBRARY_DIR})

install( EXPORT expression
  DESTINATION ${EXPRESSION_INSTALL_LIBRARY_DIR}
  FILE expression.cmake )


#
# ... Walk source tree
# 
add_subdirectory( expression )



#
# ... Testing
#
if( BUILD_EXPRESSION_TESTING )
  enable_testing()
  add_subdirectory( expression_testing )
endif( BUILD_EXPRESSION_TESTING )



#
# ... Documentation
#
if( BUILD_EXPRESSION_DOCUMENTATION )

  configure_file( Doxyfile.in Doxyfile )
  
  set( EXPRESSION_INSTALL_DOC_DIR share/${EXPRESSION_VERSION}
    CACHE PATH "Path for installation of documentation")


  
  set( EXPRESSION_INSTALL_MAN_DIR share
    CACHE PATH "Path for installation of manual pages" )


  find_package( Doxygen REQUIRED )
  configure_file( Doxyfile.in Doxygen )
  add_custom_command(
    OUTPUT ${EXPRESSION_BINARY_DIR}/doxygen.log
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile > doxygen.log
    MAIN_DEPENDENCY Doxyfile
    DEPENDS ${EXPRESSION_SOURCE_DIR}/expression
    WORKING_DIRECTORY ${EXPRESSION_BINARY_DIR} )

  add_custom_target(
    affix_documentation ALL
    DEPENDS ${EXPRESSION_BINARY_DIR}/doxygen.log )

  install( DIRECTORY ${EXPRESSION_BINARY_DIR}/doc/html DESTINATION ${EXPRESSION_INSTALL_DOC_DIR})
  install( DIRECTORY ${EXPRESSION_BINARY_DIR}/doc/man DESTINATION ${EXPRESSION_INSTALL_MAN_DIR})
  
endif( BUILD_EXPRESSION_DOCUMENTATION )






# end of build definition for expression
