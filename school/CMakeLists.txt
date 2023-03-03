file(GLOB INCLUDES_LIST "include/*.h" )
file(GLOB SOURCES_LIST "src/*.cpp" )

include_directories(include)
include_directories(../amaris/include)

add_executable(school ${SOURCES_LIST} ${INCLUDES_LIST})

target_link_libraries(school PUBLIC amaris)
target_compile_features(school PUBLIC cxx_std_17)
