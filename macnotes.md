Install xcode.  On el capitan you must install xcode 8.2.1 which is the last
version to be compatible with El Capitan.  I installe dint ona mac mini.  You
also need scons.

install python3

brew install qt5  -- don't use official thing as it doesn't bundle pkg-config
pc files that wre required by the thing.



PKG_CONFIG_PATH /usr/local/opt/qt/lib/pkgconfig

LDFLAGS /usr/local/opt/qt/lib
CPPFLAG /usr/local/opt/qt/include

qt is linked into /usr/local/opt/qt

brew install cmake
you need to disable werror with some clang version

Once you've installed xcode you need to visit preferences > locations in xcode
and change the location of the Command LIne Tools in the dropdown.c


## Install on mfm017633 -- Mac OS X Sierra

You also need pkg-config

Handling xlnt:

* brew install cmake
* cmake .
* make
* make install

The process of packaging for mac os x: Everything is called a 'bundle'.

otool(1) is something like ld but for Mac.

otool -L /usr/local/opt/qt/Frameworks/QtGui.framework/QtGui

There is also `install_name_tool`

However, `macdeployqt` does exist.

Macdeployqt requires a bundle as input, though...

http://scons.1086193.n5.nabble.com/scons-users-Bundles-for-Mac-td17052.html
http://scons-users.scons.narkive.com/D69pF4YX/scons-and-os-x
https://github.com/Araq/Claro/blob/master/macosx/osxbundle.py
https://github.com/SCons/scons/wiki
http://scons.1086193.n5.nabble.com/scons-users-Mac-OS-X-Bundles-td17045.html
