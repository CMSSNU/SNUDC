#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef NKROOT
#include <TROOT.h>
#endif

#include "NoticeTDC64M.h"

#ifdef NKROOT
ClassImp(NKTDC64M)
#endif
  
#ifndef NKC
     NKTDC64M::NKTDC64M()
{
  printf("NKTDC64M Initialization \n");
}

NKTDC64M::~NKTDC64M()
{
  printf("Leaving NKTDC64M now \n");
}
#endif


// Open TDC64M
#ifdef NKC
void TDC64Mopen(int devnum, unsigned long mid)
#else
void NKTDC64M::TDC64Mopen(int devnum, unsigned long mid)
#endif
{
  waitCPU(devnum, mid);
}

// Read TDC L2 buffer
#ifdef NKC
int TDC64Mread_TDCL2(int devnum, unsigned long mid, unsigned long page, int *data, int *edge, int *hitnum, int *evtnum, int *ch)
#else
int NKTDC64M::TDC64Mread_TDCL2(int devnum, unsigned long mid, unsigned long page, int *data, int *edge, int *hitnum, int *evtnum, int *ch)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long value;
  char rdat[0x200000];
  int dsize;
  int dnum;
  int i;
  int tmp;
	
  baseaddr = (mid & 0xFF) << 24;

  // get data size
  if (page)
    addr = baseaddr + 0x700014;
  else
    addr = baseaddr + 0x700010;
  value = VMEread(devnum, A32D16, 0, addr + 2);
  dsize = value << 16;
  value = VMEread(devnum, A32D16, 0, addr);
  dsize = dsize + (value & 0xFFFF);
	
  // get entry size
  dnum = dsize / 8;
	
  // dump buffer
  if (page)
    addr = baseaddr + 0x200000;
  else
    addr = baseaddr;
		
  if (dsize > 0)		
    VMEblockread(devnum, A32D16, 0, addr, dsize, rdat);
  	
  // making data set
  for (i = 0; i < dnum; i++) {
  	
    // TDC data
    data[i] = rdat[8 * i + 1] & 0xFF;
    data[i] = data[i] << 8;
    data[i] = data[i] + (rdat[8 * i] & 0xFF);
    	
    // pulse edge (0 = rising, 1 = trailing)
    edge[i] = rdat[8 * i + 2] & 0xFF;
    	
    // hit number
    hitnum[i] = (rdat[8 * i + 3] & 0xFF) + 1;
  		
    // event number
    evtnum[i] = rdat[8 * i + 6] & 0xFF;
    evtnum[i] = evtnum[i] << 16;
    tmp = rdat[8 * i + 5] & 0xFF;
    tmp = tmp << 8;
    evtnum[i] = evtnum[i] + tmp;
    evtnum[i] = evtnum[i] + (rdat[8 * i + 4] & 0xFF);
		
    // channel number
    ch[i] = (rdat[8 * i + 7] & 0xFF) + 1;
  }
    
  return dnum;
}
	
	
// Read TDC L1 Buffer
#ifdef NKC
void TDC64Mread_TDCL1(int devnum, unsigned long mid, unsigned long page, int emode, int *nhit, int *tdc, int *edge)
#else
void NKTDC64M::TDC64Mread_TDCL1(int devnum, unsigned long mid, unsigned long page, int emode, int *nhit, int *tdc, int *edge)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  char rdat[0x10000];
  int saddr[1024];
  int tdat[32768];
  int edat[32768];
  int i;
  int ch;
  int evt;
  int hit;
  int index;
	
  baseaddr = (mid & 0xFF) << 24;
  	
  // get number of hits
  if (page)
    addr = baseaddr + 0x400800;
  else
    addr = baseaddr + 0x400000;

  VMEblockread(devnum, A32D16, 0, addr, 0x800, rdat);
  	
  for (i = 0; i < 1024; i++) 
    nhit[i] = rdat[2 * i] & 0xFF;
  	
  // get starting address 
  if (page)
    addr = baseaddr + 0x500800;
  else
    addr = baseaddr + 0x500000;

  VMEblockread(devnum, A32D16, 0, addr, 0x800, rdat);
  	
  for (i = 0; i < 1024; i++) {
    saddr[i] = rdat[2 * i] & 0xFF;
    	
    if (emode) {
      if (nhit[i] < 32)
	saddr[i] = 0;
    }
    else {
      if (nhit[i] < 16)
	saddr[i] = 0;
    }
  }

  // get TDC data
  if (page)
    addr = baseaddr + 0x610000;
  else
    addr = baseaddr + 0x600000;
  
  VMEblockread(devnum, A32D16, 0, addr, 0x10000, rdat);

  for (i = 0; i < 32768; i++) {
    tdat[i] = rdat[2 * i + 1] & 0xFF;
    tdat[i] = tdat[i] << 8;
    tdat[i] = tdat[i] + (rdat[2 * i] & 0xFF);
  }

  // get edge data
  if (page)
    addr = baseaddr + 0x690000;
  else
    addr = baseaddr + 0x680000;
  
  VMEblockread(devnum, A32D16, 0, addr, 0x10000, rdat);

  for (i = 0; i < 32768; i++) 
    edat[i] = rdat[2 * i] & 0xFF;
  
  // initialize data value
  for (i = 0; i < 32768; i++) {
    tdc[i] = 0;
    edge[i] = 0;
  }

  // sorting tdc and edge data
  for (ch = 0; ch < 64; ch++) {
    for (evt = 0; evt < 16; evt++) {
      for (hit = 0; hit < nhit[ch * 16 + evt]; hit++) {
	if (emode) 
	  index = ch * 512 + 32 * evt + ((hit + saddr[ch * 16 + evt]) & 0x1F);
	else					
	  index = ch * 512 + 32 * evt + ((hit + saddr[ch * 16 + evt]) & 0x0F);
	
	tdc[ch * 512 + evt * 32 + hit] = tdat[index];
	edge[ch * 512 + evt * 32 + hit] = edat[index];
      }
    }
  }
}


// Send Reset signal
#ifdef NKC
void TDC64Mreset(int devnum, unsigned long mid)
#else
void NKTDC64M::TDC64Mreset(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700000;

  VMEwrite(devnum, A32D16, 0, addr, 0x0);
}


// Check CPU busy
#ifdef NKC
unsigned long TDC64Mcheck_CPU(int devnum, unsigned long mid)
#else
unsigned long NKTDC64M::TDC64Mcheck_CPU(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700000;

  data = VMEread(devnum, A32D16, 0, addr);

  return data;
}


// wait for CPU ready
#ifdef NKC
void waitCPU(int devnum, unsigned long mid)
#else
void NKTDC64M::waitCPU(int devnum, unsigned long mid)
#endif
{
  unsigned long flag;
	
  flag = 0;
  while (!flag) 
    flag = TDC64Mcheck_CPU(devnum, mid);
}


// Write TDC Mode
#ifdef NKC
void TDC64Mwrite_MODE(int devnum, unsigned long mid, int gmode, int emode, int rmode)
#else
void NKTDC64M::TDC64Mwrite_MODE(int devnum, unsigned long mid, int gmode, int emode, int rmode)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
	
  baseaddr = (mid & 0xFF) << 24;
  
  addr = baseaddr + 0x700002;
	
  data = 0;

  if (gmode)
    data = data | 0x1;

  if (emode)
    data = data | 0x2;

  if (rmode)
    data = data | 0x4;

  VMEwrite(devnum, A32D16, 0, addr, data);
}


// Read TDC mode
#ifdef NKC
unsigned long TDC64Mread_MODE(int devnum, unsigned long mid)
#else
unsigned long NKTDC64M::TDC64Mread_MODE(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700002;

  data = VMEread(devnum, A32D16, 0, addr);
  
  return data;
}


// Run TDC buffer0
#ifdef NKC
void TDC64MstartL(int devnum, unsigned long mid)
#else
void NKTDC64M::TDC64MstartL(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700004;

  VMEwrite(devnum, A32D16, 0, addr, 0x1);
}


// Stop TDC 
#ifdef NKC
void TDC64Mstop(int devnum, unsigned long mid)
#else
void NKTDC64M::TDC64Mstop(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700004;

  VMEwrite(devnum, A32D16, 0, addr, 0x0);
}


// Read Buffer 0 Flag
#ifdef NKC
unsigned long TDC64Mread_RunL(int devnum, unsigned long mid)
#else
unsigned long NKTDC64M::TDC64Mread_RunL(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x70000C;

  VMEwrite(devnum, A32D16, 0, addr, 0x0);
				
  addr = baseaddr + 0x700004;

  data = VMEread(devnum, A32D16, 0, addr);
  
  return data;
}


// Run TDC buffer1
#ifdef NKC
void TDC64MstartH(int devnum, unsigned long mid)
#else
void NKTDC64M::TDC64MstartH(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700006;

  VMEwrite(devnum, A32D16, 0, addr, 0x1);
}


// Read Buffer 1 Flag
#ifdef NKC
unsigned long TDC64Mread_RunH(int devnum, unsigned long mid)
#else
unsigned long NKTDC64M::TDC64Mread_RunH(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x70000C;

  VMEwrite(devnum, A32D16, 0, addr, 0x0);
				
  addr = baseaddr + 0x700006;

  data = VMEread(devnum, A32D16, 0, addr);
  
  return data;
}


// Write TDC range
#ifdef NKC
void TDC64Mwrite_RANGE(int devnum, unsigned long mid, unsigned long data)
#else
void NKTDC64M::TDC64Mwrite_RANGE(int devnum, unsigned long mid, unsigned long data)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700008;

  VMEwrite(devnum, A32D16, 0, addr, data);
}


// Read TDC range
#ifdef NKC
unsigned long TDC64Mread_RANGE(int devnum, unsigned long mid)
#else
unsigned long NKTDC64M::TDC64Mread_RANGE(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700008;

  data = VMEread(devnum, A32D16, 0, addr);
  
  return data;
}


// Write TDC delay
#ifdef NKC
void TDC64Mwrite_DLY(int devnum, unsigned long mid, unsigned long data)
#else
void NKTDC64M::TDC64Mwrite_DLY(int devnum, unsigned long mid, unsigned long data)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long value;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x70000A;
  	
  value = data / 8;

  VMEwrite(devnum, A32D16, 0, addr, value);
}


// Read TDC delay
#ifdef NKC
unsigned long TDC64Mread_DLY(int devnum, unsigned long mid)
#else
unsigned long NKTDC64M::TDC64Mread_DLY(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
  unsigned long value;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x70000A;

  data = VMEread(devnum, A32D16, 0, addr);
  	
  value = data * 8;
  
  return value;
}


// Read Event Number
#ifdef NKC
unsigned long TDC64Mread_ENUM(int devnum, unsigned long mid)
#else
unsigned long NKTDC64M::TDC64Mread_ENUM(int devnum, unsigned long mid)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x70000C;

  VMEwrite(devnum, A32D16, 0, addr, 0x0);

  data = VMEread(devnum, A32D16, 0, addr);
  
  return data;
}


// Write TDC mask
#ifdef NKC
void TDC64Mwrite_TMASK(int devnum, unsigned long mid, unsigned long group, unsigned long data)
#else
void NKTDC64M::TDC64Mwrite_TMASK(int devnum, unsigned long mid, unsigned long group, unsigned long data)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
	
  baseaddr = (mid & 0xFF) << 24;

  addr = baseaddr + 0x700018 + (group & 0x3) * 2;
  	
  VMEwrite(devnum, A32D16, 0, addr, data);
}


// Read TDC mask
#ifdef NKC
unsigned long TDC64Mread_TMASK(int devnum, unsigned long mid, unsigned long group)
#else
unsigned long NKTDC64M::TDC64Mread_TMASK(int devnum, unsigned long mid, unsigned long group)
#endif
{
  unsigned long baseaddr;
  unsigned long addr;
  unsigned long data;
	
  baseaddr = (mid & 0xFF) << 24;
	
  addr = baseaddr + 0x700018 + (group & 0x3) * 2;

  data = VMEread(devnum, A32D16, 0, addr);
  	
  return data;
}
