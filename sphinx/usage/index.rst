Usage
=====

Download
--------

Releases
^^^^^^^^

Official releases can be obtained from `GitHub Releases <https://github.com/fornellas/eglib/releases>`_ page.

.. code:: bash

  tar zxf eglib-$VERSION.tar.gz
  cd eglib-$VERSION/


Development Version
^^^^^^^^^^^^^^^^^^^

The development version can be obtained by cloning the Git repository:

.. code:: bash

  git clone https://github.com/fornellas/eglib.git
  cd eglib/

The cloned repository is not a full release, thus, it does not contain the required autotools files, which must be generated:

.. code:: bash

  # First install Autotools dependencies, please see for details:
  # https://github.com/fornellas/eglib/blob/master/.github/workflows/build.yml
  # then:
  ./autogen.sh

This should give you a working ``configure`` script.

Configure & Compile
-------------------

eglib is built with `GNU Autotools <https://en.wikipedia.org/wiki/GNU_Autotools>`_, meaning it works with the ubiquitous ``./configure && make`` pattern. As it supports multiple hardware architectures and SDKs, it must be configured and compiled for each particular use case.

Please choose a supported build target below. If your use case is not here yet, please check :doc:`../hacking/index` and learn how to extend eglib.

.. toctree::
   :maxdepth: 4
   :caption: Build targets:

   libopencm3/index.rst

Installing (optional)
---------------------

eglib can be simply used directly from within where ``make`` was called, where ``libeglib.a``, headers, documentation & binaries will be available.

Optionally, ``make install`` can be called to install eglib somewhere else.

Tip: it is strongly advised to do ``./configure --prefix=/somewhere/eglib/$eglib_build_target`` if you intent to install it. As eglib can be compiled for various architectures, it may only make sense to have it installed to a "system path" such as  ``/usr/local/lib/libeglib.a`` when it is a native build. Also, beware of different projects using different compiler flags and referring a common ``libeglib.a`` with potentially different flags.

Using
-----

You must compile your code with some extra flags, pointing the compiler to where eglib is.

If you're using eglib complied directly at the source tree ``$EGLIB_SRC_PATH``, then:

.. code:: bash

  EGLIB_INCLUDE_PATH=$EGLIB_SRC_PATH
  EGLIB_LIB_PATH=$EGLIB_SRC_PATH

if you installed eglib, then you must point to where it was installed, usually:

.. code:: bash

  EGLIB_INCLUDE_PATH=$PREFIX/include
  EGLIB_LIB_PATH=$PREFIX/lib


then compile your code with:

.. code:: bash

  CPPFLAGS=-I$EGLIB_INCLUDE_PATH
  LIBS=-leglib -Wl,--start-group -lm -Wl,--end-group
  LDFLAGS=$EGLIB_LIB_PATH

So that when you do:

.. code:: c

  #include <eglib.h>

the compiler can find the eglib headers and when linking, it'll find ``libeglib.a``.