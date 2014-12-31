# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =          plugin
PROJECT.NAME =		HbPlugin
PROJECT.TYPE =		staticlib

# ------------
# Qt Settings
# ------------

QT *=		gui widgets

# -----------------
# Modules Settings
# -----------------

HB +=		tools logger

# -------------
# C++ Settings
# -------------


# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
