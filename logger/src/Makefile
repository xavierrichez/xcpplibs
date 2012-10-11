
# CONFIG : DEBUG OR RELEASE ?
CONFIG= RELEASE
#CONFIG= DEBUG

AR=ar
CC=gcc
CXX=g++
ifeq (DEBUG, ${CONFIG})
	# add debug symbols
	CXXFLAGS=-g -ggdb -gstabs
else
	CXXFLAGS=-s -O3
endif
LIBS=
OBJS=logger.o
TARGET=libxcpplogger.a
#PREFIX=/usr/local
PREFIX=/mingw/

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