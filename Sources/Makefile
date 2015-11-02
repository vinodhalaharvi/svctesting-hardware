CFLAGS=-ggdb -Wall -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

all: shell

debug: shell
	gdb ./shell

capacitivepads: capacitivepads.o

capacitivepadsdriver: capacitivepadsdriver.o

delay: delay.o

lcdc: lcdc.o

lcdcConsole: lcdcConsole.o lcdcdriver.o 

lcdcdriver: lcdcdriver.o

led: led.o

leddriver: leddriver.o

main: main.o

mcg: mcg.o

potentiometer: potentiometer.o

potentiometerdriver: potentiometerdriver.o

profont: profont.o

pushbutton: pushbutton.o

pushbuttondriver: pushbuttondriver.o

sdram: sdram.o

svc: svc.o

uart: uart.o

uartdriver: uartdriver.o

shell: shell.o common.o map.o mymalloc.o stringutils.o io.o file.o io.o pushbutton.o led.o mcg.o sdram.o uart.o lcdc.o lcdcConsole.o profont.o

stringutils: stringutils.o mymalloc.o common.o

map: map.o

mymalloc: common.o mymalloc.o 

file: file.o mymalloc.o common.o stringutils.o  

led: led.o ledriver.o

io: io.o led.o pushbutton.o file.o mymalloc.o common.o stringutils.o

leddriver: leddriver.o

pushbuttondriver: pushbuttondriver.o

pushbutton: pushbutton.o

driver: driver.o

common: common.o

mymalloctesting: common.o mymalloc.o mymalloctesting.o stringutils.o

run: clean shell stringutils
	./shell

tags:
	ctags -R *.[ch]

clean:
	rm -f *.o shell  mymalloctesting  file
	rm -f mymalloc io stringutils
