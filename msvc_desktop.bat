set QMAKESPEC=msvc2013_64
set QTVERSION=5.7
set QTCOMPILED=msvc2013_64
set HBSTATIC=1
%QTDIR%/%QTVERSION%/%QTCOMPILED%/bin/qmake.exe -r -spec win32-msvc2013 -tp vc HB.pro