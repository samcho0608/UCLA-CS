#Sungmin Cho
#205124669

OPTIMIZE = -O2
CC = gcc

CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) -Wall -fPIC -c randlibsw.c -o randlibsw.o
	$(CC) $(CFLAGS) -shared -o randlibsw.so randlibsw.o

randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) -Wall -fPIC -c randlibhw.c -o randlibhw.o
	$(CC) $(CFLAGS) -shared -o randlibhw.so randlibhw.o

randmain: randmain.c randcpuid.c
	$(CC) $(CFLAGS) -Wall -c randmain.c -o randmain.o
	$(CC) $(CFLAGS) -Wall -c randcpuid.c -o randcpuid.o
	$(CC) $(CFLAGS) -Wall randmain.o randcpuid.o -o randmain -ldl -Wl,-rpath=$(PWD)