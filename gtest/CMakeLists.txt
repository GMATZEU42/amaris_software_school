include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_amaris test_logger.cpp)
target_link_libraries(test_amaris gtest_main)

set_target_properties(test_amaris PROPERTIES FOLDER "test")
set_target_properties(gtest PROPERTIES FOLDER "test/googletest")
set_target_properties(gtest_main PROPERTIES FOLDER "test/googletest")
set_target_properties(gmock PROPERTIES FOLDER "test/googletest")
set_target_properties(gmock_main PROPERTIES FOLDER "test/googletest")