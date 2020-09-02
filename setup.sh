#!/bin/bash
which root &> /dev/null || {
    if cat /etc/*release|grep -q "Ubuntu 18";then
	source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.22.02/x86_64-ubuntu18-gcc75-opt/bin/thisroot.sh
    elif cat /etc/*release|grep -q "Scientific Linux release 6";then
	source /cvmfs/sft.cern.ch/lcg/views/ROOT-latest/x86_64-slc6-gcc48-opt/setup.sh
	source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.06.08/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh
    elif cat /etc/*release|grep -q "CentOS Linux 7";then
	source /cvmfs/sft.cern.ch/lcg/views/ROOT-latest/x86_64-centos7-gcc48-opt/setup.sh
	source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.18.02/x86_64-centos7-gcc48-opt/bin/thisroot.sh
    else
	echo "Cannot setup ROOT... Exit..."
	return 1
    fi
}
echo "Using $(which root)"

export SNUDC_WORKING_DIR=$(cd "$(dirname "${BASH_ARGV[0]}")"; pwd)
if hostname|egrep -q "tamsa[1-2]|cms[1-2]";then
    SNUDC_DATA_PATH=/data8/DATA/SNUDC/
else
    SNUDC_DATA_PATH=$SNUDC_WORKING_DIR/rootfiles/
fi
export SNUDC_DATA_PATH
export SNUDC_PLOT_PATH=$SNUDC_WORKING_DIR/plots/
export ROOT_INCLUDE_PATH=$SNUDC_WORKING_DIR/include:$ROOT_INCLUDE_PATH
export LD_LIBRARY_PATH=$SNUDC_WORKING_DIR/lib:$LD_LIBRARY_PATH
export PATH=$SNUDC_WORKING_DIR/python:$PATH

source $SNUDC_WORKING_DIR/bin/BashColorSets.sh

alias lqout='cd '$SNUDC_PLOT_PATH
