# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		../../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      plugin2
PROJECT.NAME =		HbPlugin2
PROJECT.TYPE =		dynlib

OTHER_FILES += Plugin2.json

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
DEFINES +=

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
