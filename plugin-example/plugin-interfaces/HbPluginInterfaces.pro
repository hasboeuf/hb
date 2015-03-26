# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      plugin-interfaces
PROJECT.NAME =      HbPluginInterfaces
PROJECT.TYPE =      staticlib

# ------------
# Qt Settings
# ------------

QT *=

# -----------------
# Modules Settings
# -----------------

HB += tools plugin

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
