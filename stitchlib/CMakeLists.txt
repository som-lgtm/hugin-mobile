# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("stitchlib")

include_directories(./src/main/cpp/include)

#libopencv_java4.so
add_library(libopencv_java4 SHARED IMPORTED)
set_target_properties(libopencv_java4 PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libopencv_java4.so)

#libceleste.so
add_library(libceleste SHARED IMPORTED)
set_target_properties(libceleste PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libceleste.so)

#libcpfind.so
add_library(libcpfind SHARED IMPORTED)
set_target_properties(libcpfind PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libcpfind.so)

#libhuginbase.so
add_library(libhuginbase SHARED IMPORTED)
set_target_properties(libhuginbase PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libhuginbase.so)

#libjpeg.so
add_library(libjpeg SHARED IMPORTED)
set_target_properties(libjpeg PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libjpeg.so)

#libktsitch.so
add_library(libktsitch SHARED IMPORTED)
set_target_properties(libktsitch PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libktstitch.so)

#liblocalfeatures.so
add_library(liblocalfeatures SHARED IMPORTED)
set_target_properties(liblocalfeatures PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/liblocalfeatures.so)

#libomd.so
#add_library(libomd SHARED IMPORTED)
#set_target_properties(libomd PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libomd.so)

#libpano13.so
add_library(libpano13 SHARED IMPORTED)
set_target_properties(libpano13 PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libpano13.so)

#libpng.so
add_library(libpng SHARED IMPORTED)
set_target_properties(libpng PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libpng.so)

#libtiff.so
add_library(libtiff SHARED IMPORTED)
set_target_properties(libtiff PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libtiff.so)
##libfmt.so
#add_library(libfmt SHARED IMPORTED)
#set_target_properties(libfmt PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libfmt.so)
##libspdlog.so
#add_library(libspdlog SHARED IMPORTED)
#set_target_properties(libspdlog PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libspdlog.so)
#libvigraimpex.so
add_library(libvigraimpex SHARED IMPORTED)
set_target_properties(libvigraimpex PROPERTIES IMPORTED_LOCATION ../../../../libs/${ANDROID_ABI}/libvigraimpex.so)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        ./src/main/cpp/stitchlib.cpp)
 find_library(cpp_shared_lib c++_shared)
# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
# 查找 OpenMP
find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${OpenMP_CXX_FLAGS})
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OpenMP_CXX_LIBRARIES})
else()
    message(WARNING "OpenMP not found")
endif()
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        libopencv_java4
        libceleste
        libcpfind
       libhuginbase
        libjpeg
        libktsitch
        liblocalfeatures
       # libomd
        libpano13
        libpng
        libtiff
        libvigraimpex
        ${cpp_shared_lib}
        omp
        android
        log)