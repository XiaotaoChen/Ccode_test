import cppimport
import sys
from pathlib import Path
import numpy as np 
# due to limits of cppimport, we need to temporarily append path
sys.path.append(str(Path(__file__).parent))

bind_cpp = cppimport.imp("bind")

sys.path.pop()

if __name__ == "__main__":
    arr = np.zeros((5, 2 ), dtype=np.float32)
    bind_cpp.add_scalar_fp32(arr, 2)
    print(arr)
    # if we call with wrong type, pybind11 will do implicit type
    # conversion and create a new copy. the inplace change no longer work.
    arr = np.zeros((5, 2 ), dtype=np.int32)
    bind_cpp.add_scalar_fp32(arr, 2)
    print(arr)
    bind_cpp.add_scalar_int32_nogil(arr, 2)
    print(arr)

