package main

import (
	"fmt"
	"log"
	"os"
    "bufio"
)

func countBytes(filename string) int {
	data, err := os.ReadFile(filename)
	if err != nil {
		log.Fatalf("Error reading file %v: %v", filename, err)
	}
	return len(data)
}

func countLines(filename string) int {
    f, err := os.Open(filename)
    if err != nil {
        fmt.Errorf("Error: opening file %v: %v", filename, err)
    }
    defer f.Close()
    scanner := bufio.NewScanner(f)
    linesCount := 0
    for scanner.Scan() {
        linesCount++
    }
    if err = scanner.Err(); err != nil {
        log.Fatalln(err)
    } 
    return linesCount
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
		result := countBytes(filename)
		fmt.Println(result, filename)
    case "-l":
        result := countLines(filename)
        fmt.Println(result, filename)
	default:
		log.Fatalf("Error: option %v not found", option)
	}
}
