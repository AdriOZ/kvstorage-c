if [ ! -d "build" ]
then
    mkdir build
fi

rm -f build/*

gcc -g src/*.c -o build/debug.o

build/debug.o
