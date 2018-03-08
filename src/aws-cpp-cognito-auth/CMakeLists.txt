cmake_minimum_required(VERSION 2.8)

#
project(awspp)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_LIST_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})


# Locate the AWS SDK for C++ package.
find_package(aws-sdk-cpp)

# AWS SDK
if(NOT UNIX)
	set(AWS_SDK_HOME d:/lib/aws-sdk-cpp-1.4.9)

	include_directories(
		${AWS_SDK_HOME}/aws-cpp-sdk-core/include
		${AWS_SDK_HOME}/aws-cpp-sdk-cognito-identity/include
		${AWS_SDK_HOME}/aws-cpp-sdk-cognito-idp/include
		${AWS_SDK_HOME}/aws-cpp-sdk-dynamodb/include
		${AWS_SDK_HOME}/aws-cpp-sdk-s3/include
	)
endif()

set(LIBS
	aws-cpp-sdk-core
	aws-cpp-sdk-cognito-identity
	aws-cpp-sdk-cognito-idp
	aws-cpp-sdk-dynamodb
	aws-cpp-sdk-s3
)

# Open SSL
if(NOT UNIX)
	set(OPEN_SSL_HOME d:/lib/OpenSSL-Win64)

	include_directories(
		${OPEN_SSL_HOME}/include
	)

	link_directories(
		${OPEN_SSL_HOME}/lib/VC
	)

	set(LIBS
		${LIBS}
		libcrypto64MT
	)
endif()


# Link to the SDK shared libraries.
add_definitions(-DUSE_IMPORT_EXPORT)


# The executable name and its sourcefiles
add_library(${PROJECT_NAME}
	Auth.cpp
	Srp.cpp
)


# The libraries used by your executable.
# target_link_libraries(${PROJECT_NAME} ${LIBS})