rem Need Visual Studio 2013 Update 4.
set QMAKESPEC=msvc2013
set QTVERSION=5.3
PATH=%PATH%;%HBDIR%/delivery/bin/Qt53_msvc2013_x86;%QTDIR%/%QTVERSION%/%QMAKESPEC%/bin
%QTDIR%/%QTVERSION%/%QMAKESPEC%/bin/qmake.exe -o HB_msvc2013.sln -spec win32-msvc2013 -recursive -tp vc HB.pro
start devenv.exe HB_msvc2013.sln