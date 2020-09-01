#include "Notice6UVME.h"

#ifndef NKC
class NKTDC64M : public NK6UVME {
 public:
           NKTDC64M();
  virtual ~NKTDC64M();
#endif


  void TDC64Mopen(int devnum, unsigned long mid);
  int TDC64Mread_TDCL2(int devnum, unsigned long mid, unsigned long page, int *data, int *edge, int *hitnum, int *evtnum, int *ch);
  void TDC64Mread_TDCL1(int devnum, unsigned long mid, unsigned long page, int emode, int *nhit, int *tdc, int *edge);
  void TDC64Mreset(int devnum, unsigned long mid);
  unsigned long TDC64Mcheck_CPU(int devnum, unsigned long mid);
  void waitCPU(int devnum, unsigned long mid);
  void TDC64Mwrite_MODE(int devnum, unsigned long mid, int gmode, int emode, int rmode);
  unsigned long TDC64Mread_MODE(int devnum, unsigned long mid);
  void TDC64MstartL(int devnum, unsigned long mid);
  void TDC64Mstop(int devnum, unsigned long mid);
  unsigned long TDC64Mread_RunL(int devnum, unsigned long mid);
  void TDC64MstartH(int devnum, unsigned long mid);
  unsigned long TDC64Mread_RunH(int devnum, unsigned long mid);
  void TDC64Mwrite_RANGE(int devnum, unsigned long mid, unsigned long data);
  unsigned long TDC64Mread_RANGE(int devnum, unsigned long mid);
  void TDC64Mwrite_DLY(int devnum, unsigned long mid, unsigned long data);
  unsigned long TDC64Mread_DLY(int devnum, unsigned long mid);
  unsigned long TDC64Mread_ENUM(int devnum, unsigned long mid);
  void TDC64Mwrite_TMASK(int devnum, unsigned long mid, unsigned long group, unsigned long data);
  unsigned long TDC64Mread_TMASK(int devnum, unsigned long mid, unsigned long group);


#ifdef NKROOT
  ClassDef(NKTDC64M,2)
#endif
#ifndef NKC
     };
#endif

