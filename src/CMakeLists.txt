find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNFC_NCI REQUIRED libnfc-nci)

add_executable(nci-test main.cpp)

include_directories(${LIBNFC_NCI_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
SET(CMAKE_C_FLAGS_DEBUG "-g -O0")

target_link_libraries(nci-test ${LIBNFC_NCI_LIBRARIES})
target_compile_options(nci-test PRIVATE ${LIBNFC_NCI_CFLAGS_OTHER})
target_include_directories(nci-test PUBLIC ${PROJECT_SOURCE_DIR}/src)