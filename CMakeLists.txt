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

if(LINK_WITH_LLVM)
    # @TODO - cfati: Everything in this block is to avoid hardcoding default libgcc path (/usr/lib/gcc/x86_64-linux-gnu/7)
    set(_COLLECT_LTO_WRAPPER_TEXT "COLLECT_LTO_WRAPPER=")
    execute_process(
        COMMAND bash -c "$0 -v 2>&1 | grep ${_COLLECT_LTO_WRAPPER_TEXT} | sed s/${_COLLECT_LTO_WRAPPER_TEXT}//" "${CMAKE_CXX_COMPILER}"
        OUTPUT_VARIABLE _GAINARIE_COLLECT_TMP_VAR
    )
    get_filename_component(_GAINARIE_GCC_DEFAULT_PATH ${_GAINARIE_COLLECT_TMP_VAR} DIRECTORY)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${_GAINARIE_GCC_DEFAULT_PATH}")
    #set (GCCOPT "${GCCOPT} -L${_GAINARIE_GCC_DEFAULT_PATH}")
    # @TOTO END
    target_link_libraries(Test
        PUBLIC LLVMCore
    )
endif()
