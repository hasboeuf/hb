TEMPLATE = subdirs

SUBDIRS += \
    lib/HbTools.pro \
    tests/tests.pro \

tests.depends = lib
