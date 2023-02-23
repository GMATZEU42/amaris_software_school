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

add_executable(amaris ${SOURCES_LIST} ${INCLUDES_LIST})


target_compile_features(amaris PUBLIC cxx_std_17)
