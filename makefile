ROOTCFLAGS:=$(shell root-config --cflags)
ROOTLDFLAGS:=$(shell root-config --ldflags)
ROOTLIBS:=$(shell root-config --libs)
ROOTGLIBS:=$(shell root-config --glibs)

MKARCH := $(ROOTSYS)/etc/Makefile.arch
include $(MKARCH)

INCLUDE_DIR=include
SRC_DIR=src
OBJ_DIR=obj
LIB_DIR=lib

LIBNAME=SNUDC
LINKDEF=$(INCLUDE_DIR)/$(LIBNAME)_LinkDef.h
DICT=$(SRC_DIR)/$(LIBNAME)Dict.cxx
DICT_OBJ=$(patsubst $(SRC_DIR)/%.cxx,$(OBJ_DIR)/%.o,$(DICT))
LIB=$(LIB_DIR)/libSNUDC.so

HEADER_FILES=$(filter-out $(LINKDEF),$(wildcard $(INCLUDE_DIR)/*.h))
SRC_FILES=$(wildcard $(SRC_DIR)/*.C)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.C,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXXFLAGS += -I$(INCLUDE_DIR)

all: $(LIB)

$(LIB): $(OBJ_FILES) $(DICT_OBJ)
	mkdir -p $(LIB_DIR)
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ -o $@ $(EXPLLINKLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.C
	@echo "compile $<"
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DICT_OBJ): $(DICT)
	@echo "compile $<"
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DICT): $(HEADER_FILES) $(LINKDEF)
	mkdir -p $(LIB_DIR)
	$(ROOTCLING) -f $@ -rmf $(subst .so,.rootmap,$(LIB)) -rml $(notdir $(LIB)) -rml libTree.so -rml libHist.so -rml libGpad.so -s $(LIB) $(notdir $^)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(DICT)
	rm -rf $(LIB_DIR)
