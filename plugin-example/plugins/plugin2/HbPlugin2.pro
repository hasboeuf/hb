# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID      = plugin2
PROJECT.NAME    = HbPlugin2
PROJECT.DIR     = plugin2
PROJECT.INTDIR  = plugin-example/plugins
PROJECT.INSTALL = plugin-example/plugins
PROJECT.QT      =
PROJECT.TYPE    = dynlib

OTHER_FILES += Plugin2.json

# ------------
# Qt Settings
# ------------

QT *=
CONFIG *= plugin

# -----------------
# Modules Settings
# -----------------

HB += plugin-interfaces plugin log tools

# -------------
# C++ Settings
# -------------
DEFINES +=

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
