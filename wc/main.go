package main

import (
	"fmt"
	"log"
	"os"
)

func usage() {
	fmt.Println("usage: ./wc [options...] filename")
	os.Exit(1)
}

func main() {
	args := os.Args[1:]
	if len(args) == 0 {
		usage()
	}

	if len(args) == 1 {
		filename := args[0]
		lineCount, wordCount, byteCount := defaultOption(filename)
		fmt.Println(lineCount, wordCount, byteCount, filename)
		os.Exit(0)
	}

	var option, filename string
	if len(args) == 2 {
		option = args[0]
		filename = args[1]
	}

	switch option {
	case "-c":
		byteCount := countBytes(filename)
		fmt.Println(byteCount, filename)
	case "-l":
		lineCount := countLines(filename)
		fmt.Println(lineCount, filename)
	case "-w":
		wordCount := countWords(filename)
		fmt.Println(wordCount, filename)
	case "-m":
		charCount := countChars(filename)
		fmt.Println(charCount, filename)
	default:
		log.Fatalf("Error: option %v not found", option)
	}
}
