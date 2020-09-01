#!/usr/bin/env python

import os,sys

if not os.getenv("SNUDC_WORKING_DIR"):
    print("Please source setup.sh")
    exit(1)

import argparse
parser = argparse.ArgumentParser(description="SNUDC cli")
parser.add_argument("-a","--analyzer",type=str,required=True)
parser.add_argument("-c","--config",type=str,required=True)
parser.add_argument("-n","--njob",type=int,default=1)

args =parser.parse_args()

total_events=int(os.popen('echo "'+args.analyzer+' ANALYZER;ANALYZER.SetupConfig(\\"'+args.config+'\\");\ncout<<\\"ENTRIES \\"<<ANALYZER.GetEntries();\n.q"|root -l -b|grep ENTRIES|sed \'s/[^0-9]//g\'').read().strip())
print("total events = "+str(total_events))

import random
rundir=os.popen("echo $SNUDC_WORKING_DIR/run/$(date +%Y%m%d_%H%M%S_)"+str(random.randint(0,1000))).read().strip()
os.system("mkdir -p "+rundir)

shellscript=open(rundir+"/run.sh","w")
shellscript.write(
'''#!/bin/bash
root -l -b -q run${1}.C
''')
shellscript.close()
os.chmod(rundir+"/run.sh",0o755)


for i in range(args.njob):
    nskip=(total_events/args.njob+1)*i
    last_event=(total_events/args.njob+1)*(i+1)
    if last_event>total_events: last_event=total_events
    nevent=last_event-nskip
    
    rootscript=open(rundir+"/run"+str(i)+".C","w")
    rootscript.write(
'''{{
  {analyzer} a;
  a.SetOutFileName("hist{i}.root");
  a.SetupConfig("{config}");
  a.Loop({nskip},{nevent});
}}
'''.format(analyzer=args.analyzer,config=args.config,nskip=nskip,nevent=nevent,i=i))
    rootscript.close()
    
if os.system("which condor_status")==0:
    consorjds=open(rundir+"/condor.jds","w")
    condorjds.write(
'''
output = run$(process).out
error = run$(process).err
log = condor.log
executable = run.sh
arguments = $(process)
getenv = true
queue
''')
    condorjds.close()
    os.system("cd "+rundir+";condor_submit condor.jds;condor_wait condor.log")
else:
    import subprocess
    procs=[]
    for i in range(args.njob):
        procs+=[subprocess.Popen("cd "+rundir+"; ./run.sh "+str(i),shell=True)]
    for p in procs: p.wait()
    
os.system("hadd -f "+args.analyzer+".root "+" ".join([rundir+"/hist"+str(i)+".root" for i in range(args.njob)]))
