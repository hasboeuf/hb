TEMPLATE = subdirs

SUBDIRS += \
    plugin-interfaces/HbPluginInterfaces.pro \
    plugins/plugin1/HbPlugin1.pro \
    plugins/plugin2/HbPlugin2.pro \
    plugin-demo/HbPluginDemo.pro \

plugins.depends = plugin-interfaces
plugin-demo.depends = plugin-interfaces plugins
