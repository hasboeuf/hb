TEMPLATE = subdirs

SUBDIRS += \
    lib/HbNetwork.pro \
    sample/HbNetworkExample.pro \
    basic-sample/HbNetworkBasicExample.pro \

sample.depends = lib
basic-sample.depends = lib
