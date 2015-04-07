# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   = tools-example
PROJECT.DIR  = tools-example
PROJECT.NAME = HbToolsExample
PROJECT.TYPE = app

# ------------
# QT Settings
# ------------

QT *= gui widgets xml network

# -----------------
# Modules Settings
# -----------------

HB  += tools log

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
