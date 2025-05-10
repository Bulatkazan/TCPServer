all: run clean

run: 
	gcc -Werror -Wextra -Wall src/srv.c -o srv
	# strace -f ./sockets
	./srv

clean: 
	rm -rf ./srv
