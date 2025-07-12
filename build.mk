STD = c++17
CFLAGS = -std=$(STD) $(INCS)
LDFLAGS = -L$(SLIBDIR) -L$(DLIBDIR)
LDLIBS = $(addprefix -l,$(DEPS))

ifeq ($(BUILD_TYPE),Release)
CFLAGS := $(CFLAGS) -O3
else ifeq ($(BUILD_TYPE),RelWithDebInfo)
CFLAGS := $(CFLAGS) -O2 -ggdb
else ifeq ($(BUILD_TYPE),Debug)
CFLAGS := $(CFLAGS) -O0 -ggdb
endif

ifeq ($(BUILD_SHARED),ON)
CFLAGS := $(CFLAGS) -DSHARED -DEXP_BUILD
ifeq ($(OS),Windows_NT)
CFLAGS := $(CFLAGS) -fPIC
endif
endif

ifeq ($(BUILD_SHARED),OFF)
CFLAGS := $(CFLAGS) -DSHARED
endif

$(OBJDIR)/%_c.obj: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%_cpp.obj: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(SLIBDIR)/lib$(PROJ).a $(SLIBDIR)/lib$(PROJ).lib: $(OBJLIST)
	ar -rcs -o $@ $^

$(DLIBDIR)/lib$(PROJ).so $(DLIBDIR)/lib$(PROJ).dll: $(OBJLIST)
	$(eval override CFLAGS := -shared $(CFLAGS))
ifeq (${OS},Windows_NT)
	$(eval override CFLAGS := $(CFLAGS) -Wl,--out-implib,$(SLIBDIR)/lib$(PROJ).dll.a)
endif
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OUTPUT_DIR)/$(PROJ).exe $(OUTPUT_DIR)/$(PROJ): $(OBJLIST)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.INTERMEDIATE: $(OBJLIST)

