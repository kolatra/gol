make:
    gcc -Wall -Werror -g -o sdl main.c `sdl2-config --cflags --libs`

run: make
    ./sdl
    rm sdl

test:
    gcc -o t test.c
    ./t
    rm t
    