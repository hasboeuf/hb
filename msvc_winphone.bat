rem Need Visual Studio 2013 Update 4.
set QMAKESPEC=winphone_arm
set QTVERSION=5.4
set OUTPUT=HB_winphone_arm.sln
PATH=%PATH%;%HBDIR%/delivery/bin/Qt54_%QMAKESPEC%_x86;%QTDIR%/%QTVERSION%/%QMAKESPEC%/bin
%QTDIR%/%QTVERSION%/%QMAKESPEC%/bin/qmake.exe -o %OUTPUT% -spec winphone-arm-msvc2013 -recursive -tp vc HB.pro
start devenv.exe %OUTPUT%