cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("Cooper")

set(CMAKE_CXX_STANDARD 11)


function(cooper_tests test_name)
    add_executable(${test_name}_exec ${test_name}.cpp)
    add_test(NAME ${test_name} COMMAND ${test_name}_exec)
    target_compile_features(${test_name}_exec
        PRIVATE
            cxx_auto_type
        PUBLIC
            cxx_nullptr
            cxx_override
    )
endfunction()

cooper_tests(config_test)
