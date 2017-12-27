TEMPLATE = subdirs

SUBDIRS += \
    network-basic-common/HbNetworkBasicCommon.pro \
    network-basic-server/HbNetworkBasicServer.pro \
    network-basic-user/HbNetworkBasicUser.pro

network-basic-server.depends = network network-basic-common
network-basic-user.depends = network network-basic-common
