############################
#### MAKE VARS
############################
APP 	:= particle
CC 		:= g++
CCFLAGS := -Wall -pedantic -std=c++20
C		:= gcc
CFLAGS 	:=
LIBDIR  := lib/
LIBS 	:= -lX11 -lXext $(LIBDIR)tinyPTCua/libTinyPtc.a $(LIBDIR)picoPNGua/libPicoPng.a
INCDIRS := -I$(LIBDIR)tinyPTCua/src -I$(LIBDIR)picoPNGua/src -Isrc

ifndef config
	config=DEBUG
endif

ifeq ($(config),DEBUG)
	CCFLAGS += -g
else ifeq ($(config),RELEASE)
	CCFLAGS += -O3
else ifeq ($(config),MEMCHECK)
	CCFLAGS += -g -fsanitize=address -fsanitize=undefined
	LIBS += -fsanitize=address -fsanitize=undefined
else
$(error "Invalid configuration $(config)")
endif


.PHONY: info

############################
#### INSTRUCTIONS DATA
############################
MKDIR 	:= mkdir -p
MKLIB 	:= ar rcs

############################
#### DIRECTORI DATA
############################
SRC 	:= src
OBJ 	:= obj

############################
#### GENERATED MACROS
############################
define C20
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

############################
#### $(1) : File to compile
#### $(2) : Obj file
#### $(3) : Depedencies
#### $(4) : Compiler
#### $(5) : Compiler Flags
############################
define COMPILE
$(2) : $(1) $(3)
	$(4) -c -o $(2) $(1) $(5)
endef

############################
#### FILES & DIRECTORIES
############################
ALLCPPS := $(shell find $(SRC) -type f -iname *.cpp)
ALLCS 	:= $(shell find $(SRC) -type f -iname *.c)
ALLOBJS := $(call C20,$(ALLCPPS) $(ALLCS))
SRCDIRS := $(shell find $(SRC) -type d)
OBJDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SRCDIRS))

############################
#### MAKEFILE RULES
############################
$(APP) : $(OBJDIRS) $(ALLOBJS)
	$(CC) -o $(APP) $(ALLOBJS) $(LIBS)

$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(F),$(call C20,$(F)),$(call C2H,$(F)),$(CC),$(CCFLAGS) $(INCDIRS))))

$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(F),$(call C20,$(F)),$(call C2H,$(F)),$(C),$(CFLAGS) $(INCDIRS))))

$(OBJDIRS) :
	$(shell $(MKDIR) $(OBJDIRS))

info :
	$(info $(SRCDIRS))
	$(info $(OBJDIRS))
	$(info $(ALLCS))
	$(info $(ALLCPPS))
	$(info $(ALLOBJS))
	$(info $(LIBS))

clean :
	rm -rf $(OBJDIRS)
	rm $(APP)