cmake_minimum_required(VERSION 2.8)

#
#project(aws-cpp-cognito-auth)

# Locate the AWS SDK for C++ package.
# If you've built and installed the AWS SDK CPP Package then 
# name of the package you're looking for is AWSSDK
#
# Otherwise if you're linking to a development project then use
# aws-sdk-cpp
set(AWS_SDK_PACKAGE_NAME aws-sdk-cpp CACHE STRING "Name of AWS SDK CPP package to look for")
if(NOT UNIX)
	set(AWS_SDK_HOME d:/lib/aws-sdk-cpp-1.4.9 CACHE PATH "AWS SDK install dir")
    set(OPEN_SSL_HOME d:/lib/OpenSSL-Win64 CACHE PATH "OPEN SSL DIR" )
endif()






add_subdirectory(src/aws-cpp-cognito-auth)
set(BUILD_DEMO true CACHE BOOL "Create project files for the demo")
if( ${BUILD_DEMO} )
	add_subdirectory(src/aws-cpp-cognito-auth-demo)
endif()