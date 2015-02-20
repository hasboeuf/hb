# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HbComExample
PROJECT.TYPE =			subdirs

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
	com-common/HbComCommon.pro \
    com-server/HbComServer.pro \
    com-user/HbComUser.pro

com-server.depends = tools log com com-common
com-user.depends = tools log com com-common

# ---------------
# QMake Includes
# ---------------

