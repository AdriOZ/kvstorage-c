if [ ! -d "build" ]
then
    mkdir build
fi

rm -f build/*

gcc src/*.c -g -lm -std=c18 -O3 -o build/main.o

build/main.o
