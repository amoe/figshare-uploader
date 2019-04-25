# Build process documentation

To build: `scons`

To test: `./unit_tests`

To clean: `scons -c`

## Building on Linux

You need scons and xlnt installed.

To install scons, use `pip3 install scons`, or use your distro's copy of scons.
The build process was tested with SCons versions 2.5.1 and 3.0.1.

It's easier to use a systemwide copy of xlnt, for which you'll also need cmake.
You can also use the copy under `ext` directory.

You also need the appropriate Qt5 dev packages for your distribution.  This is
often provided by the top level package `qt5-default` in Debian and derivatives.

Once you have these, run `scons` to build.
You should get a binary produced `./build/main`.

## Building on Mac

You need:

* Homebrew
* Python 3 - `brew install python3`
* xlnt
* SCons - `pip3 install scons`
* Qt5 - `brew install qt5`
* pkg-config - `brew install pkg-config`

By default, Brew will install qt5 to `/usr/local/opt/qt`.  Take a note of this
path.

### Building xlnt

There's no brew package for xlnt yet, so you'll have to install it yourself.
Luckily this works identically to the standard Linux build instructions.

### Building the program itself

You need to export the correct environment variables for pkg-config to work:

    amoe@somemac $ export PKG_CONFIG_PATH=/usr/local/opt/qt/lib/pkgconfig
    amoe@somemac $ scons qt5_dir=/usr/local/opt/qt

You should automatically get an OSX 'bundle' built under the `build`
subdirectory.

## Building on Windows

The build on Windows is rather elaborate.

There are several steps:

### Build the bundled xlnt

You need CMake.  My CMake executable ended up at `C:\Program
Files\CMake\bin\cmake.exe`.  You can set a shell variable to this path as such:

    CMAKE="/c/Program Files/CMake/bin/cmake.exe"

You do this something like so:

    cd ext/xlnt-1.3.0
    md build
    cd build
    cmake -G "Visual Studio 15 2017 Win64" ..
    cmake --build . --config Release

Now you will find the files you are looking for under `source/Release`
directory.

To use those to build this program, you must copy them to the root of the source
tree -- the same directory as this README file.  I found files
`xlnt.{dll,exp,lib}`.


### Build this program 

Now to build this program, you need to already have the Qt developer version
installed.  It's normally installed to a directory that looks something like this
`C:\Qt\5.9.3\msvc2017_64`.

You also need Python 3 (any version, but 3 is needed) and SCons 3.0.1.  You must
use that SCons version as that's the only one that supports Python 3.

You should install scons using pip.
Before you install SCons, you should upgrade the following packages:

    python -m pip install -U pip
    pip install -U setuptools
    pip install -U wheel
    pip install scons

This avoids an error `--single-version-externally-managed`.  SCons will put its
scripts into the `Scripts` directory of your Python directory.  You may need to
fully qualify the path to SCons with this path.  Scons will install a batch file
`scons.bat` that you can invoke.  Note that this will not tab-complete in
git-bash by default.  On my system, the path in git-bash looks like `/c/Program
Files/Python3/Scripts/scons.bat`.

You can assign it to a variable like this:

    SCONS="/c/Program Files/Python3/Scripts/scons.bat"

Then make sure that you quote it when you use it, like `"$SCONS"`.

Once you have this you do:

    scons qt5_dir=C:\Qt\5.9.3\msvc2017_64

Using the correct directory for your Qt installation.  scons has no way to detect
the root of the Qt installation in Windows (it can do so in Linux).

Note that you should not try to do this within git-bash.  For some reason
scons fails to detect moc when it's invoked through git-bash.  Instead, use
standard Windows `cmd`.

You also need [Windows OpenSSL
binaries](http://slproweb.com/products/Win32OpenSSL.html).  Use the version
`Win64 OpenSSL v1.0.2n`.  (Now tested with version `q` also.)  Then you need the
libs `ssleay32.dll` and `libeay32.dll` from this package.  The default install
location for that package is `C:\OpenSSL-Win64`.  Choose the install option to
copy the DLLs to the OpenSSL binary directory, then you'll be able to find them
more easily.  They should be copied into the source tree.

You can build the app using `windeployqt` to get the various Qt DLLs into the
current directory.  By default this will copy far too many files, but at least
it will work.

    windeployqt --release build\main.exe

So now you should have all the run-time requirements resolved, by copying these
DLLs into the source directory:

* Qt libraries
* OpenSSL libraries
* xlnt libraries

These files are:

* `xlnt.dll`
* `ssleay32.dll`
* `libeay32.dll`

Now it should be able to run.

Yow! x7
