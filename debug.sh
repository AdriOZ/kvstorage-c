if [ ! -d "build" ]
then
    mkdir build
fi

rm -f build/*

gcc src/*.c -g -lm -std=c18 -o build/debug.o

build/debug.o
