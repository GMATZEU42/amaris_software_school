add_executable(test_school test_prime.cpp)
target_link_libraries(test_school gtest_main)

include_directories(../../school/include)
include_directories(../../school/src)

target_compile_features(test_amaris PUBLIC cxx_std_17)

set_target_properties(test_school PROPERTIES FOLDER "test")
set_target_properties(test_school PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=*.*")