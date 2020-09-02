# SNUDC
Data collection and analysis code of Seoul National University multi wire Drift Chamber

## Setup
```
source setup.sh
make
```

## Run Analysis
### Single core
```
root
Time2Length a
a.SetupConfig("runA")
a.Loop()
```
### Multi core
```
SNUDC.py -h
SNUDC.py -a Time2Length -c runA -n 20
```
