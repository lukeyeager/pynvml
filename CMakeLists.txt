cmake_minimum_required(VERSION 2.8.12)
project(pynvml)

add_subdirectory(pybind11)
pybind11_add_module(pynvml src/main.cpp)

# nvml.h
find_package(CUDA 7.0 REQUIRED)
target_include_directories(pynvml PUBLIC ${CUDA_INCLUDE_DIRS})

# libnvidia-ml
find_library(NVML_LIB nvidia-ml
    HINTS ${CUDA_TOOLKIT_ROOT_DIR}
    PATH_SUFFIXES lib/stubs lib64/stubs)
if(NOT NVML_LIB)
    message(FATAL "libnvidia-ml not found")
else()
    target_link_libraries(pynvml PUBLIC ${NVML_LIB})
endif()
