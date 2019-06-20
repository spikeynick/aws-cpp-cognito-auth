cmake_minimum_required(VERSION 2.8)

#
project(aws-cpp-cognito-auth)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" CACHE STRING "CXX FLAGS")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_LIST_DIR}/../../lib/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR} CACHE PATH "")


# Locate the AWS SDK for C++ package.
# If you've built and installed the AWS SDK CPP Package then 
# name of the package you're looking for is AWSSDK
#
# Otherwise if you're linking to a development project then use
# aws-sdk-cpp

set(AWS_SDK_PACKAGE_NAME aws-sdk-cpp CACHE STRING "Name of AWS SDK CPP package to look for")

find_package(${AWS_SDK_PACKAGE_NAME})

# AWS SDK
if(NOT UNIX)
	set(AWS_SDK_HOME d:/lib/aws-sdk-cpp-1.4.9 CACHE PATH "AWS SDK install dir")

	include_directories(
		${AWS_SDK_HOME}/include #If we're using an installed SDK
		${AWS_SDK_HOME}/aws-cpp-sdk-core/include #If we're using a development project SDK
		${AWS_SDK_HOME}/aws-cpp-sdk-cognito-identity/include #If we're using a development project SDK
		${AWS_SDK_HOME}/aws-cpp-sdk-cognito-idp/include #If we're using a development project SDK
	)
endif()

# Open SSL
if(NOT UNIX)
	set(OPEN_SSL_HOME d:/lib/OpenSSL-Win64 CACHE PATH "OPEN SSL DIR" )

	include_directories(
		${OPEN_SSL_HOME}/include
	)

#        link_directories (
#        ${AWS_SDK_HOME}/lib
#    )

    set(AWS_LIBS aws-cpp-sdk-access-management aws-cpp-sdk-cognito-identity aws-cpp-sdk-cognito-idp aws-cpp-sdk-config aws-cpp-sdk-core aws-cpp-sdk-iam )
  #  set(LIBS ${LIBS} ${AWS_LIBS})

endif()


# Link to the SDK shared libraries.
#add_definitions(-DUSE_IMPORT_EXPORT)


# The executable name and its sourcefiles
add_library(${PROJECT_NAME}
	Auth.cpp
	Srp.cpp
)
