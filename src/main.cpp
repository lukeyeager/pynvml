#include <pybind11/pybind11.h>
#include <nvml.h>

namespace py = pybind11;

#define NVML_CHECK(condition) \
    do { \
        nvmlReturn_t status = condition; \
        if (status != NVML_SUCCESS) \
            throw std::runtime_error(nvmlErrorString(status)); \
    } while (0)

constexpr unsigned int STRMAX = 255;

PYBIND11_MODULE(pynvml, m) {
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    // Initialization and Cleanup

    m.def("nvmlInit", []() { NVML_CHECK(nvmlInit()); });
    m.def("nvmlShutdown", []() { NVML_CHECK(nvmlShutdown()); });

    // System Queries

    m.def("nvmlSystemGetDriverVersion", []() {
        char version[STRMAX];
        NVML_CHECK(nvmlSystemGetDriverVersion(version, STRMAX));
        return std::string(version);
    });
    m.def("nvmlSystemGetNVMLVersion", []() {
        char version[STRMAX];
        NVML_CHECK(nvmlSystemGetNVMLVersion(version, STRMAX));
        return std::string(version);
    });

    // Device Queries

    m.def("nvmlDeviceGetCount", []() {
        unsigned int deviceCount;
        NVML_CHECK(nvmlDeviceGetCount(&deviceCount));
        return deviceCount;
    });
    m.def("nvmlDeviceGetHandleByIndex", [](unsigned int index) {
        nvmlDevice_t device;
        NVML_CHECK(nvmlDeviceGetHandleByIndex(index, &device));
        return (void*)device;
    });
    m.def("nvmlDeviceGetName", [](void* handle) {
        nvmlDevice_t device = (nvmlDevice_t)handle;
        char name[STRMAX];
        NVML_CHECK(nvmlDeviceGetName(device, name, STRMAX));
        return std::string(name);
    });
}
