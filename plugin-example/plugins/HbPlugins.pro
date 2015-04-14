# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME =            HbPlugins
PROJECT.TYPE =            subdirs

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    plugin1/HbPlugin1.pro \
    plugin2/HbPlugin2.pro

# ---------------
# QMake Includes
# ---------------

