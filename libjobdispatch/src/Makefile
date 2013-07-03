ifeq ("", "$(CONFIG)")
# CONFIG : DEBUG OR RELEASE ?
CONFIG=		RELEASE
#CONFIG=	DEBUG
endif
ifeq ("", "$(PLATFORM)")
PLATFORM=	UNIX
#PLATFORM=	WINDOWS
endif
ifeq ("", "$(PREFIX)")
	ifeq (WINDOWS, $(PLATFORM))
		# under MinGW, put libs into /mingw/lib
		PREFIX=/mingw/
	else
		# under Linux, put libs into /usr/local/lib
		PREFIX=/usr/local
	endif
endif
ifeq (DEBUG, $(CONFIG))
	# add debug symbols
	BUILDFLAGS=-ggdb -Wall
else
	# release optimization
	BUILDFLAGS=-s -O3
endif
ifeq (WINDOWS, $(PLATFORM))
	# specific #define for Windows
	PLATFORMFLAGS+=-D_WIN32 -DWIN32 -U_UNICODE -UUNICODE
endif

CXXFLAGS=$(BUILDFLAGS) $(PLATFORMFLAGS)
AR=ar
CC=gcc
CXX=g++
OBJS=JobDispatcher.o JobHandler.o JobDispatchChannel.o PingChannel.o
LCMGEN=JobInfo.hpp Ping.hpp
TARGET=libjobdispatch.a

all: $(LCMGEN) $(OBJS)
		ar rcs $(TARGET) $(OBJS)
		
clean:
		rm -f *.o *.hpp $(TARGET)
		
install: all
		mkdir -p $(PREFIX)/lib
		install $(TARGET) $(PREFIX)/lib
		mkdir -p $(PREFIX)/include/xcpplibs/jobdispatch
		install *.h *.hpp $(PREFIX)/include/xcpplibs/jobdispatch
		
%.hpp: %.lcm
		lcm-gen -x "$<"

%.o: %.cpp
		$(CXX) -c "$<" -o"$@" $(CXXFLAGS)
