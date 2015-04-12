set QMAKESPEC=winphone_arm
set QTVERSION=5.4
%QTDIR%/%QTVERSION%/%QMAKESPEC%/bin/qmake.exe -o HB_winphone_arm.sln -spec winphone-arm-msvc2013 -recursive -tp vc HB.pro
start devenv.exe HB_winphone_arm.sln