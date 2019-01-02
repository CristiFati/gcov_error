cmake_minimum_required(VERSION 3.2)
project(gcov_test)

find_package(LLVM 7.0.0 REQUIRED CONFIG)
message(STATUS "Found LLVM: ${LLVM_DIR} ${LLVM_PACKAGE_VERSION}")

add_executable(Test
        "main.cpp"
)

target_compile_definitions(Test
        PUBLIC
        ${LLVM_DEFINITIONS}
)

llvm_map_components_to_libnames(llvm_libs core)

target_link_libraries(Test
        PUBLIC
        ${llvm_libs}
)

target_include_directories(Test
        PUBLIC
        ${LLVM_INCLUDE_DIRS}
)

target_compile_features(Test
        PUBLIC
        cxx_std_17
)

set_target_properties(Test
        PROPERTIES OUTPUT_NAME "test"
)