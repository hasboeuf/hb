# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HbNetworkBasicExample
PROJECT.TYPE =			subdirs

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    network-basic-common/HbNetworkBasicCommon.pro \
    network-basic-server/HbNetworkBasicServer.pro \
    network-basic-user/HbNetworkBasicUser.pro

network-basic-server.depends = tools log network network-basic-common
network-basic-user.depends = tools log network network-basic-common

# ---------------
# QMake Includes
# ---------------

