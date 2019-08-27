#Directory declaration
MAINDIR = $(APP_HOME)
PGMDIR = $(MAINDIR)/bin
LIBDIR = $(MAINDIR)/lib
INCDIR = $(MAINDIR)/include

#Application Version
include APPVER

#DEBUG Mode
EXECUTE=#DEBUG

ifeq ($(EXECUTE), DEBUG)
	OPTIMIZE =
	DEBUGFLAGS = -g -D_DEBUG
	LIB =
	EXTNAME = _DBG
else
	OPTIMIZE = -O2
	DEBUGFLAGS =
	LIB =
	EXTNAME =
endif

#variable

CC        = gcc
CXX       = g++
OFLAGS    = -Wall -W -c
CFLAGS    = -Wall -W -o
IFLAGS    = -I. -I$(INCDIR)
LFLAGS    = -L. -L$(LIBDIR)
LIBS      = -lm -lpthread $(LIB)
REMOVE    = rm -f
COPY      = cp -f
#file extensions
O        = .o
EXE      = .exe

.c.o :
	$(CC) -std=c2a $(OFLAGS) $(DEBUGFLAGS) $(OPTIMIZE) $(IFLAGS) $<
.cpp.o:
	$(CXX) -std=c++2a $(OFLAGS) $(DEBUGFLAGS) $(OPTIMIZE) $(IFLAGS) $<

all : StringTest$(EXTNAME).$(MAJORLIBVER).$(MINORLIBVER).$(PATCHLIBVER)$(EXE) 

clean :
	$(REMOVE) core
	$(REMOVE) *.txt
	$(REMOVE) *$(O)
	$(REMOVE) StringTest$(EXTNAME).$(MAJORLIBVER).$(MINORLIBVER).$(PATCHLIBVER)$(EXE)

install : all
	$(COPY) StringTest$(EXTNAME).$(MAJORLIBVER).$(MINORLIBVER).$(PATCHLIBVER)$(EXE) $(PGMDIR)

uninstall: clean
	$(REMOVE) $(PGMDIR)/StringTest$(EXTNAME).$(MAJORLIBVER).$(MINORLIBVER).$(PATCHLIBVER)$(EXE)

StringTest$(EXTNAME).$(MAJORLIBVER).$(MINORLIBVER).$(PATCHLIBVER)$(EXE): main$(O) String$(O)
	$(CXX) -std=c++2a $(DEBUGFLAGS) $(OPTIMIZE) main$(O) String$(O) $(IFLAGS) $(LFLAGS) $(LIBS) $(CFLAGS) $@
