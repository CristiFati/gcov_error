cmake_minimum_required(VERSION 3.2)
project(gcov_test)

find_package(LLVM 7.0.0 REQUIRED CONFIG)
message(STATUS "Found LLVM: ${LLVM_DIR} ${LLVM_PACKAGE_VERSION}")

add_executable(test
        "main.cpp"
)

target_compile_features(test
        PUBLIC
        cxx_std_17
)

target_include_directories(test
        PUBLIC
        ${LLVM_INCLUDE_DIRS}
)

target_compile_definitions(test
        PUBLIC
        ${LLVM_DEFINITIONS}
)

if(LINK_WITH_LLVM)
        target_link_libraries(test
                PUBLIC
                LLVMCore
        )
endif()