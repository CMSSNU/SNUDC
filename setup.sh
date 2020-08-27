#!/bin/bash
which root > /dev/null || {
    if cat /etc/*release|grep -q "Ubuntu 18";then
	source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.22.02/x86_64-ubuntu18-gcc75-opt/bin/thisroot.sh
    elif cat /etc/*release|grep -q "Scientific Linux release 6";then
	source /cvmfs/sft.cern.ch/lcg/views/ROOT-latest/x86_64-slc6-gcc48-opt/setup.sh
	source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.06.08/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh
    else
	echo "Cannot setup ROOT... Exit..."
	exit 1
    fi
}
echo "Using $(which root)"

export SNUDC_WORKING_DIR=$(cd "$(dirname "${BASH_ARGV[0]}")"; pwd)
export SNUDC_FILE_PATH=$SNUDC_WORKING_DIR/rootfiles/
export SNUDC_PLOT_PATH=$SNUDC_WORKING_DIR/plots/
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$SNUDC_WORKING_DIR/include/:$SNUDC_WORKING_DIR/src/
export LD_LIBRARY_PATH=$SNUDC_WORKING_DIR/lib:$LD_LIBRARY_PATH

source $SNUDC_WORKING_DIR/bin/BashColorSets.sh

alias lqout='cd '$SNUDC_PLOT_PATH
