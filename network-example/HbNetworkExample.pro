# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME =            HbNetworkExample
PROJECT.TYPE =            subdirs

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    network-common/HbNetworkCommon.pro \
    network-server/HbNetworkServer.pro \
    network-user/HbNetworkUser.pro

network-server.depends = network network-common
network-user.depends = network network-common

# ---------------
# QMake Includes
# ---------------

