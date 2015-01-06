# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HbNetworkExample
PROJECT.TYPE =			subdirs

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    network-server/HbNetworkServer.pro \
    network-user/HbNetworkUser.pro

network-server.depends = tools log network
network-user.depends = tools log network

# ---------------
# QMake Includes
# ---------------

