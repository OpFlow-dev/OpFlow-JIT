# ----------------------------------------------------------------------------
# MLIR dialect target
# ----------------------------------------------------------------------------
add_subdirectory(lang/dialect)

# ----------------------------------------------------------------------------
# Lib target
# ----------------------------------------------------------------------------
file(GLOB_RECURSE OPFLOW_SRC *.cpp)
add_library(OpFlow-JIT SHARED ${OPFLOW_SRC})
add_library(OpFlow::OpFlow-JIT ALIAS OpFlow-JIT)

target_include_directories(OpFlow-JIT PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(OpFlow-JIT 
    PRIVATE spdlog::spdlog
    OpLang
    MLIRIR MLIRParser MLIRSupport
    MLIROptLib        # w.r.t. #include "mlir/Tools/mlir-opt/MlirOptMain.h"
    MLIRFuncDialect   # w.r.t. #include "mlir/Dialect/Func/IR/FuncOps.h"
    MLIRTransforms    # w.r.t. #include "mlir/Transforms/Passes.h"
    )

# ----------------------------------------------------------------------------
# Language & library features detection
# ----------------------------------------------------------------------------
include(CheckIncludeFiles)
check_include_files("sys/mman.h" HAS_SYS_MMAN_H)
if (HAS_SYS_MMAN_H)
    target_compile_definitions(OpFlow-JIT INTERFACE OPFLOW_HAS_MMAN_H)
endif ()

if (OPFLOW_NO_EXCEPTIONS AND NOT MSVC)
    target_compile_options(OpFlow-JIT INTERFACE -fno-exceptions)
endif ()

# ----------------------------------------------------------------------------
# Platform detection
# ----------------------------------------------------------------------------
if (UNIX)
    target_compile_definitions(OpFlow-JIT INTERFACE OPFLOW_PLATFORM_UNIX)
elseif (APPLE)
    target_compile_definitions(OpFlow-JIT INTERFACE OPFLOW_PLATFORM_APPLE)
elseif (WIN32)
    target_compile_definitions(OpFlow-JIT INTERFACE OPFLOW_PLATFORM_WIN)
endif ()

# sanitizer flags
target_compile_options(OpFlow-JIT
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_ADDRESS}>: -fsanitize=address>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_LEAK}>: -fsanitize=leak>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_THREAD}>: -fsanitize=thread>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_UB}>: -fsanitize=undefined>)
target_link_options(OpFlow-JIT
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_ADDRESS}>: -fsanitize=address>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_LEAK}>: -fsanitize=leak>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_THREAD}>: -fsanitize=thread>
        PRIVATE $<$<BOOL:${OPFLOW_SANITIZE_UB}>: -fsanitize=undefined>)

# ----------------------------------------------------------------------------
# Install
# ----------------------------------------------------------------------------
if (OPFLOW_INSTALL)
    message(STATUS "Generating install")
    IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        SET(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}" CACHE PATH "" FORCE)
        message(STATUS "Install prefix set to: ${CMAKE_INSTALL_PREFIX}")
    ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(project_config_in "${CMAKE_CURRENT_LIST_DIR}/../cmake/OpFlowConfig.cmake.in")
    set(project_config_out "${CMAKE_CURRENT_BINARY_DIR}/OpFlowConfig.cmake")
    set(config_targets_file "OpFlowConfigTargets.cmake")
    set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/OpFlowConfigVersion.cmake")
    set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/OpFlow-JIT")
    set(pkgconfig_install_dir "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
    set(pkg_config "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc")

    # ----------------------------------------------------------------------------
    # Include files
    # ----------------------------------------------------------------------------
    install(
            TARGETS OpFlow-JIT
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    # ----------------------------------------------------------------------------
    # Install CMake config files
    # ----------------------------------------------------------------------------
    #install(EXPORT OpFlow-JIT DESTINATION ${export_dest_dir} NAMESPACE OpFlow-JIT:: FILE ${config_targets_file})

    include(CMakePackageConfigHelpers)
    configure_file("${project_config_in}" "${project_config_out}" @ONLY)

    write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
    install(FILES "${project_config_out}" "${version_config_file}" DESTINATION "${export_dest_dir}")

    # ----------------------------------------------------------------------------
    # Support creation of installable packages
    # ----------------------------------------------------------------------------
    #include(cmake/opflowCPack.cmake)
endif ()