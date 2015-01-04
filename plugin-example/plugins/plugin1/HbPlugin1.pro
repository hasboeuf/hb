# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		../../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      plugin1
PROJECT.NAME =		HbPlugin1
PROJECT.TYPE =		dynlib

OTHER_FILES += Plugin1.json

# ------------
# Qt Settings
# ------------

QT *=
CONFIG *= plugin

# -----------------
# Modules Settings
# -----------------

HB += plugin plugin-interfaces

# -------------
# C++ Settings
# -------------
DEFINES += HB_PLUGIN_BUILD

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
