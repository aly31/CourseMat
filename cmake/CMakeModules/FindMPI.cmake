
## the key factor is to check for the exact environment variable before we check that one 
## do module show in crc as see what is the exact spelling for it

set( MPI_ROOT $ENV{MPI_ROOT} )
# note that the MPI shoulb be build under PGI 
message("MPI" ${MPI_ROOT})

# Check if we can use PkgConfig
find_package(PkgConfig)

#Determine from PKG
if( PKG_CONFIG_FOUND AND NOT MPI_ROOT )
  pkg_check_modules( PKG_MPI QUIET "mpi" )
endif()

#Check whether to search static or dynamic libs
set( CMAKE_FIND_LIBRARY_SUFFIXES_SAV ${CMAKE_FIND_LIBRARY_SUFFIXES} )

message("Suffixes"  ${CMAKE_FIND_LIBRARY_SUFFIXES})

 find_library(
    MPI_LIB
    NAMES "libmpi.so"
    PATHS ${MPI_ROOT}
    PATH_SUFFIXES "lib" "lib64"
    NO_DEFAULT_PATH
)

  find_path(
    MPI_INCLUDES
    NAMES "mpi.h"
    PATHS ${MPI_ROOT}/include
    PATH_SUFFIXES "include"
    NO_DEFAULT_PATH
  )


set(MPI_LIBRARIES ${MPI_LIB})

if(MPIL_LIB)
  set(MPI_LIBRARIES ${MPI_LIBRARIES} ${MPIL_LIB})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MPI DEFAULT_MSG
                                  MPI_INCLUDES MPI_LIBRARIES)

mark_as_advanced(MPI_INCLUDES MPI_LIBRARIES )


