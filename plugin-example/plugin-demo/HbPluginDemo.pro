# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID      = plugin-demo
PROJECT.NAME    = HbPluginDemo
PROJECT.DIR     = plugin-demo
PROJECT.INTDIR  = plugin-example
PROJECT.INSTALL = plugin-example
PROJECT.QT      = gui widgets
PROJECT.TYPE    = app

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------

HB += plugin-interfaces plugin log tools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
