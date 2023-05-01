TARGET = main

# SERIALPORT = /dev/cu.usbserial
# SERIALPORT = /dev/cu.KeySerial1
# SERIALPORT = /dev/cu.UPSH112I1d13P1.1
SERIALPORT = usb

# PROGRAMMER = jtagmkii
# PROGRAMMER = stk500v2
# PROGRAMMER = avrispmkii
PROGRAMMER = usbasp

SRCS = main.c

OBJS = $(SRCS:.c=.o)

#CPU = atmega328
CPU = atmega128

BINDIR = .
OPTIMIZE = -O2
INCLUDE  = -I. -Iinclude -Iinclude/avrx
CFLAGS   = -mmcu=${CPU} -Wall ${OPTIMIZE} -g ${INCLUDE} ${OPTIMIZE}

#-Werror
#for Windows compilation, for Mac, you need to comment out the following line.
#CFLAGS += -DWINDOWS -D__STDIO_FDEVOPEN_COMPAT_12

LIBS     = -lm
CC       = avr-gcc
LDFLAGS += -Wl,-u,vfprintf,-lprintf_flt
REALTARGET = $(addprefix ${BINDIR}/, $(addsuffix .hex, ${TARGET}))

#.PRECIOUS: %.elf %.o

all: ${REALTARGET}

%.s: %.c
	${CC} -c ${CFLAGS} -S -o $@ $<

%.o: %.c
	${CC} -c ${CFLAGS} -o $@ $<

%.elf: %.o
	${CC} -mmcu=${CPU} ${LDFLAGS} -o $@ $(OBJS) ${LIBS}

%.hex: %.elf
	avr-objcopy -O ihex $< $@

#for JTAG
#${BINDIR}/%.cof: %.elf
#	avr-objcopy --debugging -O ${FORMAT} \
#	--change-section-address .data-0x800000 \
#	--change-section-address .bss-0x800000 \
#	--change-section-address .noinit-0x800000 \
#	$< $@

%.lst: %.elf
	avr-objdump -h -S $< > $@

clean:
	rm -f ${REALTARGET} *.hex *.srec *.elf *.o *.bin *.s *.lst *~ .depend Makefile.bak

assembly:
	for i in ${OBJS}; do make $${i%%.*}.s; done

program: all
	# IF USING THE OLDER AVRISP, UNCOMMENT THE NEXT TWO LINES TO USE UISP

	#uisp -v=3 -dprog=stk500 -dpart=ATmega128 -dserial=${SERIALPORT} --erase
	#uisp -v=3 -dprog=stk500 -dpart=ATmega128 -dspeed=115200 -dserial=${SERIALPORT} --upload if=${BINDIR}/${TARGET}.hex

	# USE AVRDUDE IF USING THE NEWER VERSION OF AVRISP

	avrdude -p $(CPU) -c ${PROGRAMMER} -P ${SERIALPORT} -v -U flash:w:${BINDIR}/${TARGET}.hex:i

