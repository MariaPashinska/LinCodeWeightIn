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


add_executable(testScalar_WeightDistribution TestScalar.cpp)
target_link_libraries (testScalar_WeightDistribution PRIVATE v1.3)


add_executable(testScalar_MinimumDistance TestScalar_MinimumDistance.cpp)  
target_link_libraries (testScalar_MinimumDistance PRIVATE v1.3)


add_executable(testScalar_SearchEqual TestScalar_SearchEqual.cpp)
target_link_libraries (testScalar_SearchEqual PRIVATE v1.3)


add_executable(testScalar_SearchLessThan TestScalar_SearchLessThan.cpp)
target_link_libraries (testScalar_SearchLessThan PRIVATE v1.3)



add_executable(testScalar_CountEqual TestScalar_CountEqual.cpp)
target_link_libraries (testScalar_CountEqual PRIVATE v1.3)


add_executable(testScalar_CountLessThan TestScalar_CountLessThan.cpp)
target_link_libraries (testScalar_CountLessThan PRIVATE v1.3)




#install(TARGETS test DESTINATION ${PROJECT_SOURCE_DIR}/ExampleFiles)