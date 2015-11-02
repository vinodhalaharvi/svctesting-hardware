CFLAGS=-ggdb -Wall -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

all: main

debug: main
	gdb ./main

main: main.o delay.o led.o svc.o 

led: led.o ledriver.o

run: clean main 
	./main

tags:
	ctags -R *.[ch]

clean:
	rm -f *.o main  
