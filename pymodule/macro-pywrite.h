//-----------------------------------------------------------------*- c++ -*-
// Macro for wrapping around ..._pywrite functions
//---------------------------------------------------------------------------
// Author: Cedric Adjih
//---------------------------------------------------------------------------
// Copyright 2011-2017 Inria
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//---------------------------------------------------------------------------

#ifndef __MACRO_PYWRITE_H__
#define __MACRO_PYWRITE_H__

//---------------------------------------------------------------------------
// [march 2013] extracted from WSNColor/pkg-python/HipSens/Core/hipsens.i
//---------------------------------------------------------------------------

//#ifdef WITH_FILE_IO
#define WRAP_CALL(function, out, arg_var)   (function)((out), (arg_var))
//#elif defined(WITH_PRINTF)
//#define WRAP_CALL(function, out, arg_var)	\
//  function(0, arg_var);			\
//  fprintf(out, "<not available>");		
//#else /* !defined(WITH_FILE_IO) && !defined(WITH_PRINTF) */
//#define WRAP_CALL(function, out, arg_var)    fprintf(out, "<not available>")
//#endif /* WITH_FILE_IO */

#ifndef __APPLE__
  /* for Linux and the rest... */
#define WRAP_PYWRITE(name, function, arg_type)				\
  PyObject* name(arg_type arg_var) {					\
    char* data = NULL;							\
    size_t size;							\
    FILE* out = open_memstream(&data, &size);				\
    if (out == NULL) {							\
      PyErr_SetString(PyExc_RuntimeError, "error opening memory file");	\
      return NULL;							\
    }									\
    WRAP_CALL(function, out, arg_var);					\
    fclose(out);							\
    PyObject* result = PyString_FromStringAndSize(data, size);		\
    free(data);								\
    return result;							\
  }
#else /* __APPLE__ */
#warning "Using RamDisk hack instead of open_memstream"
#define RAMDISK_PATH "/Volumes/RamDisk"
#define WRAP_PYWRITE(name, function, arg_type)				\
  PyObject* name(arg_type arg_var) {					\
    char* data = NULL;							\
    FILE* out = fopen(RAMDISK_PATH "/tmp-file.dat", "w+b");		\
    if (out == NULL) {							\
      PyErr_SetFromErrnoWithFilename(PyExc_RuntimeError,		\
				     "<opening memory file>");		\
      return NULL;							\
    }									\
    WRAP_CALL(function, out, arg_var);					\
    fflush(out);							\
    long dataSize = ftell(out);						\
    if (dataSize < 0)							\
      return PyErr_SetFromErrnoWithFilename(PyExc_RuntimeError,		\
					    "<ftell memory file>");	\
    rewind(out);							\
    data = (char*)malloc(dataSize);					\
    fread(data, dataSize, 1, out);					\
    PyObject* result = PyString_FromStringAndSize(data, dataSize);	\
    free(data);								\
    fclose(out);							\
    return result;							\
  }
#endif /* __APPLE__ */

//---------------------------------------------------------------------------

#endif /*__MACRO_PYWRITE_H__*/
