# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := G4LISA
G4TARGET := $(name)
G4EXLIB := true
#CPPVERBOSE := true

ifndef G4INSTALL
  G4INSTALL = ../../source
endif

LIB_DIR = $(HOME)/lib
EXTRA_INCLUDES = -I./include 

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk

CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags) $(EXTRA_INCLUDES)
LDFLAGS  += $(shell $(ROOTSYS)/bin/root-config --libs)
CPPFLAGS  += -Wl,--no-as-needed
LDFLAGS  += -Wl,--no-as-needed
CPPFLAGS  += -Woverloaded-virtual -DISSIM
LDFLAGS  += -Woverloaded-virtual -DISSIM

EXTRALIBS = -L$(LIB_DIR) -lEventInfo

include $(G4INSTALL)/config/binmake.gmk

test:	
	echo $(LDFLAGS)

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

bkpclean:
	rm -f src/*~ include/*~ *~

