package main

import (
	"fmt"
	"os"
	"strings"
	"slices"
)

func usage() {
	fmt.Println("usage: ./wc [options...] filename")
	os.Exit(1)
}

func handleArgs(args []string) ([]string, []rune) {
	var options []rune
	var files []string
	for _, arg := range args {
		if strings.HasPrefix(arg, "-") {
			arg = strings.Trim(arg, "-")
			for _, r := range arg {
				options = append(options, r)
			}
		} else {
			files = append(files, arg)
		}
	}
	return files, options
}

func main() {
	files, options := handleArgs(os.Args[1:])

	supportedOptions := []struct{ 
		opt rune
		f countFunc
	}{
		{ opt: 'l', f: countLines },
		{ opt: 'w', f: countWords },
		{ opt: 'm', f: countChars },
		{ opt: 'c', f: countBytes },
	}
	
	for _, filename := range files {
		var counts []string
		for _, opt := range supportedOptions {
			if slices.Contains(options, opt.opt) {
				counts = append(counts, string(opt.f(filename)))
			}
		}
		fmt.Println(strings.Join(counts, " ") + filename)
	}
}
