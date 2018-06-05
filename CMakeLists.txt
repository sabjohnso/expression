#
# ... Build script for expression
#

cmake_minimum_required( VERSION 3.1 )

project( EXPRESSION )

set( EXPRESSION_MAJOR  0 )
set( EXPRESSION_MINOR  1 )
set( EXPRESSION_UPDATE 0 )
set( EXPRESSION_VERSION expression-${EXPRESSION_MAJOR}.${EXPRESSION_MINOR} )
set( EXPRESSION_VERSION_UPDATE ${EXPRESSION_VERSION}.{EXPRESSION_UPDATE} )
  

option( BUILD_EXPRESSION_TESTING  "Build the expression  tests" ON )

include_directories( 
  ${EXPRESSION_SOURCE_DIR}
  ${EXPRESSION_BINARY_DIR} )

if( NOT EXPRESSION_INSTALL_INCLUDE_DIR )
  set( EXPRESSION_INSTALL_INCLUDE_DIR include/expression
    CACHE PATH "Path for installation of header files")
endif( NOT EXPRESSION_INSTALL_INCLUDE_DIR )

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
  
  if( NOT EXPRESSION_INSTALL_DOC_DIR )
    set( EXPRESSION_INSTALL_DOC_DIR share/${EXPRESSION_VERSION}
      CACHE PATH "Path for installation of documentation")
  endif( NOT EXPRESSION_INSTALL_DOC_DIR )

  if( NOT EXPRESSION_INSTALL_MAN_DIR )
    set( EXPRESSION_INSTALL_MAN_DIR share
      CACHE PATH "Path for installation of manual pages" )
  endif( NOT EXPRESSION_INSTALL_MAN_DIR )

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
