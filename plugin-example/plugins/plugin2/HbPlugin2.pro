# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../../..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME    = HbPlugin2
PROJECT.DIR     = plugin-example/plugins/plugin2
#PROJECT.INTDIR  = plugin-example/plugins
#PROJECT.INSTALL = plugin-example/plugins
PROJECT.QT      =
PROJECT.TYPE    = dynlib

OTHER_FILES += Plugin2.json

# ------------
# Qt Settings
# ------------

QT *=
CONFIG *= plugin

# -----------------
# Modules Settings
# -----------------

hb += HbPluginInterfaces HbPlugin HbLog HbTools

# -------------
# C++ Settings
# -------------
DEFINES +=

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
