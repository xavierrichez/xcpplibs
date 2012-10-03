
AR=ar
CC=gcc
CXX=g++
CXXFLAGS=
LIBS=
OBJS=logger.o
TARGET=libxcpplogger.a
#PREFIX=/usr/local
PREFIX=/mingw/

all: $(OBJS)
		ar rcs $(TARGET) $(OBJS)
		
clean:
		rm -f *.o $(TARGET)
		
install:
		mkdir -p $(PREFIX)/lib
		install $(TARGET) $(PREFIX)/lib
		mkdir -p $(PREFIX)/include/xcpplibs
		install logger.h $(PREFIX)/include/xcpplibs/

%.o: %.cpp
		$(CXX) -c "$<" -o"$@" $(CXXFLAGS)