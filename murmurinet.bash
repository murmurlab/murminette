#!/bin/bash

# clear
# exit 0;

get_next_line(){
	# cd "$1"
	if [ ! -d "$1" ]; then
		echo "Error: Directory $1 does not exist."
		exit 1
	fi
	echo "Testing get_next_line in directory: $1"
	bash ./murminettes/get_next_line/all_tests.bash "$(pwd)/murminettes/get_next_line/test.c" "$1"

	# cc -L "$1" -lgnl -I "$1" -o test_gnl murminettes/get_next_line/murminette.c || { echo "Compilation error for test_gnl"; exit 1; }
}

libft(){
	# cd "$1"
	if [ ! -d "$1" ]; then
		echo "Error: Directory $1 does not exist."
		exit 1
	fi
	if [ ! -f "$1"/Makefile ]; then
		echo "Error: Makefile not found in $1."
		exit 1
	fi
	echo "Testing libft in directory: $1 with verbose=$2"
	if [ "$2" == "-v" ]; then
		echo "#define DEBUG" > ./murminettes/libft/v.h
		exit 0;
	elif [ "$2" == "-vno" ]; then
		echo "/* #define DEBUG */" > ./murminettes/libft/v.h
		exit 0;
	fi
	if ! [ -f ./murminettes/libft/v.h ]; then
		echo "/* #define DEBUG */" > ./murminettes/libft/v.h
	fi
	make  ./murminettes/libft/bin_lib42 p_wd="$1" verbose="$2" || { echo "Makefile $? error in $1"; exit 1; }
	./murminettes/libft/bin_lib42
	# cc -L "$1" -lft -I "$1" -o test_libft libft/murminette.c || { echo "Compilation error for test_libft"; exit 1; }
}

update(){
	make ./murminettes/libft/bin_lib42 p_wd="$1" verbose="$2" || { echo "Makefile error in $1"; exit 1; }
}

# check argc
if [ $# -lt 2 ]; then
	echo "usage: $0 {libft|gnl} [path] [tester opt]"
	exit 1
fi
case $1 in
	u)
		echo "Updating murmurinet..."
		bash -l -c 'murmur \'
		echo "Update complete."
		exit 0
		;;
    libft)
		libft "$2" "$3"
        ;;
    gnl)
		get_next_line "$2"
        ;;
    *)
		echo "usage: $0 {libft|gnl} [path]"
		exit 1
        ;;
esac

# dir_libmurmureval=~/.local/lib/murmur.eval/
# libdir_libmurmureval="$dir_libmurmureval"/murmur_eval/build/
# incdir_libmurmureval="$dir_libmurmureval"/murmur_eval/incs/
# libname_libmurmureval="libmurmureval.a"

