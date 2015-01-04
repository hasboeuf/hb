# ----------------
# Module Settings
# ----------------

MODULE.NAME =		HB
MODULE.PATH =		..

# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HbPluginExample
PROJECT.TYPE =			subdirs

TEMPLATE = SUBDIRS
CONFIG += ordered

SUBDIRS += \
    plugin-demo/HbPluginDemo.pro \
    plugin-interfaces/HbPluginInterfaces.pro \
    plugins/HbPlugins.pro

plugin-demo.depends = plugin-interfaces plugins
plugins.depends = plugin-interfaces

# ---------------
# QMake Includes
# ---------------

