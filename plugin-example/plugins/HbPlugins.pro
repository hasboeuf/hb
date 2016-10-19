# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME =            HbPlugins
PROJECT.TYPE =            subdirs

SUBDIRS += \
    plugin1/HbPlugin1.pro \
    plugin2/HbPlugin2.pro

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
