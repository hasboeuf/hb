# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   = log-viewer
PROJECT.DIR  = log-viewer
PROJECT.NAME = HbLogViewer
PROJECT.QT   = widgets xml network
PROJECT.TYPE = app

# ------------
# QT Settings
# ------------


# -----------------
# Modules Settings
# -----------------

HB += log tools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
