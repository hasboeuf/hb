# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../../..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME    = HbPluginDemo
PROJECT.DIR     = plugin-example/plugin-demo
#PROJECT.INTDIR  = plugin-example
#PROJECT.INSTALL = plugin-example
PROJECT.QT      = gui widgets
PROJECT.TYPE    = app

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------

hb += HbPluginInterfaces HbPlugin HbLog HbTools

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
