package main

import (
	"fmt"
	"os"
	"slices"
	"strconv"
	"strings"
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

	supportedOptions := []struct {
		opt rune
		f   countFunc
	}{
		{opt: 'l', f: countLines},
		{opt: 'w', f: countWords},
		{opt: 'm', f: countChars},
		{opt: 'c', f: countBytes},
	}

	for _, filename := range files {
		var counts []string
		for _, opt := range supportedOptions {
			if slices.Contains(options, opt.opt) {
				count := opt.f(filename)
				strCount := strconv.Itoa(count)
				counts = append(counts, strCount)
			}
		}
		fmt.Println(strings.Join(counts, " "), filename)
	}
}
