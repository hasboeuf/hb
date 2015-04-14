# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.ID   =      tools

SUBDIRS += core \
           network

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------


# -------------
# C++ Settings
# -------------
DEFINES += HB_TOOLS_SHARED

# -----------------
# Install Settings
# -----------------


# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )
