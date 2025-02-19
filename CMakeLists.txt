cmake_minimum_required(VERSION 3.28)

project(skycli)

set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

add_library(${PROJECT_NAME}
    "src/command.cpp"
    "src/cli.cpp"
    "src/typing.cpp"
    "src/parser.cpp"
    "src/help_message.cpp"
)

include_directories(/usr/include/readline)
target_link_libraries(${PROJECT_NAME} readline)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    LINKER_LANGUAGE CXX
    CMAKE_CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
)

# Install the library
include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(TARGETS skycli
    EXPORT skycli-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES 
    "include/command.hpp" 
    "include/cli.hpp" 
    "include/typing.hpp" 
    "include/parser.hpp" 
    "include/command_macros.hpp" 
    "include/static_var_holder.hpp"
    "include/static_var_macros.hpp" 
    "include/help_message.hpp"
    "include/skycli.hpp" 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(EXPORT skycli-targets
    FILE skycli-targets.cmake
    NAMESPACE skycli::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/skycli-config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/skycli-config.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Setup tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(runTests
    test/test_parser.cpp
)

target_link_libraries(runTests gtest gtest_main pthread ${PROJECT_NAME})