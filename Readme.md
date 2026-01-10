# Murminette tester collaborative repository

## installation

```bash
git clone https://github.com/murmurlab/scripts.git ~/.murmurbox ; bash ~/.murmurbox/murmurbox.bash<<<'' ; bash -l -c 'murmur \'
```
```bash
bash -l
```
```bash
murmur murminette libft "YOUR_LIBFT_ABSOLUTEPATH"
```

## logic

> note: this tester uses [murmur eval](https://github.com/lab-murmur-land/murmur.eval) as a test framework.

This is an example of how to write a test case. There may be more complex ways to write case studies; this is a simple one. You can give sample tests like this as input to the AI ​​and receive other test outputs. You can add your tests and send pull requests in this way.

file: murminette/murminettes/libft/lib42.c
```c
NEW_CASES( ft_strlcpy_test,
    ((&(t_strlcpy){
        .size = 0 ,                                                 // size arg
        .dst = (char []){'A','A','A','A','A','A','A','A','A','A'},  // dst arg
        .src = "coucou"                                             // src arg
    }),(
        _tmp = &(t_strlcpy){},
        (*(t_strlcpy *)_tmp).dst = (char []){'A','A','A','A','A','A','A','A','A','A'}, // expected dst
        (*(t_strlcpy *)_tmp).size = strlcpy((*(t_strlcpy *)_tmp).dst, "coucou", 0), // expected return size
        _tmp
    )),
    ...
    ...
```

The murmurbox (command murmur) downloads the necessary [murmur eval](https://github.com/lab-murmur-land/murmur.eval) test library when installing murminette. The makefile compiles the test code for the specific project with the required library.

## usage

To see detailed output, compile the test with the -v / -vno parameter (`murmur murminette libft "YOUR_LIBFT_ABSOLUTEPATH" -v`) then run it normally (`murmur murminette libft "YOUR_LIBFT_ABSOLUTEPATH"`)

### You can create an issue for errors, bugs, or features you want.
