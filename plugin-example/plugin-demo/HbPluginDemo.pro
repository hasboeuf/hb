# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =          plugin-demo
PROJECT.NAME =		HbPluginDemo
PROJECT.TYPE =		app

# ------------
# QT Settings
# ------------

QT *= gui widgets

# -----------------
# Modules Settings
# -----------------

HB  += tools log plugin plugin-interfaces

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
