# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      log-viewer
PROJECT.NAME =		HbLogViewer
PROJECT.TYPE =		app

#QRC_FILE  =             $${PROJECT.NAME}

# ------------
# QT Settings
# ------------

QT *= gui widgets

# -----------------
# Modules Settings
# -----------------

HB  += tools log

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
