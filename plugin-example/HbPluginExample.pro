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

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    plugin-interfaces/HbPluginInterfaces.pro \
    plugin-demo/HbPluginDemo.pro \
    plugins/HbPlugins.pro

plugin-demo.depends = plugin-interfaces plugins
plugins.depends = plugin-interfaces

# ---------------
# QMake Includes
# ---------------

