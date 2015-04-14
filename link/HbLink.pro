# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.ID = link

SUBDIRS += config \
           facebook \
           facebook/api

# ------------
# Qt Settings
# ------------

# -----------------
# Modules Settings
# -----------------

HB += log tools

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
