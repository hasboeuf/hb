# ----------------
# Module Settings
# ----------------

MODULE.NAME = HB
MODULE.PATH = ../..

# -----------------
# Project Settings
# -----------------

PROJECT.ID = plugin-interfaces

# ------------
# Qt Settings
# ------------


# -----------------
# Modules Settings
# -----------------

HB += plugin tools

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
