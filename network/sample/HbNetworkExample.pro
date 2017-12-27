TEMPLATE = subdirs

SUBDIRS += \
    network-common/HbNetworkCommon.pro \
    network-server/HbNetworkServer.pro \
    network-user/HbNetworkUser.pro

network-server.depends = network network-common
network-user.depends = network network-common
