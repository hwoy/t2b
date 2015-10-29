cc = $(CC)
bin = t2b
CFLAGS =  -O2  -ansi -Wpedantic -Wall -Werror

.PHONY: all clean

all:	$(bin)

$(bin):	main.o function.o
	$(cc) -o $(bin) main.o function.o
main.o:
	$(cc) -c -o main.o $(CFLAGS) main.c
function.o:
	$(cc) -c -o function.o $(CFLAGS) function.c
clean:
	rm -rf main.o function.o $(bin) *~

