TEMPLATE =  subdirs
SUBDIRS += 	plugin-demo \
                plugin-interfaces \
                plugins

plugin-demo.depends = plugin-interfaces plugins
plugins.depends = plugin-interfaces
