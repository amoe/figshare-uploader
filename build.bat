SET scons_path="C:/Program Files/Python3/Scripts/scons.bat"
SET qt5_dir=C:/Qt/5.11.3/msvc2017_64
SET windeployqt_path=%qt5_dir%/bin/windeployqt.exe
SET openssl_path=C:/OpenSSL-Win64

REM The clean command is below.
REM %scons_path% -c qt5_dir=%qt5_dir%

echo %windeployqt_path%

call %scons_path% qt5_dir=%qt5_dir%

rmdir /s /q package
call %windeployqt_path% --dir package --release build/main.exe

copy /y "build\main.exe" "package\figshare-uploader.exe"
copy /y xlnt.dll package\xlnt.dll
copy /y %openssl_path%/libeay32.dll package\libeay32.dll
copy /y %openssl_path%/ssleay32.dll package\ssleay32.dll
copy /y %openssl_path%/libssl32.dll package\libssl32.dll
