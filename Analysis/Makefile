.EXPORT_ALL_VARIABLES:

.PHONY: all

LIB_DIR = $(HOME)/lib

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
ROOTINC      := -I$(shell root-config --incdir)

COMMON_DIR = $(HOME)/programs/common/

ALLIBS  = -lm $(ROOTLIBS) $(ROOTGLIBS) -L$(LIB_DIR) -lCommandLineInterface -lEventInfo

CPP             = g++
CFLAGS		= -pedantic -Wall -Wno-long-long -g -O3 $(ROOTCFLAGS) -fPIC
DFLAGS		= -Wall -Wno-long-long -g -O3 $(ROOTCFLAGS) -fPIC
CFLAGS		+= -Wl,--no-as-needed
DFLAGS		+= -Wl,--no-as-needed

INCLUDES        = -I./inc -I$(COMMON_DIR)
LFLAGS		= -fPIC -O2 -g $(ROOTLDFLAGS)
LIBS 		= $(ALLIBS)

USING_ROOT_6 = $(shell expr $(shell root-config --version | cut -f1 -d.) \>= 6)
ifeq ($(USING_ROOT_6),1)
	EXTRAS =  EventInfoDictionary_rdict.pcm 
endif

all: EventInfo $(EXTRAS) 
	echo Done

LISAAna: LISAAna.cc 
	@echo "Compiling $@"
	@$(CPP) $(CFLAGS) $(INCLUDES) $^ $(LIBS) -o $@
	@cp LISAAna $(HOME)/bin

EventInfo: build/EventInfo.o build/EventInfoDictionary.o 
	@echo "Compiling $@"
	$(CPP) $(LFLAGS) -shared -Wl,-soname,libEventInfo.so -o $(LIB_DIR)/libEventInfo.so $^ -lc

build/%.o: src/%.cc inc/%.hh
	@echo "Compiling $@"
	@mkdir -p $(dir $@)
	@$(CPP) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

build/%Dictionary.o: build/%Dictionary.cc
	@echo "Compiling $@"
	@mkdir -p $(dir $@)
	@$(CPP) $(CFLAGS) $(INCLUDES) -fPIC -c $< -o $@

build/%Dictionary.cc: inc/%.hh inc/%LinkDef.h
	@echo "Building $@"
	@mkdir -p $(dir $@)
	@rootcint -f $@ -c $(INCLUDES) $(SWITCH) $(notdir $^)

build/%Dictionary_rdict.pcm: build/%Dictionary.cc
	@echo "Confirming $@"
	@touch $@

%Dictionary_rdict.pcm: build/%Dictionary_rdict.pcm
	@echo "Placing $@"
	@cp build/$@ $(LIB_DIR)
clean:
	rm  -f LISAAna build/*.o build/*Dictionary*
