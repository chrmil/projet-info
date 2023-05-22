all: exec.exe

*.o: *.c
	gcc -c $< -o $@

exec.exe: *.c
	gcc $^ -o $@
