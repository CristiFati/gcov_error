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
    target_link_libraries(Test
        PUBLIC LLVMCore
    )
endif()
