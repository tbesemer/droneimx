#!/bin/sh

ROOT_DIR=`pwd`

if [ ! -d $ROOT_DIR/hal ]
then
    echo "$ROOT_DIR/hal: Missing, run from ~/app/mpu9250"
    exit 1
fi

if [  -d $ROOT_DIR/RTIMULib2 ]
then
    echo "$ROOT_DIR/RTIMULib2: Exist, Not CLoning"
    exit 0
fi


git clone https://github.com/tbesemer/RTIMULib2.git
cd RTIMULib2
git checkout -b droneimx

exit 0

