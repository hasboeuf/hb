# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HB
PROJECT.TYPE =			subdirs

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    tools/HbTools.pro \
    log/HbLog.pro \
	log-viewer/HbLogViewer.pro \
    network/HbNetwork.pro \
    plugin/HbPlugin.pro
    #plugin-example/HbPluginExample.pro
	
logger.depends = tools
network.depends = log tools    
plugin.depends = log tools
plugin-example.depends = plugin log tools

# ---------------
# QMake Includes
# ---------------

!include( $${PROJECT.NAME}.pri ): \
error( "QMake file $${PROJECT.NAME}.pri not found" )
