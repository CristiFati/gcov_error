cmake_minimum_required(VERSION 3.9)
project(STELA)

find_package(Git REQUIRED)
find_package(LLVM 7.0.0 REQUIRED CONFIG)
message(STATUS "Found LLVM: ${LLVM_DIR} ${LLVM_PACKAGE_VERSION}")

add_library(STELA STATIC
        "src/lib.cpp"
        "include/STELA/lib.hpp"
)

target_include_directories(STELA
        INTERFACE
        include
        PUBLIC
        ${LLVM_INCLUDE_DIRS}
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/STELA>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${SOURCE_DIR}
)

target_compile_definitions(STELA
        PUBLIC
        ${LLVM_DEFINITIONS}
)

llvm_map_components_to_libnames(llvm_libs core native mcjit asmprinter asmparser linker instrumentation vectorize ipo)

target_link_libraries(STELA
        PUBLIC
        ${llvm_libs}
)

target_compile_features(STELA
        PUBLIC
        cxx_std_17
)

if(TEST_COVERAGE)
        set(CMAKE_CXX_FLAGS "-DNDEBUG -DTEST_COVERAGE -O0 --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
endif()

add_subdirectory(test)