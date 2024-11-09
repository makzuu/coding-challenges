package main

import (
	"fmt"
	"log"
	"os"
)

func count_bytes(filename string) int {
	data, err := os.ReadFile(filename)
	if err != nil {
		log.Fatalf("Error reading file %v: %v", filename, err)
	}
	return len(data)
}

func main() {
	args := os.Args[1:]
	if len(args) != 2 {
		log.Fatalln("Error: 2 arguments expected: option, filename.")
	}

	option := args[0]
	filename := args[1]

	switch option {
	case "-c":
		result := count_bytes(filename)
		fmt.Println(result, filename)
	default:
		log.Fatalf("Error: option %v not found", option)
	}
}
