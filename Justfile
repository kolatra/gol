make:
    gcc -o sdl main.c `sdl2-config --cflags --libs`
    ./sdl
    rm sdl

test:
    gcc -o t test.c
    ./t
    rm t
    