#!/bin/sh

if [ $# -ne 1 ]
then
    echo "Directory arg missing."
    exit 1
fi

DELIVERY_PATH=$1
cd $DELIVERY_PATH
SO_PATH=$(pwd)

sudo mkdir -p /etc/ld.so.conf.d
sudo touch /etc/ld.so.conf.d/hb.conf

sudo sh -c "echo $SO_PATH > /etc/ld.so.conf.d/hb.conf"

sudo ldconfig
