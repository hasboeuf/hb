# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID      = plugin1
PROJECT.NAME    = HbPlugin1
PROJECT.DIR     = plugin1
PROJECT.INTDIR  = plugin-example/plugins
PROJECT.INSTALL = plugin-example/plugins
PROJECT.QT      =
PROJECT.TYPE    = dynlib

OTHER_FILES += Plugin1.json

# ------------
# Qt Settings
# ------------

CONFIG *= plugin

# -----------------
# Modules Settings
# -----------------

HB += plugin-interfaces plugin log tools

# -------------
# C++ Settings
# -------------

# -----------------
# Install Settings
# -----------------

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
