#@!/bin/sh

TREE_ROOT=`pwd`
if [ ! -d$TREE_ROOT/yocto ]
then
    echo "Need to be in ~/sdk, with ~/sdk/yocto."
    exit 1
fi

cd $TREE_ROOT/yocto
if [ $? -ne 0 ]
then
    echo "Can't CD into $TREE_ROOT/yocto"
    exit 1

fi

if [ ! -d poky ]
then
    git clone -b morty git://git.yoctoproject.org/poky.git
fi

if [ ! -d meta-freescale-3rdparty ]
then
    git clone -b morty https://github.com/Freescale/meta-freescale-3rdparty.git
fi

if [ ! -d meta-freescale ]
then
    git clone -b morty https://github.com/Freescale/meta-freescale.git
fi

if [ ! -d meta-freescale-distro ]
then
    git clone -b morty https://github.com/Freescale/meta-freescale-distro.git
fi

if [ ! -d meta-openembedded ]
then
    git clone -b morty https://github.com/openembedded/meta-openembedded.git
fi

cd poky; . ./oe-init-build-env
cd $CWD
 
exit 0
