# ----------------
# Module Settings
# ----------------

MODULE.NAME = hb
MODULE.PATH = ..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME = HbPluginExample
PROJECT.TYPE = subdirs

SUBDIRS += \
    plugin-interfaces/HbPluginInterfaces.pro \
    plugin-demo/HbPluginDemo.pro \
    plugins/HbPlugins.pro

plugin-demo.depends = plugin-interfaces plugins
plugins.depends = plugin-interfaces

# ---------------
# QMake Includes
# ---------------

!include( $${MODULE.PATH}/$${MODULE.NAME}.pri ): \
error( "QMake file $${MODULE.NAME}.pri not found" )

