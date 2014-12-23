# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      tools
PROJECT.NAME =		HbTools
PROJECT.TYPE =		dynlib

SUBDIRS += core

# ------------
# Qt Settings
# ------------

QT *=		gui widgets

# -----------------
# Modules Settings
# -----------------


# -------------
# C++ Settings
# -------------
DEFINES += HB_TOOLS_BUILD

# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
