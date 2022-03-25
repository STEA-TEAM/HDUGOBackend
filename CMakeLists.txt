cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "Vcpkg target triplet" FORCE)

project(HDUGOBackend CXX)

set(CMAKE_CXX_STANDARD 20)
message(STATUS "use c++20")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "Using Clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "Using GCC")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message(STATUS "Using Intel C++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "Using Visual Studio C++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /MP")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()

add_executable(${PROJECT_NAME} main.cc)

aux_source_directory(controllers CTL_SRC)
aux_source_directory(databases DB_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(services SVC_SRC)
aux_source_directory(utils UTIL_SRC)

find_package(cryptopp CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_package(LibXml2 CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(HdugoCore REQUIRED PATHS C:/dev/packages)

target_link_libraries(${PROJECT_NAME} PRIVATE
        cryptopp-static
        Drogon::Drogon
        LibXml2::LibXml2
        OpenSSL::SSL
        OpenSSL::Crypto
        HdugoCore::HdugoCore)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
        ${CMAKE_CURRENT_BINARY_DIR})
# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
        ${CTL_SRC}
        ${DB_SRC}
        ${FILTER_SRC}
        ${MODEL_SRC}
        ${PLUGIN_SRC}
        ${SVC_SRC}
        ${UTIL_SRC})
# ##############################################################################
# uncomment the following line for dynamically loading views 
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)
