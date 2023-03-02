add_subdirectory(src)
add_subdirectory(include)

foreach(file ${SOURCES})
	set(file "src/${file}")
	list(APPEND SOURCES_LIST ${file})
endforeach()

foreach(file ${INCLUDES})
	set(file "include/${file}")
	list(APPEND INCLUDES_LIST ${file})
endforeach()

include_directories(include)

add_executable(school ${SOURCES_LIST} ${INCLUDES_LIST})

include_directories(../amaris/include)
target_link_libraries(school PUBLIC amaris)
target_compile_features(school PUBLIC cxx_std_17)
