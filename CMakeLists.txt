cmake_minimum_required(VERSION 3.2)
project(gcov_test)

find_package(LLVM 7.0.0 REQUIRED CONFIG)
message(STATUS "Found LLVM: ${LLVM_DIR} ${LLVM_PACKAGE_VERSION}")

add_executable(Test
    "main.cpp"
)

target_compile_features(Test
    PUBLIC cxx_std_17
)

target_include_directories(Test
    PUBLIC ${LLVM_INCLUDE_DIRS}
)

target_compile_definitions(Test
    PUBLIC ${LLVM_DEFINITIONS}
)

message(INFO " CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES0: " ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})
message(INFO " CMAKE_CXX_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES: "${CMAKE_CXX_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES})
message(INFO " CMAKE_CXX_IMPLICIT_LINK_LIBRARIES: "${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})


if(LINK_WITH_LLVM)
    # Everything till target_link_libraries is to avoid hardcoding default libgcc path (/usr/lib/gcc/x86_64-linux-gnu/7)
    set(_COLLECT_LTO_WRAPPER_TEXT "COLLECT_LTO_WRAPPER=")
    execute_process(
        COMMAND bash -c "$0 -v 2>&1 | grep ${_COLLECT_LTO_WRAPPER_TEXT} | sed s/${_COLLECT_LTO_WRAPPER_TEXT}//" "${CMAKE_CXX_COMPILER}"
        OUTPUT_VARIABLE _COLLECT_TMP_VAR
    )
    get_filename_component(_GAINARIE_GCC_DEFAULT_PATH ${_COLLECT_TMP_VAR} DIRECTORY)
    message(INFO " _GAINARIE_GCC_DEFAULT_PATH: " ${_GAINARIE_GCC_DEFAULT_PATH})
    set(CMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} -L${_GAINARIE_GCC_DEFAULT_PATH}0)
    link_directories(BEFORE
        ${_GAINARIE_GCC_DEFAULT_PATH}1
    )
    target_link_libraries(Test
        PUBLIC LLVMCore
    )
    link_directories(BEFORE
        ${_GAINARIE_GCC_DEFAULT_PATH}2
    )
endif()
