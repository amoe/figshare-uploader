# upgraded-fortnight

To build: `scons`

To test: `./unit_tests`

To clean: `scons -c`

## Building on Linux

You need scons and xlnt installed.

To install scons, use `pip3 install scons`, or use your distro's copy of scons.
The build process was tested with SCons versions 2.5.1 and 3.0.1.

It's easier to use a systemwide copy of xlnt.

You also need the appropriate Qt5 dev packages for your distribution.  This is
often provided by the top level package `qt5-default` in Debian and derivatives.

Once you have these, run `scons` to build.
You should get a binary `./main` in the current directory.

## Building on Windows

The build on Windows is rather elaborate.

There are several steps:

### Build the bundled xlnt

You need CMake.

You do this something like so:

    cd ext/xlnt-1.2.0
    md build
    cd build
    cmake -G "Visual Studio 15 2017 Win64" ..
    cmake --build . --config Release

Now you will find the files you are looking for under `source/Release`
directory.

To use those to build this program, you must copy them to the root of the source
tree -- the same directory as this README file.  There should be around five
`xlnt` files.


### Build this program 

Now to build this program, you need to already have the Qt developer version
installed.  It's normally installed to a directory that looks something like this
`C:\Qt\5.9.3\msvc2017_64`.

You also need Python 3 (any version, but 3 is needed) and SCons 3.0.1.  You must
use that SCons version as that's the only one that supports Python 3.

You should install scons using pip.

Once you have this you do:

    scons qt5_dir=C:\Qt\5.9.3\msvc2017_64

Using the correct directory for your Qt installation.  scons has no way to detect
the root of the Qt installation in Windows (it can do so in Linux).

You also need [Windows OpenSSL
binaries](http://slproweb.com/products/Win32OpenSSL.html).  Use the version
`Win64 OpenSSL v1.0.2n`.  Then you need the libs `ssleay32.dll` and
`libeay32.dll` from this package.

You can build the app using `windeployqt` to get the various Qt DLLs into the
current directory.  By default this will copy far too many files, but at least
it will work.

    windeployqt --release main.exe

So now you should have all the run-time requirements resolved, by copying these
DLLs into the source directory:

* Qt libraries
* OpenSSL libraries
* xlnt libraries

Now it should be able to run.

