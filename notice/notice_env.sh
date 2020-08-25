#!/bin/bash

export NKHOME=$(cd "$(dirname "${BASH_ARGV[0]}")"; pwd)
echo $NKHOME

export LIBUSB_INC=/usr/include/libusb-1.0
export LIBUSB_LIB=/usr/lib64
#export LIBUSB_LIB=/usr/lib/x86_64-linux-gnu

source /cvmfs/sft.cern.ch/lcg/views/ROOT-latest/x86_64-slc6-gcc48-opt/setup.sh
ROOTHOME=/cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.06.08/x86_64-slc6-gcc48-opt/root
. $ROOTHOME/bin/thisroot.sh

if [ -z "${PATH}" ]; then
   PATH=$NKHOME/bin; export PATH
else
   PATH=$NKHOME/bin:$PATH; export PATH
fi

if [ -z "${LD_LIBRARY_PATH}" ]; then
   LD_LIBRARY_PATH=$NKHOME/lib:/usr/local/lib; export LD_LIBRARY_PATH
else
   LD_LIBRARY_PATH=$NKHOME/lib:/usr/local/lib:$LD_LIBRARY_PATH; export LD_LIBRARY_PATH
fi

