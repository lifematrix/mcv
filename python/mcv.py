
import platform
import ctypes
from numpy.ctypeslib import ndpointer
import numpy as np


__all__ = ['gas_blur']

def _load_lib():
    lib_fname = "libmcv"
    sys_name = platform.system()
    if sys_name == "Linux":
        lib_fname += ".so"
    elif sys_name == "Darwin":
        lib_fname += ".dylib"
    else:
        raise EnvironmentError("Unkonw system of platform: %s" % sys_name)

    lib_fname = "../build/" + lib_fname
    print("load library form: %s" % lib_fname)
    return ctypes.cdll.LoadLibrary(lib_fname)

__lib = _load_lib()

_gas_blur_func = __lib.c_gas_blur
_gas_blur_func.restype = None
_gas_blur_func.argtypes = [
    ndpointer(np.float32, ndim=3, flags="C_CONTIGUOUS"),
    #ctypes.c_void_p,
    ctypes.c_size_t,
    ctypes.c_size_t,
    ctypes.c_size_t,
    ctypes.c_float,
    ndpointer(np.float32, ndim=3, flags="C_CONTIGUOUS")]
    # ctypes.c_void_p,]

def gas_blur(img, sigma):
    if img.flags['C_CONTIGUOUS'] != True:
        raise ValueError("numpy array should be C_CONTIGUOUS")

    if len(img.shape) == 3:
        n_channels = img.shape[2]
    else:
        n_channels = 1

    print("n_channels: %d" % n_channels)
    dest = np.zeros(img.shape, dtype=np.float32)
    _gas_blur_func(img, img.shape[0], img.shape[1], n_channels, sigma, dest)

    return dest
