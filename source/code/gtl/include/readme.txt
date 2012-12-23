OpenGL 1.4 include files
========================

Overview
--------

These are OpenGL 1.4 and GLU 1.3 compatible include files based on the
Mesa 4.0.1 distribution. The files have been modified slightly in order to
fit a wide range of compilers, and to be independent of Mesa.


Installation
------------

Copy the files gl.h, glu.h and glext.h to your compilers include/GL
directory. If no GL directory exists in your include directory, create it
(note: "GL" should be with upper case). If you already have any of these
files in your include/GL directory, it may be wise to make a backup of
them.

The gl.h file has been adapted to the official glext.h file that can be
found at http://oss.sgi.com/projects/ogl-sample/ABI/glext.h

The supplied glext.h file (from 2002-Jul-18) can be replaced directly
by the above mentioned official glext.h file when new updates arrive.

NOTE: The glext.h file was modified in order to add support for
OpenGL 1.4, ARB_vertex_program and ARB_fragment_program (since the latest
official glext.h file did not include them). Therefore you should make
sure that any replacement glext.h file has that support before overwriting
the herein included file.



Note for Windows
----------------

For Windows, the OpenGL 1.2, 1.3 & 1.4 definitions are not made in gl.h
(as is done in the original Mesa gl.h file). Those definitions are made in
the glext.h file instead. The reason is that under Windows, OpenGL 1.2,
1.3 and 1.4 functionality is treated as extensions, and thus should be
defined as such. For other environments (e.g. Linux), OpenGL 1.2, 1.3 and
1.4 definitions are still made in the gl.h file.



Contact
-------

Please report any problems to: marcus.geelnard@home.se



Good luck!

   Marcus
