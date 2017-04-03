
import ctypes
from numpy.ctypeslib import ndpointer
import numpy as np


__all__ = ['gas_blur']

__lib = ctypes.cdll.LoadLibrary("../build/libmcv.dylib")

_gas_blur_func = __lib.c_gas_blur
_gas_blur_func.restype = None
_gas_blur_func.argtypes = [
    ndpointer(np.float32, ndim=3, flags="C_CONTIGUOUS"),
    ctypes.c_size_t,
    ctypes.c_size_t,
    ctypes.c_size_t,
    ctypes.c_float,
    ndpointer(np.float32, ndim=3, flags="C_CONTIGUOUS")]

def gas_blur(img, sigma):
    if len(img.shape) == 3:
        n_channels = img.shape[2]
    else:
        n_channels = 1

    dest = np.zeros(img.shape, dtype=np.float32)
    _gas_blur_func(img, img.shape[0], img.shape[1], n_channels)

    return dest
