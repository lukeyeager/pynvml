from __future__ import print_function

import sys

import pytest

import pynvml as m


if sys.version_info[0] == 2:
    string_types = basestring,
else:
    string_types = str,


def setup_module():
    m.nvmlInit()


def teardown_module():
    m.nvmlShutdown()


def test_driver_version():
    v = m.nvmlSystemGetDriverVersion()
    assert isinstance(v, string_types)
    assert len(v) > 0


def test_nvml_version():
    v = m.nvmlSystemGetDriverVersion()
    assert isinstance(v, string_types)
    assert len(v) > 0


def test_get_all_names():
    device_count = m.nvmlDeviceGetCount()
    for index in range(device_count):
        handle = m.nvmlDeviceGetHandleByIndex(index)
        name = m.nvmlDeviceGetName(handle)
        assert isinstance(name, string_types)
        assert len(name) > 0
