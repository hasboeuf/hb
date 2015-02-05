# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   = link-example
PROJECT.DIR  = link-example
PROJECT.NAME = HbLinkExample
PROJECT.TYPE = app

# ------------
# QT Settings
# ------------

QT *= widgets xml network script

# -----------------
# Modules Settings
# -----------------

HB  += link

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
