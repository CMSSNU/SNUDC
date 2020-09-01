class fadc{
 public:
  Int_t tdc;     // TDC data
  Int_t edge;    // edge flag
  Int_t hitnum;  // hit number
  Int_t evtnum;  // event number
  Int_t ch;      // TDC channel #
};

class head{
 public:
  Int_t gmode;
  Int_t emode;
  Int_t rmode;
  Int_t range;
  Int_t delay;
  Int_t mask[64];
};

