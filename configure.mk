# pass from calling makefile / CLI
PROJ =
EXE_SRC =
BUILD_TYPE =
BUILD_SHARED =
CC =

# set directory paths
SRCDIR = $(PROJ)/src
OBJDIR = $(PROJ)/obj
SLIBDIR = $(PROJ)/lib/static
DLIBDIR = $(PROJ)/lib/shared
OUTPUT_DIR = $(PROJ)/bin

export SLIBDIR DLIBDIR OBJDIR OUTPUT_DIR SRCDIR
export INCS
export BUILD_TYPE

ifneq ($(PROJ),)

# set source paths
LIB_SRC := $(wildcard $(SRCDIR)/*.c)
ifeq ($(CC),g++)
LIB_SRC := $(LIB_SRC) $(wildcard ls $(SRCDIR)/*.cpp)
else
override EXE_SRC := $(filter-out $(wildcard ls $(SRCDIR)/*.cpp),$(EXE_SRC))
endif
override EXE_SRC := $(addprefix $(SRCDIR)/,$(EXE_SRC))
LIB_SRC := $(filter-out $(EXE_SRC),$(LIB_SRC))
INCS = $(PROJ) $(DEPS)
INCS := $(addprefix -I,$(INCS))
INCS := $(addsuffix /include,$(INCS))

endif

all: $(OBJDIR) $(SLIBDIR) $(DLIBDIR) $(OUTPUT_DIR) LIBsrcToObj EXEsrcToObj
ifneq ($(BUILD_SHARED),ON)
	"$(MAKE)" -f build.mk OBJLIST='$(LIBOBJ)' BUILD_SHARED=\
	 $(SLIBDIR)/lib$(PROJ).lib
else
	"$(MAKE)" -f build.mk OBJLIST='$(LIBOBJ)' BUILD_SHARED=ON\
	 $(DLIBDIR)/lib$(PROJ).dll
endif
	$(eval override DEPS := $(DEPS) $(PROJ))
ifneq ($(BUILD_SHARED),ON)
	"$(MAKE)" -f build.mk OBJLIST='$(EXEOBJ)' BUILD_SHARED=\
	  $(OUTPUT_DIR)/$(PROJ).exe DEPS='$(DEPS)'
else
	"$(MAKE)" -f build.mk OBJLIST='$(EXEOBJ)' BUILD_SHARED=OFF\
	  $(OUTPUT_DIR)/$(PROJ).exe DEPS='$(DEPS)'
endif

%srcToObj:
	$(info $@)
	$(eval objtmp=$(subst src,obj,$($*_SRC)))
	$(eval objtmp=$(subst .cpp,_cpp.obj,$(objtmp)))
	$(eval objtmp=$(subst .c,_c.obj,$(objtmp)))
	$(eval $*OBJ=$(objtmp))
	$(info $*OBJ=$(S*OBJ))

$(OBJDIR) $(SLIBDIR) $(DLIBDIR) $(OUTPUT_DIR):
	mkdir -p '$@'

clean:
ifeq ($(PROJ),)
	rm -f */{bin,obj}/*
	rm -f */lib/{shared,static}/*
else
	rm -f $(PROJ)/{bin,obj}/*
	rm -f $(PROJ)/lib/{static,shared}/*
endif

.PHONY: all clean