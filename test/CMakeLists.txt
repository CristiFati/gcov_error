cmake_minimum_required(VERSION 3.2)

add_executable(Test
        "src/test.cpp"
        "src/main.cpp"
)

set_target_properties(Test
        PROPERTIES OUTPUT_NAME "suite"
)

target_link_libraries(Test
        PRIVATE
        STELA
)
