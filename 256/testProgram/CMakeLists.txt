#source app
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	configure_file( ${PROJECT_SOURCE_DIR}/testFiles/TestDataBig ${CMAKE_BINARY_DIR}/build/Debug/TestDataBig COPYONLY)
	configure_file( ${PROJECT_SOURCE_DIR}/testFiles/TestDataSmall ${CMAKE_BINARY_DIR}/build/Debug/TestDataSmall COPYONLY)
	configure_file( ${PROJECT_SOURCE_DIR}/testFiles/ArticleData ${CMAKE_BINARY_DIR}/build/Debug/ArticleData COPYONLY)
	configure_file( ${PROJECT_SOURCE_DIR}/testFiles/TestDataBig ${CMAKE_BINARY_DIR}/build/Release/TestDataBig COPYONLY)
	configure_file( ${PROJECT_SOURCE_DIR}/testFiles/TestDataSmall ${CMAKE_BINARY_DIR}/build/Release/TestDataSmall COPYONLY)
	configure_file( ${PROJECT_SOURCE_DIR}/testFiles/ArticleData ${CMAKE_BINARY_DIR}/build/Release/ArticleData COPYONLY)

else()
	configure_file( ${PROJECT_SOURCE_DIR}/testFiles/TestDataBig ${CMAKE_BINARY_DIR}/build/TestDataBig COPYONLY)
	configure_file( ${PROJECT_SOURCE_DIR}/testFiles/TestDataSmall ${CMAKE_BINARY_DIR}/build/TestDataSmall COPYONLY)
		configure_file( ${PROJECT_SOURCE_DIR}/testFiles/ArticleData ${CMAKE_BINARY_DIR}/build/ArticleData COPYONLY)
endif()


if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(Test-UI Source.cpp)
target_link_libraries (Test-UI PRIVATE v1.3)


add_executable(test256_WeightDistribution Test256.cpp)
target_link_libraries (test256_WeightDistribution PRIVATE v1.3)


add_executable(test256_MinimumDistance Test256_MinimumDistance.cpp)
target_link_libraries (test256_MinimumDistance PRIVATE v1.3)


add_executable(test256_SearchEqual Test256_SearchEqual.cpp)
target_link_libraries (test256_SearchEqual PRIVATE v1.3)

add_executable(test256_SearchLessThan Test256_SearchLessThan.cpp)
target_link_libraries (test256_SearchLessThan PRIVATE v1.3)

add_executable(test256_CountEqual Test256_CountEqual.cpp)
target_link_libraries (test256_CountEqual PRIVATE v1.3)

add_executable(test256_CountLessThan Test256_CountLessThan.cpp)
target_link_libraries (test256_CountLessThan PRIVATE v1.3)



#install(TARGETS test DESTINATION ${PROJECT_SOURCE_DIR}/ExampleFiles)