cmake_minimum_required(VERSION 3.14)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(YGM-Tutorial
        VERSION 0.1
        DESCRIPTION "YGM Tutorial"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)


#
#  Threads
#
find_package(Threads REQUIRED)


#
# Boost
include(setup_boost)
prepare_fetchcontent_boost()
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        Boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.78.0
        GIT_SUBMODULES ${BOOST_REQD_SUBMODULES}
        GIT_PROGRESS TRUE
        CONFIGURE_COMMAND ""  # tell CMake it's not a cmake project
)
FetchContent_MakeAvailable(Boost)
get_boost_include_dirs()

# #
# #  cereal
# find_package(cereal QUIET)
# if (NOT cereal_FOUND)
#     set(JUST_INSTALL_CEREAL TRUE)
#     FetchContent_Declare(cereal
#             GIT_REPOSITORY https://github.com/USCiLab/cereal.git
#             GIT_TAG master
#             )
#     FetchContent_MakeAvailable(cereal)
# endif ()


#
#  MPI
find_package(MPI)

#
#  YGM
if (MPI_CXX_FOUND)
    find_package(YGM QUIET)
    if (NOT YGM_FOUND)
        set(JUST_INSTALL_YGM TRUE)
        FetchContent_Declare(YGM
            GIT_REPOSITORY https://github.com/llnl/ygm.git
            GIT_TAG v0.8-dev
                )
        FetchContent_MakeAvailable(YGM)
    endif ()
endif ()


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
    if (NOT MPI_CXX_FOUND)
        message(WARNING "YGM requires MPI; skip building ${exe_name}.")
        return()
    endif ()

    target_link_libraries(${exe_name} PRIVATE MPI::MPI_CXX)
    target_link_libraries(${exe_name} PRIVATE cereal)
    target_link_libraries(${exe_name} PRIVATE Threads::Threads)
    if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
        target_link_libraries(${exe_name} PRIVATE rt)
    endif ()
    target_link_libraries(${exe_name} PRIVATE ygm::ygm)
endfunction()

function(add_tutorial_executable name)
    add_executable(${name} ${name}.cpp)
    add_common_compile_options(${name})
    target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/include ${BOOST_INCLUDE_DIRS})
    target_link_libraries(${name} PRIVATE Boost::json)
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
