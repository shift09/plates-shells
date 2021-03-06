# version requirement
cmake_minimum_required(VERSION 3.10)

# use gcc 9.2 for c++ 17
# set(CMAKE_C_COMPILER "gcc-9")
# set(CMAKE_CXX_COMPILER "g++-9")

# project name
project(plates_shells)
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../")

# all source codes
file(GLOB source_files
    "${PROJECT_ROOT}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${PROJECT_ROOT}/include/*.h")

# include directories, and header files
include_directories("/usr/local/include")
include_directories("${PROJECT_ROOT}/include")

# compiler settings
set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

# generate executable file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT})
add_executable(plates_shells ${source_files})

# Mac OS
if(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    message("=====Building on Mac OS=====")
    # lapack
    find_package(LAPACK REQUIRED)
    # Pardiso
    find_library(
        PARDISO_LIB
        NAMES libpardiso600-MACOS-X86-64 pardiso600-MACOS-X86-64
        HINTS "${PROJECT_ROOT}/lib"
        NO_DEFAULT_PATH
    )
    message(STATUS "PARDISO_LIB: [${PARDISO_LIB}]")
    find_library(
        OMP_LIB
        NAMES libiomp5 iomp5
        HINTS "${PROJECT_ROOT}/lib"
        NO_DEFAULT_PATH
    )
    message(STATUS "OMP_LIB: [${OMP_LIB}]")
    # link libraries
    target_link_libraries(plates_shells ${PARDISO_LIB} ${LAPACK_LIBRARIE} ${OMP_LIB})

# Linux Ubuntu
elseif(${CMAKE_SYSTEM_NAME} MATCHES Linux)
    message("=====Building on Linux Ubuntu=====")
    # linking directories
    link_directories(
                    /usr/lib/x86_64-linux-gnu
                    /usr/lib/x86_64-linux-gnu/lapack
                    /usr/lib/gcc/x86_64-linux-gnu/7.4.0)
    # lapack
    find_package(LAPACK REQUIRED)
    # Pardiso
    find_library(
        PARDISO_LIB
        NAMES libpardiso600-GNU720-X86-64 pardiso600-GNU720-X86-64
        HINTS "${PROJECT_ROOT}/lib"
        NO_DEFAULT_PATH
    )
    message(STATUS "PARDISO_LIB: [${PARDISO_LIB}]")
    # OpenMP
    find_package(OpenMP REQUIRED)
    if (OPENMP_FOUND)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    endif()
    # gfortran
    find_library(
        FORTRAN_LIB
        NAMES libgfortran gfortran
        HINTS "/usr/lib/gcc/x86_64-linux-gnu/7.4.0"
        NO_DEFAULT_PATH
    )
    message(STATUS "FORTRAN_LIB: [${FORTRAN_LIB}]")
    # POXIS thread
    find_package(Threads REQUIRED)
    set(pthread ${CMAKE_THREAD_LIBS_INIT})

    target_link_libraries(plates_shells ${PARDISO_LIB} ${LAPACK_LIBRARIES} ${FORTRAN_LIB} pthread)
endif()