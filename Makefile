
dir_libmurmureval=~/.local/lib/murmur.eval/
libdir_libmurmureval=$(dir_libmurmureval)/murmur_eval/build/
incdir_libmurmureval=$(dir_libmurmureval)/murmur_eval/incs/
libname_libmurmureval="libmurmureval.a"

# make && gcc example-murmur_eval.c libft.a murmur.eval/murmur_eval/build/libmurmureval.a -I murmur.eval/murmur_eval/incs/ -fsanitize=address -g -lbsd && ./a.out

tests_dir=./murminettes/



prj_lib42 = $(p_wd)
cflags_lib42= $(CFLAGS)
# ifdef verbose
# 	cflags_lib42+= -D DEBUG
# endif
cflags_lib42 += -I $(incdir_libmurmureval) -I $(prj_lib42) -g
ldflags_lib42= -L $(libdir_libmurmureval) -lmurmureval -lbsd -L $(prj_lib42) -lft -g -fsanitize=address
test_lib42 = $(tests_dir)libft/
files_lib42= $(shell find $(test_lib42) -name '*.c')
objs_lib42= $(files_lib42:.c=.o)
bin_lib42= $(test_lib42)bin_lib42


# objs_all = $(objs_lib42)

# bins_all = $(bin_lib42)

# .SUFFIXES: .c .o

# %.o: %.c

update: clear $(objs_all)
	

clear:
	@rm -f $(objs_all) $(bins_all)

log:
	@echo $(deps)

all:
	@echo "usage: make <libft|gnl|...>"

$(test_lib42)%.o: $(test_lib42)%.c $(test_lib42)/*.h ${prj_lib42}/libft.a
	@gcc $(cflags_lib42) -c $< -o $@ 2> /dev/null 1> /dev/null
$(bin_lib42): $(objs_lib42)
	@gcc -o $@ $^ $(ldflags_lib42)

$(murmur_eval):
