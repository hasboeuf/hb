# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   = log-viewer
PROJECT.DIR  = log-viewer
PROJECT.NAME = HbLogViewer
PROJECT.TYPE = app

# ------------
# QT Settings
# ------------

QT *= widgets xml network

# -----------------
# Modules Settings
# -----------------

HB  += tools log

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
