/*
 * NoticeKorea NKUSBVME USB/VME Interface for Linux
 *
 *  by H.J. Kim (hongjoo@knu.ac.kr) Sept 1996
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 *
 *   TODO
 *   
 * Changelog:
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "NKUSBVME_Linux.h"

//int handle;
int handle[10]={0};

int uopen(int devnum)
{
  //char *devname;

  char devname[80];
  if(devnum >9 || devnum <0) return -1;  //devnum 0-10 max
     sprintf(devname,"/dev/nkusbvme%d", devnum);

     printf("devname = %s\n", devname);

     handle[devnum] = open(devname,O_RDWR);
     //#ifdef DEBUG
     printf("nkusbvme open handle = %d \n",handle[devnum]); 
     if(handle[devnum]<0) {
        printf("Open failed!!!!!! devnum=%d \n",handle[devnum]);
     }
     //#endif
     return handle[devnum];
}

int uclose(int devnum)
{
  close(handle[devnum]);

  return 0;
}

int uwrite(int devnum, char *buffer,
           unsigned long length)
{
  int ret ;  
  ret = write(handle[devnum],buffer,length);
#ifdef DEBUG
  printf("write ret= %d \n",ret);
  for(int i=0;i<length;i++) {
    printf(" %x ",buffer[i]);
  }
  printf("count= %d \n",length);
#endif
  return ret;
}

int uread(int devnum, char *buffer, unsigned long length)
{
  int count; 
  count = read(handle[devnum],buffer,length);  
  if(count < (int) length) {
    printf(" evt reading is not completed! wanted=%d, reading=%ld \n",count,length);
  }
  return count;
}

