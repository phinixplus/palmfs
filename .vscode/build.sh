#!/bin/bash

function build {
	case $1 in
		"release") GCC_ARGS="-Wall -Wextra -pedantic -O2 -Iincl/" ;;
		"debug") GCC_ARGS="-Wall -Wextra -pedantic -g -Iincl/" ;;
	esac
	mkdir -p bin/
	files=$(find src/ -name "*.c")
	for src in $files; do
		bin="bin/$(echo ${src::-2} | cut -d'/' -f2-).o"
		echo "Building: $src -> $bin"
		gcc $GCC_ARGS -c -o $bin $src
	done
	echo "Building: bin/*.o -> bin/palmfs"
	gcc $GCC_ARGS -o bin/palmfs bin/*.o -lfuse3
	echo "Build completed."
}

function clean {
	[[ -d bin/ ]] && rm -r bin/
}

case $1 in
	"build") build $2 ;;
	"clean") clean $2 ;;
esac