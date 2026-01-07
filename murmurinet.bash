#!/bin/bash

bash -l -c 'murmur \'
# clear
# exit 0;

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
	else
		echo "/* #define DEBUG */" > ./murminettes/libft/v.h
	fi
	make ./murminettes/libft/bin_lib42 p_wd="$1" verbose="$2" || { echo "Makefile error in $1"; exit 1; }
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
	# u)
	# 	echo "Updating murmurinet..."
	# 	update "$3"
	# 	;;
    libft)
		libft "$2" "$3"
        ;;
    gnl)
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

