########################################################################
#                                                                      #
#   NK Korea    TDC64M test program                                    #
#                                                                      #
#   Created: Sept. 2006                                                #
#                                                                      #
#   Auth: H.J. Kim hongjoo@knu.ac.kr                                   #
#                                                                      #
########################################################################
#   NKHOME should be defined

FILENAME = tdc64m_test

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLDFLAGS  := $(shell root-config --ldflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

EXE     =       $(FILENAME)

CC	=	g++

COPTS	=	-fPIC -O -Wall -Wno-deprecated -DNKROOT $(ROOTCFLAGS)

FLAGS	=	-shared 

LDFLAG  =       -O

DEPLIBS	=      -L/$(NKHOME)/lib  -lNotice6UVME_root -lNoticeTDC64M_root 

LIBS	=	-L/$(NKHOME)/lib  

INCLUDEDIR =	-I/$(NKHOME)/include

INSTALLDIR     =	$(NKHOME)/bin
INSTALLINCLUDE =	$(NKHOME)/include

OBJS	=	$(FILENAME).o 

INCLUDES =	$(FILENAME).h 



#########################################################################

all	:	$(EXE)

                
clean	:
		/bin/rm -f $(OBJS) $(LIB) $(EXE)

install	:	$(EXE)
		/bin/rm -f $(INSTALLDIR)/$(EXE)
		install $(EXE) $(INSTALLDIR)
 

$(EXE)	:	$(OBJS)
		$(CC) $(LDFLAG) $(OBJS) $(DEPLIBS)  $(ROOTLIBS) $(ROOTGLIBS) -o $(EXE)

$(OBJS) :       $(INCLUDES)
%.o	:	%.cxx
		$(CC) $(COPTS) $(INCLUDEDIR) -c -o $@ $<

