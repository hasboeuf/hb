# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

SUBDIRS += config \
           facebook \
           facebook/api \
           google \
           google/api \

# ------------
# Qt Settings
# ------------

# -----------------
# Modules Settings
# -----------------

hb += HbLog HbTools

# -------------
# C++ Settings
# -------------
DEFINES += HB_LINK_SHARED

# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
