md build-xlnt
cd build-xlnt

set cmake="C:\Program Files\CMake\bin\cmake.exe"
set cmake_generator="Visual Studio 15 2017"

call %cmake% -G %cmake_generator% ../ext/xlnt-1.3.0
call %cmake% --build . --config Release

cd ..
copy build-xlnt\source\Release\* .