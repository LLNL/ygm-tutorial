cmake_minimum_required(VERSION 3.14)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(YGM-Tutorial
        VERSION 0.9
        DESCRIPTION "YGM Tutorial"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

#
#  YGM
set(YGM_REQUIRE_PARQUET ON)
set(YGM_INSTALL_PARQUET ON)
FetchContent_Declare(YGM
    GIT_REPOSITORY https://github.com/llnl/ygm.git
    GIT_TAG v0.9-dev
        )
FetchContent_MakeAvailable(YGM)

#
# Faker
FetchContent_Declare(faker
    GIT_REPOSITORY https://github.com/cieslarmichal/faker-cxx
    GIT_TAG v4.0.1
        )
FetchContent_MakeAvailable(faker)


#
#  Common functions for all MetallData Executables
#
function(add_common_compile_options name)
    # Common
    #target_compile_options(${name} PRIVATE -Wall -Wextra -pedantic)

    # Debug
    target_compile_options(${name} PRIVATE $<$<CONFIG:Debug>:-O0>)
    target_compile_options(${name} PRIVATE $<$<CONFIG:Debug>:-g3>)
#    if (Linux)
#        target_compile_options(${name} PRIVATE $<$<CONFIG:Debug>:-pg>)
#    endif ()

    # Release
    target_compile_options(${name} PRIVATE $<$<CONFIG:Release>:-Ofast>)
    target_compile_options(${name} PRIVATE $<$<CONFIG:Release>:-DNDEBUG>)

    # Release with debug info
    target_compile_options(${name} PRIVATE $<$<CONFIG:RelWithDebInfo>:-Ofast>)
    target_compile_options(${name} PRIVATE $<$<CONFIG:RelWithDebInfo>:-g3>)
#    if (Linux)
#        target_compile_options(${name} PRIVATE $<$<CONFIG:RelWithDebInfo>:-pg>)
#    endif ()
endfunction()

#
# Function for setting up a target that uses YGM
#
function(setup_ygm_target exe_name)
    if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
        target_link_libraries(${exe_name} PRIVATE rt)
    endif ()
    target_link_libraries(${exe_name} PRIVATE ygm::ygm Boost::unordered Boost::container Boost::json)
endfunction()

function(add_tutorial_executable name)
    add_executable(${name} ${name}.cpp)
    add_common_compile_options(${name})
    target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/include ${BOOST_INCLUDE_DIRS})
    target_link_libraries(${name} PRIVATE Boost::json faker-cxx Parquet::parquet_shared Arrow::arrow_shared)
    setup_ygm_target(${name})
endfunction()

add_subdirectory(solutions)
add_subdirectory(exercises)
add_subdirectory(sandbox)
add_subdirectory(examples)

#
# Copy the testing data directory
#
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
