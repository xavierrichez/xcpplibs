# CONFIG : DEBUG OR RELEASE ?
CONFIG=		RELEASE
#CONFIG=	DEBUG
PLATFORM=	UNIX
#PLATFORM=	WINDOWS

ifeq (DEBUG, $(CONFIG))
	# add debug symbols
	BUILDFLAGS=-g -ggdb -gstabs
else
	# release optimization
	BUILDFLAGS=-s -O3
endif
ifeq (WINDOWS, $(PLATFORM))
	# specific #define for Windows
	PLATFORMFLAGS+=-D_WIN32 -DWIN32 -U_UNICODE -UUNICODE
	# under MinGW, put libs into /mingw/lib
	PREFIX=/mingw/
else
	# under Linux, put libs into /usr/local/lib
	PREFIX=/usr/local
endif
	# specific #define for TinyXML and MySQL++
DEPFLAGS=

CXXFLAGS=$(BUILDFLAGS) $(PLATFORMFLAGS) $(DEPFLAGS)
AR=ar
CC=gcc
CXX=g++
LIBS=
OBJS=logger.o
TARGET=libxcpplogger.a

all: $(OBJS)
		ar rcs $(TARGET) $(OBJS)
		
clean:
		rm -f *.o $(TARGET)
		
install: all
		mkdir -p $(PREFIX)/lib
		install $(TARGET) $(PREFIX)/lib
		mkdir -p $(PREFIX)/include/xcpplibs
		install logger.h $(PREFIX)/include/xcpplibs/

%.o: %.cpp
		$(CXX) -c "$<" -o"$@" $(CXXFLAGS)