cmake_minimum_required(VERSION 3.11)

project(test_ci_cd VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(consts.h.in ${PROJECT_SOURCE_DIR}/consts.h)

add_executable(ci_cd_exe main.cpp)

add_library(ci_cd lib.cpp lib.h)

add_executable(tests test_ver.cpp)

set_target_properties(ci_cd_exe ci_cd tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

message (STATUS ${Boost_INCLUDE_DIR})

set_target_properties(tests PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ci_cd_exe
    ci_cd
    Threads::Threads
)

target_link_libraries(tests
    ${Boost_LIBRARIES}
    ci_cd
)

install(TARGETS ci_cd_exe RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ms.sopkova@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(ci_cd_test tests)
