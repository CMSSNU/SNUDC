#include <stdio.h>
#ifdef NKROOT
  #include <TROOT.h>
#endif
#include "Notice6UVME.h"
#ifdef NKROOT
  ClassImp(NK6UVME)
#endif

#ifndef NKC
NK6UVME::NK6UVME()
{
   printf("NK6UVME Initialization \n") ;
}

NK6UVME::~NK6UVME()
{
   printf("Leaving NK6UVME now \n");
}
#endif

//char devname2[80];
// open VME controller
#ifdef NKC
 int VMEopen(int devnum)
#else
 int NK6UVME::VMEopen(int devnum)
#endif
{
  //  strcpy(devname2,devname);
  
  return uopen(devnum);
}


// close VME controller
#ifdef NKC
int VMEclose(int devnum)
#else
int NK6UVME::VMEclose(int devnum)
#endif
{
  return uclose(devnum);
}


// VME write cycle
#ifdef NKC
int VMEwrite(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long data)
#else
int NK6UVME::VMEwrite(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long data)
#endif
{
  int flag;
  int ntry;
  flag = -1;
  ntry =0;
  while (flag < 0) {
    if(ntry>5) {
      printf(" 6UVME : VMEwrite does not respond. After 5 try, giving up! \n");
      return -99;
    }
    ntry++;
    flag = Vwrite(devnum, am, tout, address, data);  // send command to EP6
    
    if (flag < 0) {
      printf(" 6UVME : VMEwrite does not respond. Close and Open VME again \n");
      VMEclose(devnum);
      VMEopen(devnum);
    }
  }

  return 0;
}


// VME read cycle
#ifdef NKC
unsigned long VMEread(int devnum, unsigned short am, unsigned short tout, unsigned long address)
#else
unsigned long NK6UVME::VMEread(int devnum, unsigned short am, unsigned short tout, unsigned long address)
#endif

{
  unsigned long data[2];
  int flag;
  int ntry;
  flag = -1;
  ntry =0;
  while (flag < 0) {
    if(ntry>5) {
      printf(" 6UVME : VMEread does not respond. After 5 try, giving up! \n");
      return 0;      
    }
    ntry++;
    flag = Vread(devnum, am, tout, address, data);       // send command to EP6
    if (flag < 0) {
      printf(" 6UVME : VMEread does not respond. Close and Open VME again \n");
      VMEclose(devnum);
      VMEopen(devnum);
    }
  }
  return data[0];
}
  

// VME block read cycle
#ifdef NKC
int VMEblockread(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long counts, char *data)
#else
int NK6UVME::VMEblockread(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long counts, char *data)
#endif
{
  int flag;
  int ntry;
  flag = -1;
  ntry =0;
  while (flag < 0) {
    if(ntry>5) {
      printf(" 6UVME : VMEbloakread does not respond. After 5 try, giving up! \n");
      return -99;
    }
    ntry++;
    flag = Vblockread(devnum, am, tout, address, counts, data);
    
    if (flag < 0) {

      VMEclose(devnum);
      VMEopen(devnum);
      printf(" 6UVME : VMEblockread does not respond. Close and Open VME again \n");
    }
  }

  return 0;
}


// write cycle
#ifdef NKC
int Vwrite(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long data)
#else
int NK6UVME::Vwrite(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long data)
#endif
{
  char wbuf[16];                       // buffer for EP6 write
  int flag;

  wbuf[0] = 0x00;                                // can be any value
  wbuf[1] = 0x00;                                // can be any value
  wbuf[2] = am & 0xFF;                           // WRITE+LWORD+AM
  wbuf[3] = tout & 0xFF;                         // timeout in us
  wbuf[4] = address & 0xFF;                      // address
  wbuf[5] = (address >> 8) & 0xFF;
  wbuf[6] = (address >> 16) & 0xFF;
  wbuf[7] = (address >> 24) & 0xFF;
  wbuf[8] = data & 0xFF;                         // data
  wbuf[9] = (data >> 8) & 0xFF;
  wbuf[10] = (data >> 16) & 0xFF;
  wbuf[11] = (data >> 24) & 0xFF;

  flag = uwrite(devnum, wbuf, 12);
  if (flag < 0) 
    return flag;

  return 0;
}


// read cycle
#ifdef NKC
int Vread(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long *data)
#else
int NK6UVME::Vread(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long *data)
#endif
{
  char wbuf[16];                        // buffer for EP6 write
  unsigned int lword;
  char rbuf[16];
  unsigned long temp;
  unsigned char vmemode;
  int flag;
  
  vmemode = am | 0x0080;                         // set in read mode

  lword = vmemode & 0x40;           

  wbuf[0] = 0x00;                                // can be any value
  wbuf[1] = 0x00;                                // can be any value
  wbuf[2] = vmemode & 0xFF;                      // WRITE+LWORD+AM
  wbuf[3] = tout & 0xFF;                         // timeout in us
  wbuf[4] = address & 0xFF;                      // start address
  wbuf[5] = (address >> 8) & 0xFF;
  wbuf[6] = (address >> 16) & 0xFF;
  wbuf[7] = (address >> 24) & 0xFF;

  if (lword) {
    wbuf[8] = 2;                     
    wbuf[9] = 0;
    wbuf[10] = 0;
    wbuf[11] = 0;
  }
  else {
    wbuf[8] = 4;                     
    wbuf[9] = 0;
    wbuf[10] = 0;
    wbuf[11] = 0;
  }
  flag = uwrite(devnum,wbuf,12);

    
  if (flag < 0) 
    return flag;

  
  if (lword) {
    flag = uread(devnum,rbuf,2);

    if (flag < 0) 
      return flag;

    data[0] = rbuf[0]&0xFF;
    temp = rbuf[1]&0xFF;
    temp = temp << 8;
    data[0] = data[0] + temp;
  }
  else {

    flag = uread(devnum,rbuf,4);

    if (flag < 0) 
      return flag;

    data[0] = rbuf[0]&0xFF;
    temp = rbuf[1]&0xFF;
    temp = temp << 8;
    data[0] = data[0] + temp;
    temp = rbuf[2]&0xFF;
    temp = temp << 16;
    data[0] = data[0] + temp;
    temp = rbuf[3]&0xFF;
    temp = temp << 24;
    data[0] = data[0] + temp;
  }
  
  return 0;
}
  

// block read cycle
#ifdef NKC
int Vblockread(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long counts, char *data)
#else
int NK6UVME::Vblockread(int devnum, unsigned short am, unsigned short tout, unsigned long address, unsigned long counts, char *data)
#endif
{
  char wbuf[16];                       
  unsigned char vmemode;
  int flag;
  unsigned long chunk, remain;
  unsigned long i;
  
  chunk = counts / 0x10000;
  remain = counts % 0x10000;

  vmemode = am | 0x0080;                         // set in read mode

  wbuf[0] = 0x00;                                // can be any value
  wbuf[1] = 0x00;                                // can be any value
  wbuf[2] = vmemode & 0xFF;                      // WRITE+LWORD+AM
  wbuf[3] = tout & 0xFF;                         // timeout in us
  wbuf[4] = address & 0xFF;                      // start address
  wbuf[5] = (address >> 8) & 0xFF;
  wbuf[6] = (address >> 16) & 0xFF;
  wbuf[7] = (address >> 24) & 0xFF;

  wbuf[8] = counts & 0xFF;                      
  wbuf[9] = (counts >> 8) & 0xFF;
  wbuf[10] = (counts >> 16) & 0xFF;
  wbuf[11] = (counts >> 24) & 0xFF;

  flag = uwrite(devnum,wbuf,12);
    
  if (flag < 0) 
    return flag;

  for (i = 0; i < chunk; i++) {
    flag = uread(devnum,data+0x10000*i,0x10000);
    
    if (flag < 0)
      return flag;
  }

  flag = uread(devnum,data+0x10000*chunk,remain);

  if (flag < 0) 
    return flag;

  return 0;
}


