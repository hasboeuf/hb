# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME = HbLogViewer
PROJECT.QT   = widgets xml network
PROJECT.TYPE = app
PROJECT.DIR = log-viewer

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------

hb += HbLog HbTools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
