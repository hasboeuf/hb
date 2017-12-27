TEMPLATE = subdirs

SUBDIRS += \
    lib/HbLog.pro \
    viewer/HbLogViewer.pro \

viewer.depends = lib
