include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(test_amaris)
add_subdirectory(test_school)

# Now simply link against gtest or gtest_main as needed. Eg
#[[
file(GLOB AMARIS_TEST "amaris_test/*.cpp" )
add_executable(test_amaris test_logger.cpp test_console.cpp)
target_link_libraries(test_amaris gtest_main amaris)

include_directories(../amaris/include)

target_compile_features(test_amaris PUBLIC cxx_std_17)

set_target_properties(test_amaris PROPERTIES FOLDER "test")
set_target_properties(test_amaris PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "--gtest_filter=*.*")

#
file(GLOB SCHOOL_TEST "school_test/*.cpp" )
add_executable(test_school test_prime.cpp)
target_link_libraries(test_amaris gtest_main school)
]]


# Set filter-folder for gtest projects
set_target_properties(gtest PROPERTIES FOLDER "test/googletest")
set_target_properties(gtest_main PROPERTIES FOLDER "test/googletest")
set_target_properties(gmock PROPERTIES FOLDER "test/googletest")
set_target_properties(gmock_main PROPERTIES FOLDER "test/googletest")

