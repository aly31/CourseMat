cmake_minimum_required(VERSION 2.8.11)

project(pittPack)

#disable in source build
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

message(STATUS "cmake is building on a ${CMAKE_SYSTEM_NAME} system")
set(dir ${PROJECT_SOURCE_DIR})
message("project source dir" ${dir})

set(CMAKE_FILES_DIRECTORY ${dir}/build)
message("Files Directory" ${CMAKE_FILES_DIRECTORY})

#define some colors (Unix-based systems)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()


# get the number of physical procesors 

message("project binary dir" ${EXECUTABLE_OUTPUT_PATH})
message("CMAKE SOURCE DIR:" ${CMAKE_SOURCE_DIR})
message("CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})

# Out-of-Source build is required by amrGem, this if statement prevents
# in-source-builds 

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()


message("cmake Home Dir:" ${CMAKE_HOME_DIRECTORY})
message("cmake Build Dir:" ${CMAKE_BUILD_DIRECTORY})
message("cmake Binary Dir:" ${CMAKE_BINARY_DIR})
message("cmake source dir:" ${CMAKE_SOURCE_DIR})

# specify the path for Modules 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

#find HDF5
#find_package(HDF5 ${HDF5_MIN_VERSION} REQUIRED)
#if(HDF5_FOUND)
#include_directories(${HDF5_INCLUDE_DIRS})
#message( "${Red}HDF5 Library Found: ${ColourReset}" ${HDF5_INCLUDE_DIRS})
#message("${Green} HDF5 Library Found: ${ColourReset}")
#endif()

#find_package(MYMPI ${MPI_MIN_VERSION} REQUIRED)
#if(MPI_FOUND)
#include_directories(${MPI_INCLUDE_PATH})
#message( "${Red} MPI Include Path : ${ColourReset}" ${MPI_INCLUDES})
#message( "${Red} MPI Library Path : ${ColourReset}"  ${MPI_LIBRARIES})
#message("${Red} MPI Library Found : ${ColourReset}")
#endif()


# Define all header files for linking, this is required such that one doesnt
# have to hardcode the directories for I/O operations and hence ensure
# portability

#set(HEADER_FILES "${dir}/src/include/tridiag.h" "${dir}/src/include/statevector.h" "${dir}/src/include/fft.h" )

#set(HEADER_FILES  "${dir}/src/include/*")

message("header files" ${HEADER_FILES})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wno-unused-variable")

SET(CMAKE_EXEC_LINKER_FLAGS "${CMAKE_EXEC_LINKER_FLAGS}   -Wno-unused-variable -Wno-unknown-pragmas -Wno-sign-compare " )

message(${RED} ${CMAKE_CXX_FLAGS} ${ColourReset} )

# Generate Object Files

add_executable(PittPack ${OBJ} ${HEADER_FILES})

#add_library()

# do not forget to link external libraries here 
#if(!GPU)
target_link_libraries(PittPack ${HDF5_LIBRARIES} ${FFTW_LIB} ${MPI_LIBRARIES} )

# st OFF to ON to enable documaneting
option(BUILD_DOCUMENTATION "Use Doxygen to create the HTML based API documentation" OFF)
if(BUILD_DOCUMENTATION)
  FIND_PACKAGE(Doxygen)

  if (NOT DOXYGEN_FOUND)
    message(FATAL_ERROR
      "Doxygen is needed to build the documentation. Please install it
correctly")
endif()

  add_custom_target (doc ALL
                     ${DOXYGEN_EXECUTABLE}
${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
                     )

endif()
