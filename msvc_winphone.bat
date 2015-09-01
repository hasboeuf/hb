rem Need Visual Studio 2013 Update 4.
set QMAKESPEC=winphone_arm
set QTVERSION=5.5
set OUTPUT=HB_winphone_arm.sln
set HBSTATIC=1
%QTDIR%/%QTVERSION%/%QMAKESPEC%/bin/qmake.exe -o %OUTPUT% -spec winphone-arm-msvc2013 -r -tp vc HB.pro