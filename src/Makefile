# Compiler settings - Can be customized.
CC = g++
WINDRES = windres.exe
CXXFLAGS = -Wall -O2 -std=c++11 -fexec-charset=gbk -finput-charset=UTF-8
LDFLAGS =  -s -shared-libstdc++  -lgdi32 -luser32 -lkernel32 -lcomctl32 -mwindows

# Makefile settings - Can be customized.
APPNAME = WinKcp_Launcher
EXT = .cpp

SRCDIR = .
OBJDIR = .

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

####################### Targets beginning here #########################
all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(WINDRES)  -J rc -O coff -i resource.rc -o resource.res 
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)  resource.res

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT) 
	$(CC)  $(CXXFLAGS) -o $@ -c $<
