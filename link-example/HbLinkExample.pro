# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   = link-example
PROJECT.DIR  = link-example
PROJECT.NAME = HbLinkExample
PROJECT.QT   = gui widgets xml network
PROJECT.TYPE = app

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------

HB += link log tools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
