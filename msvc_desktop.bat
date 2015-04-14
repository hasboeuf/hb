set QMAKESPEC=msvc2013
set QTVERSION=5.4
set OUTPUT=HB_msvc2013.sln
set HBSTATIC=1
PATH=%PATH%;%HBDIR%/delivery/bin/Qt54_%QMAKESPEC%_x86;%QTDIR%/%QTVERSION%/%QMAKESPEC%/bin
%QTDIR%/%QTVERSION%/%QMAKESPEC%/bin/qmake.exe -o %OUTPUT% -spec win32-msvc2013 -recursive -tp vc HB.pro
start devenv.exe %OUTPUT%