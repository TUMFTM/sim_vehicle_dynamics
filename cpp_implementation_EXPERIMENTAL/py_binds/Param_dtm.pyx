STUFF = "Hi"
cimport cParam_dtm

cdef class Param_dtm:
    cdef cParam_dtm.Parameters_dtm* _c_param_dtm

    def __cinit__(self):
        self._c_param_dtm = cParam_dtm.param_dtm_new()
        if self._c_param_dtm is NULL:
            raise MemoryError()

    def __dealloc__(self):
        if self._c_param_dtm is not NULL:
            cParam_dtm.param_dtm_free(self._c_param_dtm)

    def setParameters(self):
        if self._c_param_dtm is not NULL:
            cParam_dtm.setParameters(self._c_param_dtm)
