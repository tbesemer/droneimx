#!/bin/sh

TREE_ROOT=`pwd`
if [ ! -d $TREE_ROOT/yocto/poky/build ]
then
    echo "Need to be in ~/sdk, with ~/sdk/yocto/poky/build"
    exit 1
fi

cd $TREE_ROOT/yocto/poky/
pwd


. ./oe-init-build-env

bitbake core-image-minimal 
if [ $? -ne 0 ]
then
    echo "bitbake core-image-minimal FAILED"
    exit 1
fi

bitbake core-image-minimal -c populate_sdk
if [ $? -ne 0 ]
then
    echo "bitbake core-image-minimal -c populate_sdk FAILED"
    exit 1
fi


exit 0

