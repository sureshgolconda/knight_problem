
CC=g++
BINDIR=../bin/
MKDIR=mkdir -p
########## compiler flags ####################
CFLAGS=-c -Wall -std=c++0x -Wno-sign-compare
LDFLAGS= -std=c++0x

ifeq ($(DEBUG),y)
CFLAGS                :=$(CFLAGS) -g
LDFLAGS               :=$(LDFLAGS) -g
else
CFLAGS                :=$(CFLAGS) -O2 -g
endif

ifeq ($(PROFILE),y)
CFLAGS                :=$(CFLAGS) -pg
LDFLAGS               :=$(LDFLAGS) -pg
endif


#############################################
SOURCES=main.C util.C search_path.C board.C
OBJECTS=$(SOURCES:.C=.o)
EXE=knight_path

#############################################
all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS) 
	@$(MKDIR) $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINDIR)$@

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(BINDIR)$(EXE)