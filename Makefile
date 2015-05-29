all : liblocaltime2038.so

liblocaltime2038.so : localtime2038.c
	gcc -m32 -shared -fPIC -o liblocaltime2038.so localtime2038.c -ldl

a.out : test.c
	gcc -m32 test.c

test : liblocaltime2038.so a.out
	LD_PRELOAD=./liblocaltime2038.so ./a.out

clean :
	-rm a.out liblocaltime2038.so
