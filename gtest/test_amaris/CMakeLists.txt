add_executable(test_amaris test_logger.cpp test_console.cpp)
target_link_libraries(test_amaris gtest_main amaris)

include_directories(../../amaris/include)

target_compile_features(test_amaris PUBLIC cxx_std_17)

set_target_properties(test_amaris PROPERTIES FOLDER "test")
set_target_properties(test_amaris PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=*.*")