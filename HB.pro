# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HB
PROJECT.TYPE =			subdirs

SUBDIRS += \
    tools/HbTools.pro \
    log/HbLog.pro \
    plugin/HbPlugin.pro \
    link/HbLink.pro \
    network/HbNetwork.pro \
    tools-example/HbToolsExample.pro \    
    log-viewer/HbLogViewer.pro \
    plugin-example/HbPluginExample.pro \
    link-example/HbLinkExample.pro \    
    network-example/HbNetworkExample.pro \
    network-basic-example/HbNetworkBasicExample.pro

log.depends = tools
plugin.depends = tools log
link.depends = tools log
network.depends = tools log link
tools-example.depends = tools log
log-viewer.depends = tools log
plugin-example.depends = tools log plugin
link-example.depends = tools log link
network-example.depends = tools log link network
network-basic-example.depends = tools log link network

# ---------------
# QMake Includes
# ---------------

!include( $${PROJECT.NAME}.pri ): \
error( "QMake file $${PROJECT.NAME}.pri not found" )
