#include "murmur_eval.hpp"
#include "libft.h"
#include <string.h>
#include <bsd/string.h>
#include <stdio.h>
#include "./v.h"

typedef struct s_strlcpy t_strlcpy;
typedef struct s_strlcpy t_strlcat;

struct s_strlcpy {
	size_t	size;
	char	*src;
	char 	*dst;
};

void		ft_strlcat_test()
{
	_res = &(t_strlcat){};
	((t_strlcat *)_res)->dst = ((t_strlcat *)_try)->dst;
	((t_strlcat *)_res)->size = ft_strlcat(
		((t_strlcat *)_res)->dst,
		((t_strlcat *)_try)->src,
		((t_strlcat *)_try)->size
	);
	ft_strlcpy_eval();
}

int eq;

void		ft_strlcpy_test()
{
	_res = &(t_strlcpy){};
	((t_strlcpy *)_res)->dst = ((t_strlcpy *)_try)->dst;
	((t_strlcpy *)_res)->size = ft_strlcpy(
		((t_strlcpy *)_res)->dst,
		((t_strlcpy *)_try)->src,
		((t_strlcpy *)_try)->size
	);
	ft_strlcpy_eval();
}
void		ft_strlcpy_eval_x(){
	printf("expected	[ dst: ");
	fflush(stdout);
	write(1, ((t_strlcpy *)_exp)->dst, 10);
	printf(", ret: %zu ]\n", ((t_strlcpy *)_exp)->size);
}
void		ft_strlcpy_eval_eq(){
	#ifdef DEBUG
		ft_strlcpy_eval_x();
		printf("==================TEST %zu="GREEN"[OK]"RESET"================\n\n\n", _idx);	
	#else
		printf(GREEN"t_%zu: [OK] "RESET, _idx);
	#endif // DEBUG
}
void		ft_strlcpy_eval_neq(){
	ft_strlcpy_eval_x();
	printf(YELLOW"your		[ src: no, dst: "RESET);
	fflush(stdout);
	write(1, ((t_strlcpy *)_res)->dst, 10);
	printf(", sz: %zu ]\n", ((t_strlcpy *)_res)->size);
	printf("^^^^^^^^^=========TEST %zu="RED"[KO]"RESET"================\n\n\n", _idx);	
}
void		ft_strlcpy_eval(){
	int eqstr = memcmp(
		((t_strlcpy *)_res)->dst,
		((t_strlcpy *)_exp)->dst,
		10
	);
	eq = (((t_strlcpy *)_res)->size == ((t_strlcpy *)_exp)->size);

	#ifdef DEBUG
		printf("=============== %s ============\n", _name);
		printf("try		[ src: %s, dst: ", ((t_strlcpy *)_try)->src);fflush(stdout);
		write(1, ((t_strlcpy *)_try)->dst, 10);
		printf(", sz: %zu ]\n", ((t_strlcpy *)_try)->size);	
	#endif // DEBUG
	(eq && eqstr == 0) ? ft_strlcpy_eval_eq() : ft_strlcpy_eval_neq();
}

// make && gcc example-murmur_eval.c libft.a murmur.eval/murmur_eval/build/libmurmureval.a -I murmur.eval/murmur_eval/incs/ -fsanitize=address -g -lbsd && ./a.out 

// example ultra complex test case usage:
// ((&(t_strlcpy){
// 			.size = 0 ,
// 			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
// 			.src = "coucou"
// 		}),(
// 			_tmp = &(t_strlcpy){},
// 			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
// 			({
// 				t_strlcpy *res = _tmp;
// 				res->size = strlcpy(res->dst, "coucou", 0);
// 			}),
// 			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", 0),
// 			_tmp
// 		))

int main(){
	// OLD_CASES(
	// 	NEW_CASE("abc", &(size_t){3}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("nnnn", &(size_t){4}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("nnnnnnnnnnnnnn", &(size_t){4}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("a", &(size_t){4}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("a", &(size_t){1}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("a", &(size_t){1}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("a", &(size_t){1}, ft_strlen_test, ft_strlen_eval)
	// t1:	NEW_CASE("a", &(size_t){1}, ft_strlen_test, ft_strlen_eval) break;
	// 	NEW_CASE("a", &(size_t){1}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("a", &(size_t){1}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("a", &(size_t){1}, ft_strlen_test, ft_strlen_eval)
	// 	NEW_CASE("a", &(size_t){1}, ft_strlen_test, ft_strlen_eval) break;
	// )
	// printf("tsrat\n");
	// NEW_CASES(ft_strlen_test, ft_strlen_eval,
	// 	("abc", &(size_t){3}),
	// 	("nnnn", &(size_t){4}),
	// 	("nnnnnnnnnnnnnn", &(size_t){14}),


	// 	("a", &(size_t){3}),
	// 	(({
	// 		static char arr[] = "aa";
	// 		NULL;}), &(size_t){3})
	// )
	// NEW_CASES( ft_strlen_test, ft_strlen_eval,
	// 	((char []){"abc"}, &(size_t){3}),
	// 	((char []){"nnnn"}, &(size_t){4}),
	// 	((char []){"nnnnnnnnnnnnnn"}, &(size_t){14}),
	// 	((char []){"a"}, &(size_t){3}),
	// 	(({
	// 		static char arr[] = "aa";
	// 		arr;}), &(size_t){3})
	// )
	// __cplusplus && __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L

	// https://github.com/Tripouille/libftTester/blob/master/tests/ft_strlcpy_test.cpp
	// /* 1 */ check(ft_strlcpy(dest, src, 0) == strlen(src) && dest[0] == 'A'); showLeaks();
	// /* 2 */ check(ft_strlcpy(dest, src, 1) == strlen(src) && dest[0] == 0 && dest[1] == 'A'); showLeaks();
	// /* 3 */ check(ft_strlcpy(dest, src, 2) == strlen(src) && dest[0] == 'c' && dest[1] == 0  && dest[2] == 'A'); showLeaks();
	// /* 4 */ check(ft_strlcpy(dest, src, -1) == strlen(src) && !strcmp(src, dest) && dest[strlen(src) + 1] == 'A'); showLeaks(); memset(dest, 'A', 10);
	// /* 5 */ check(ft_strlcpy(dest, src, 6) == strlen(src) && !memcmp(src, dest, 5) && dest[5] == 0); showLeaks(); memset(dest, 'A', 10);
	// /* 6 */ check(ft_strlcpy(dest, src, 7) == strlen(src) && !memcmp(src, dest, 7)); showLeaks(); memset(dest, 'A', 10);
	// /* 7 */ check(ft_strlcpy(dest, src, 8) == strlen(src) && !memcmp(src, dest, 7)); showLeaks(); memset(dest, 'A', 10);
	// /* 8 */ check(ft_strlcpy(dest, "", 42) == 0 && !memcmp("", dest, 1)); showLeaks(); memset(dest, 0, 10);
	// /* 9 */ check(ft_strlcpy(dest, "1", 0) == 1 && dest[0] == 0); showLeaks(); memset(dest, 'A', 10);	
	printf("\n======== STRLCPY TESTS ========\n");
	NEW_CASES( ft_strlcpy_test,
		((&(t_strlcpy){
			.size = 0 ,													// size arg
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},	// dst arg
			.src = "coucou"												// src arg
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'}, // expected dst
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", 0), // expected return size
			_tmp
		)),
		((&(t_strlcpy){
			.size = 1 ,
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			.src = "coucou"
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", 1),
			_tmp
		)),
		((&(t_strlcpy){
			.size = 2 ,
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			.src = "coucou"
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", 2),
			_tmp
		)),
		((&(t_strlcpy){
			.size = -1 ,
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			.src = "coucou"
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", -1),
			_tmp
		)),
		((&(t_strlcpy){
			.size = 6 ,
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			.src = "coucou"
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", 6),
			_tmp
		)),
		((&(t_strlcpy){
			.size = 7 ,
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			.src = "coucou"
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", 7),
			_tmp
		)),
		((&(t_strlcpy){
			.size = 8 ,
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			.src = "coucou"
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", 8),
			_tmp
		)),
		((&(t_strlcpy){
			.size = 42 ,
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			.src = ""
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "", 42),
			_tmp
		)),
		((&(t_strlcpy){
			.size = 0 ,
			.dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			.src = "1"
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'},
			(*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "1", 0),
			_tmp
		))
	)

	// https://github.com/Tripouille/libftTester/blob/master/tests/ft_strlcat_test.cpp
	// char dest[30]; memset(dest, 0, 30);
	// char * src = (char *)"AAAAAAAAA";
	// dest[0] = 'B';
	// /* 1 */ check(ft_strlcat(dest, src, 0) == strlen(src) && !strcmp(dest, "B")); showLeaks();
	// dest[0] = 'B';
	// /* 2 */ check(ft_strlcat(dest, src, 1) == 10 && !strcmp(dest, "B")); showLeaks();
	// memset(dest, 'B', 4);
	// /* 3 */ check(ft_strlcat(dest, src, 3) == 3 + strlen(src) && !strcmp(dest, "BBBB")); showLeaks();
	// /* 4 */ check(ft_strlcat(dest, src, 6) == 13 && !strcmp(dest, "BBBBA")); showLeaks();
	// memset(dest, 'C', 5);
	// /* 5 */ check(ft_strlcat(dest, src, -1) == 14 && !strcmp(dest, "CCCCCAAAAAAAAA")); showLeaks();
	// memset(dest, 'C', 15);
	// /* 6 */ check(ft_strlcat(dest, src, 17) == 24 && !strcmp(dest, "CCCCCCCCCCCCCCCA")); showLeaks();
	// memset(dest, 0, 30);
	// /* 7 */ check(ft_strlcat(dest, src, 1) == strlen(src) && !strcmp(dest, "")); showLeaks();
	// memset(dest, 0, 30); memset(dest, '1', 10);
	// /* 8 */ check(ft_strlcat(dest, src, 5) == strlen(src) + 5 && !strcmp(dest, "1111111111")); showLeaks();
	// memset(dest, 0, 30); memset(dest, '1', 10);
	// /* 9 */ check(ft_strlcat(dest, src, 5) == strlen(src) + 5 && !strcmp(dest, "1111111111")); showLeaks();
	// memset(dest, 0, 30); memset(dest, '1', 10);
	// /* 10 */ check(ft_strlcat(dest, "", 15) == 10 && !strcmp(dest, "1111111111")); showLeaks();
	// memset(dest, 0, 30);
	// /* 11 */ check(ft_strlcat(dest, "", 42) == 0 && !strcmp(dest, "")); showLeaks();
	// memset(dest, 0, 30);
	// /* 12 */ check(ft_strlcat(dest, "", 0) == 0 && !strcmp(dest, "")); showLeaks();
	// memset(dest, 0, 30);
	// /* 13 */ check(ft_strlcat(dest, "123", 1) == 3 && !strcmp(dest, "")); showLeaks();
	// memset(dest, 0, 30);
	// /* 14 */ check(ft_strlcat(dest, "123", 2) == 3 && !strcmp(dest, "1")); showLeaks();
	// memset(dest, 0, 30);
	// /* 15 */ check(ft_strlcat(dest, "123", 3) == 3 && !strcmp(dest, "12")); showLeaks();
	// memset(dest, 0, 30);
	// /* 16 */ check(ft_strlcat(dest, "123", 4) == 3 && !strcmp(dest, "123")); showLeaks();
	// memset(dest, 0, 30);
	// /* 17 */ check(ft_strlcat(dest, "123", 0) == 3 && !strcmp(dest, "")); showLeaks();

	printf("\n======== STRLCAT TESTS ========\n");
	NEW_CASES( ft_strlcat_test,
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				((char *)_tmp)[0] = 'B';
			}), _tmp),													// dst arg
			.src = "AAAAAAAAA",											// src arg
			.size = 0 ,													// size arg
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0}, // expected dst
			({ (*(t_strlcpy *)_tmp).dst[0] = 'B'; }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", 0), // expected return size
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				((char *)_tmp)[0] = 'B';
			}), _tmp),
			.src = "AAAAAAAAA",
			.size = 1 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ (*(t_strlcpy *)_tmp).dst[0] = 'B'; }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", 1),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 'B', 4);
			}), _tmp),
			.src = "AAAAAAAAA",
			.size = 3 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 'B', 4); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", 3),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 'B', 4);
			}), _tmp),
			.src = "AAAAAAAAA",
			.size = 6 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 'B', 4); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", 6),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 'C', 5);
			}), _tmp),
			.src = "AAAAAAAAA",
			.size = -1 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 'C', 5); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", -1),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 'C', 15);
			}), _tmp),
			.src = "AAAAAAAAA",
			.size = 17 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 'C', 15); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", 17),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 0, 30);
			}), _tmp),
			.src = "AAAAAAAAA",
			.size = 1 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 0, 30); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", 1),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, '1', 10);
			}), _tmp),
			.src = "AAAAAAAAA",
			.size = 5 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, '1', 10); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", 5),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, '1', 10);
			}), _tmp),
			.src = "AAAAAAAAA",
			.size = 5 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, '1', 10); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "AAAAAAAAA", 5),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, '1', 10);
			}), _tmp),
			.src = "",
			.size = 15 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, '1', 10); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "", 15),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 0, 30);
			}), _tmp),
			.src = "",
			.size = 42 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 0, 30); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "", 42),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 0, 30);
			}), _tmp),
			.src = "",
			.size = 0 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 0, 30); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "", 0),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 0, 30);
			}), _tmp),
			.src = "123",
			.size = 1 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 0, 30); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "123", 1),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 0, 30);
			}), _tmp),
			.src = "123",
			.size = 2 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 0, 30); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "123", 2),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 0, 30);
			}), _tmp),
			.src = "123",
			.size = 3 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 0, 30); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "123", 3),
			_tmp
		)),
		((&(t_strlcpy){
			.dst = (_tmp = (char [30]){0}, ({
				memset(_tmp, 0, 30);
			}), _tmp),
			.src = "123",
			.size = 0 ,
		}),(
			_tmp = &(t_strlcpy){},
			(*(t_strlcpy *)_tmp).dst = (char [30]){0},
			({ memset((*(t_strlcpy *)_tmp).dst, 0, 30); }),
			(*(t_strlcpy *)_tmp).size = strlcat((*(t_strlcpy *)_tmp).dst, "123", 0),
			_tmp
		))
	)
	printf("\n");
	return 0;
}
