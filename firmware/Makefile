CC=avr-gcc
CFLAGS=-Wall -O2 -DF_CPU=$(F_CPU) -mmcu=$(MCU)
MCU=atmega8
F_CPU=16000000L


PROGNAME = beamersteuerung

MYOBJS = beamer.o screen.o controls.o uart.o

ALLOBJS = $(PROGNAME).o $(MYOBJS)

OBJCOPY=avr-objcopy
BIN_FORMAT=ihex

AVRSIZE=avr-size -A

RM=rm -f


# Starting with simple, straight-forward CFLAGS:
CFLAGS   = -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS  += -std=c99 -pipe -Os -Wall

# And other FLAGs as well
CXXFLAGS = $(CFLAGS)
ASFLAGS  = -Wa,-adhlns=$(subst $(suffix $<),.lst,$<)
LDFLAGS  = -Wl,-Map=$(PROGNAME).map
LIBS     = -lm

### Compiler fine-tuning ###

# -Wno-pointer-sign because those "char*" and "uchar*" warnings are useless.
CFLAGS  += -Wno-pointer-sign

# With a non-returning void main, we can safely ignore this warning.
CFLAGS  += -Wno-main

# People say these are good flags:
CFLAGS  += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums

# Warn if the compiler adds padding inside any struct. This will break some
# code assumptions when loading/storing partial sensor data from EEPROM.
# -Wpadded
#   Warn if padding is included in a structure, either to align an element of
#   the structure or to align the whole structure.  Sometimes when this
#   happens it is possible to rearrange the fields of the structure to reduce
#   the padding and so make the structure smaller.
CFLAGS  += -Wpadded

# -Wmissing-field-initializers
#     Warn if a structure's initializer has some fields missing.
CFLAGS  += -Wmissing-field-initializers

# This saved 112 bytes
CFLAGS  += -fno-split-wide-types

# And I'm not very sure about enabling these:
#CFLAGS  += -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions
# But these saved 118 bytes:
CFLAGS  += -fno-move-loop-invariants -fno-tree-scev-cprop

# From GCC manpage:
#   -mcall-prologues
#      Functions prologues/epilogues expanded as call to appropriate subroutines.
#      Code size will be smaller.
# However, in my experiment it actually increased the code size by 54~86 bytes.
#CFLAGS  += -mcall-prologues

# From GCC manpage:
#   -mtiny-stack
#     Change only the low 8 bits of the stack pointer.
# This saves only 10 bytes.
CFLAGS  += -mtiny-stack

# -fms-extensions is required to accept anonymous structures and unions.
CFLAGS  += -fms-extensions

# Supposedly, -ffreestanding together with a non-returning main would save a
# few bytes. But in fact this flag increases the firmware by 8 or 14 bytes,
# even with a non-returning main.
# Also, it gives a linking error about 'fabs'.
#CFLAGS  += -ffreestanding

# Setting the cost of inlining small functions.
# My gcc 4.5.2 doesn't support inline-call-cost, maybe it was removed in newer
# GCC versions?
# Also, enabling those other options increased the firmware size.
#CFLAGS  += --param inline-call-cost=2 -finline-limit=3 -fno-inline-small-functions
#CFLAGS  += -finline-limit=3 -fno-inline-small-functions

# Replace CALL statements with RCALL where possible to save a few bytes.
LDFLAGS += -Wl,--relax

# Don't include unused functions and data.
CFLAGS  += -ffunction-sections -fdata-sections
LDFLAGS += -Wl,--gc-sections -Wl,--print-gc-sections

# Compile all *.c files at once, allowing for better optimizations.
# Note: -combine has been removed in GCC 4.6, in favor of LTO
#       http://gcc.gnu.org/bugzilla/show_bug.cgi?id=29171#c7
#       http://gcc.gnu.org/wiki/LinkTimeOptimization
COMBINE_FLAGS = -combine -fwhole-program


.PHONY: all
all: normal-build

normal-build: $(ALLOBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $(PROGNAME).elf $^ $(LIBS)

.PHONY: clean
clean:
	rm -f $(PROGNAME).{o,s,elf,hex,eep,lss,sym,lst,map}
	rm -f $(ALLOBJS)
	rm -f $(ALLOBJS:.o=.s)
	rm -f $(ALLOBJS:.o=.lst)
	rm -f $(ALLOBJS:.o=.map)


.PHONY: size
size: beamersteuerung.elf
	$(AVRSIZE) $<

%.elf: %.s ; $(CC) $(CFLAGS) -s -o $@ $<

%.s: %.c ; $(CC) $(CFLAGS) -S -o $@ $<

%.hex: %.elf ; $(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@
